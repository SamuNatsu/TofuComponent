#ifndef EVENTHOOKMGR_H
#define EVENTHOOKMGR_H

#include "EventHook.h"

#include <string>
#include <unordered_map>

namespace TFC {
class EventHookMgr {
using VVF = std::function<void()>;
public:
     // Construction & Destruction
    EventHookMgr();
    ~EventHookMgr();
     // Add & Remove
    bool AddHook(const char*, SDL_EventType, VVF);
    bool IsHookExists(const char*);
    void RemoveAllHook();
    bool RemoveHook(const char*);
     // Get
    Uint64 GetHookID(const char*);
    std::string GetError() const;
private:
	 // Hook map
    std::unordered_map<const char*, Uint64> hook;
	 // Error string
    std::string error = "";
};
} // TFC

#endif // EVENTHOOKMGR_H
