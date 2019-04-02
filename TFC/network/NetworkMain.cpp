#include "NetworkMain.h"

namespace TFC {
namespace Network {
namespace NetworkData {
WSADATA WSA;
} // NetworkData
 // Initialize & Quit
bool Initialize() {
    return WSAStartup(MAKEWORD(2,2),&NetworkData::WSA) == 0;
}

void Quit() {
    WSACleanup();
}
} // Network
} // TFC
