#include "TCPClient.h"

namespace TFC {
namespace Network {
TCPClient::TCPClient() {}

TCPClient::~TCPClient() {
    Disconnect();
}

bool TCPClient::Connect(const char* IP, Uint16 port, Uint64 mSize) {
    Disconnect();

    cSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (cSock == INVALID_SOCKET) {
        return false;
    }

    cAddr.sin_family = AF_INET;
    cAddr.sin_addr.S_un.S_addr = inet_addr(IP);
    cAddr.sin_port = htons(port);

    int mode = 1;
    if (ioctlsocket(cSock, FIONBIO, (u_long*)&mode) == SOCKET_ERROR) {
        closesocket(cSock);
        return false;
    }

    while (true) {
        if (connect(cSock, (LPSOCKADDR)&cAddr, sizeof(cAddr)) == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK || err == WSAEINVAL) {
                Sleep(1);
                continue;
            }
            else if (err == WSAEISCONN) {
                break;
            }
            else {
                closesocket(cSock);
                return false;
            }
        }
    }

    connected = true;
    msgSize = mSize;

    return true;
}

bool TCPClient::IsConnected() const {
    return connected;
}

void TCPClient::Disconnect() {
    if (connected) {
        closesocket(cSock);
        connected = false;
    }
}

std::string TCPClient::GetMsg() {
    std::string rtn;
    rtn.resize(msgSize + 1);
    if (recv(cSock, &rtn[0], msgSize + 1, 0) == SOCKET_ERROR) {
        return "ERROR FROM TFC";
    }
    else {
        return rtn;
    }
}

bool TCPClient::SendMsg(const char* msg) {
    std::string sMsg = msg;
    sMsg.resize(msgSize + 1);
    while (true) {
        if (send(cSock, &sMsg[0], msgSize + 1, 0) == SOCKET_ERROR) {
            if(WSAGetLastError() == WSAEWOULDBLOCK) {
                Sleep(1);
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }
}
} // Network
} // TFC
