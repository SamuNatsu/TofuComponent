#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "../../TFC_header.h"

#include <mswsock.h>
#include <windows.h>
#include <winsock2.h>

#include <mutex>
#include <queue>
#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <functional>
#include <unordered_map>

namespace TFC {
namespace Network {
class TCPServer {
using Uint16 = uint16_t;
using Uint64 = uint64_t;
using VUF = std::function<void(Uint64)>;
public:
    struct TCPmsg {
        std::string msg;
        Uint64 index;
    };
     // Construction & Destruction
    TCPServer();
    ~TCPServer();
     // Open & Close
    bool Open(Uint16, int, Uint64 = 255);
    bool IsOpened() const;
    void Close();
     // Control
    Uint64 FreshMsgQueue();
    bool GetMsg(TCPmsg&);
    bool SendMsg(Uint64, const char*);
    void BroadcastMsg(const char*);
     // Get
    bool GetIPAndPort(Uint64, std::string&, Uint16&);
     // Set
    void SetConnectCallback(VUF);
    void SetDisconnectCallback(VUF);
private:
    bool opened = false;

    SOCKET sSock;
    SOCKADDR_IN sAddr;
    Uint64 msgSize;

    std::atomic<bool> sFlag;
    std::shared_ptr<std::thread> sThread;

    Uint64 cnt = 0;
    std::unordered_map<Uint64, SOCKET> cMap;
    VUF cCallback = [](Uint64 index){}, dCallback = [](Uint64 index){};
    std::mutex mMutex;

    std::queue<TCPmsg> msgQueue;
/*
    HANDLE IOCP;

    std::vector<std::shared_ptr<std::thread> > workers;

    LPFN_ACCEPTEX pAcceptEx;*/
};
} // Network
} // TFC

#endif // TCPSERVER_H
