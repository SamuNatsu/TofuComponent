#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <cstdint>
#include <winsock2.h>

#include <string>

namespace TFC {
namespace Network{
class TCPClient{
using Uint16 = uint16_t;
using Uint64 = uint64_t;
public:
     // Construction & Destruction
    TCPClient();
    ~TCPClient();
     // Connect & Disconnect
    bool Connect(const char*, Uint16, Uint64 = 255);
    bool IsConnected() const;
    void Disconnect();
     // Control
    std::string GetMsg();
    bool SendMsg(const char*);
private:
    bool connected = false;
    Uint64 msgSize;

    SOCKET cSock;
    SOCKADDR_IN cAddr;
};
} // Network
} // TFC

#endif // TCPCLIENT_H
