#ifndef NETWORKMAIN_H_INCLUDED
#define NETWORKMAIN_H_INCLUDED

#include <winsock2.h>

namespace TFC {
namespace Network {
namespace NetworkData {
extern WSADATA WSA;
} // NetworkData
 // Initialize & Quit
bool Initialize();
void Quit();
} // Network
} // TFC

#endif // NETWORKMAIN_H_INCLUDED
