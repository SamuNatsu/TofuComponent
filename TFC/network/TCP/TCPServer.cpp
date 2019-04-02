#include "TCPServer.h"

namespace TFC {
namespace Network {

TCPServer::TCPServer() {}

TCPServer::~TCPServer() {
    Close();
}

bool TCPServer::Open(Uint16 port, int waitCount, Uint64 mSize) {
    Close();
/*
	sFlag.store(true);

    IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (IOCP == NULL) {
        return false;
    }

	sFlag.store(true);
    for (int i = 0, lmt = SDL_GetCPUCount() << 1; i < lmt; ++i) {
        workers.emplace_back(
            std::make_shared<std::thread>(
                std::thread(
                    [&]() {
                        void* pContext = NULL;
                        OVERLAPPED* pOverlapped = NULL;
                        DWORD dw = 0;
                        do {
                            GetQueuedCompletionStatus(IOCP, &dw, (PULONG_PTR)&pContext, &pOverlapped, INFINITE);
                        }
                        while (sFlag.load());
                    })));
    }

    sSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sSock == INVALID_SOCKET) {
		return false;
	}

    sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(sSock, (sockaddr*)&sAddr, sizeof(sAddr)) == SOCKET_ERROR) {
		closesocket(sSock);
		return false;
	}

	if (listen(sSock, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(sSock);
		return false;
	}

    //CreateIoCompletionPort(sSock, IOCP, 0, 0);

    GUID guidAcceptEx = WSAID_ACCEPTEX;
    DWORD dw = 0;
    if (WSAIoctl(sSock,
                 SIO_GET_EXTENSION_FUNCTION_POINTER,
                 &guidAcceptEx,
                 sizeof(guidAcceptEx),
                 &pAcceptEx,
                 sizeof(pAcceptEx),
                 &dw,
                 NULL,
                 NULL) == SOCKET_ERROR) {
		closesocket(sSock);
		return false;
    }*/

    sSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sSock == INVALID_SOCKET) {
		return false;
	}

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(sSock, (const struct sockaddr*)&sAddr, sizeof(sAddr)) == SOCKET_ERROR) {
		closesocket(sSock);
		return false;
	}

	if (listen(sSock, waitCount) == SOCKET_ERROR) {
		closesocket(sSock);
		return false;
	}

	int mode = 1;
	if (ioctlsocket(sSock, FIONBIO, (u_long*)&mode) == SOCKET_ERROR) {
        closesocket(sSock);
		return false;
	}

    int timeo = 1000;
    setsockopt(sSock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeo, sizeof(timeo));
    setsockopt(sSock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeo, sizeof(timeo));

	sFlag.store(true);
    sThread = std::make_shared<std::thread>(
                std::thread(
                    [&]() {
                        SOCKET sClient;
                        sockaddr_in addrClient;
                        int addrClientlen = sizeof(addrClient);
                        while (sFlag.load()) {
                            sClient = accept(sSock, (sockaddr*)&addrClient, &addrClientlen);
                            if (sClient == INVALID_SOCKET) {
                                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                                    Sleep(10);
                                    continue;
                                }
                                else {
                                    return;
                                }
                            }
                            else {
                                {
                                    std::unique_lock<std::mutex> lock(mMutex);
                                    cMap[++cnt] = sClient;
                                }
                                cCallback(cnt);
                            }
                        }
                    }));

    opened = true;
    msgSize = mSize;

	return true;
}

bool TCPServer::IsOpened() const {
    return opened;
}

void TCPServer::Close() {
    if (opened) {
        sFlag.store(false);
        if(sThread.get()->joinable()) {
            sThread.get()->join();
        }
        sThread.reset();

        for (auto& i : cMap) {
            dCallback(i.first);
            closesocket(i.first);
        }
        cMap.clear();
        closesocket(sSock);

        opened = false;
    }
}

TCPServer::Uint64 TCPServer::FreshMsgQueue() {
    std::unique_lock<std::mutex> lock(mMutex);

    std::queue<Uint64> delQueue;
    Uint64 cnt = 0;

    for (auto& i : cMap) {
        std::string msg;
        msg.resize(msgSize + 1);
        while (true) {
            if (recv(i.second, &msg[0], msgSize, 0) == SOCKET_ERROR) {
                int err = WSAGetLastError();
                if (err == WSAEWOULDBLOCK) {
                    break;
                }
                else if (err == WSAEINVAL) {
                    Sleep(5);
                    continue;
                }
                else {
                    delQueue.push(i.first);
                    break;
                }
            }
            else {
                msgQueue.emplace((TCPmsg){msg, i.first});
                ++cnt;
                break;
            }
        }
    }

    while (!delQueue.empty()) {
        dCallback(delQueue.front());
        cMap.erase(delQueue.front());
        delQueue.pop();
    }

    return cnt;
}

bool TCPServer::GetMsg(TCPmsg& msg) {
    if (!msgQueue.empty()) {
        msg = msgQueue.front();
        msgQueue.pop();
        return true;
    }
    return false;
}

bool TCPServer::SendMsg(Uint64 index, const char* msg) {
    std::unique_lock<std::mutex> lock(mMutex);

    SOCKET cSock = cMap[index];
    std::string sMsg = msg;
    sMsg.resize(msgSize + 1);

    while (true) {
        if (send(cSock, &sMsg[0], msgSize + 1, 0) == SOCKET_ERROR) {
            if(WSAGetLastError() == WSAEWOULDBLOCK) {
                Sleep(5);
                continue;
            }
            else {
                dCallback(cSock);
                cMap.erase(cSock);
                return false;
            }
        }
        break;
    }

    return true;
}

void TCPServer::BroadcastMsg(const char* msg) {
    std::unique_lock<std::mutex> lock(mMutex);

    std::queue<Uint64> delQueue;

    for (auto& i : cMap) {
        std::string sMsg = msg;
        sMsg.resize(msgSize + 1);

        while (true) {
            if (send(i.first, &sMsg[0], msgSize + 1, 0) == SOCKET_ERROR) {
                if(WSAGetLastError() == WSAEWOULDBLOCK) {
                    Sleep(5);
                    continue;
                }
                else {
                    delQueue.push(i.first);
                    break;
                }
            }
            break;
        }
    }

    while (!delQueue.empty()) {
        dCallback(delQueue.front());
        cMap.erase(delQueue.front());
        delQueue.pop();
    }
}

bool TCPServer::GetIPAndPort(Uint64 index, std::string& ip, Uint16& port) {
    std::unique_lock<std::mutex> lock(mMutex);

    if (cMap.find(index) == cMap.end()) {
        return false;
    }

    SOCKADDR_IN cAddr;
    int len = sizeof(cAddr);

    if (getpeername(cMap[index], (sockaddr*)&cAddr, &len) == SOCKET_ERROR) {
        return false;
    }
    else {
        ip = inet_ntoa(cAddr.sin_addr);
        port = ntohs(cAddr.sin_port);
    }

    return true;
}

void TCPServer::SetConnectCallback(VUF callbackFunction) {
    std::unique_lock<std::mutex> lock(mMutex);

    cCallback = callbackFunction;
}

void TCPServer::SetDisconnectCallback(VUF callbackFunction) {
    std::unique_lock<std::mutex> lock(mMutex);

    dCallback = callbackFunction;
}
} // Network
} // TFC
