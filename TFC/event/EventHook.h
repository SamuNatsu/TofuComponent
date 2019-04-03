#ifndef EVENTHOOK_H
#define EVENTHOOK_H

#include "../graph/Display.h"
#include "../TFC_header.h"

#include <string>
#include <functional>
#include <unordered_map>

namespace TFC {
namespace EventHook {
using VVF = std::function<void()>;
struct STF {
    SDL_EventType type;
    VVF hookFunction;
};
namespace EventHookData {
 // Hook counter
extern Uint64 hookCounter;
 // Hook map
extern std::unordered_map<Uint64, STF> hook;
 // Error string
extern std::string error;
} // EventHookData
 // Add & Remove
Uint64 AddHook(SDL_EventType, VVF);
bool IsHookExists(Uint64);
void RemoveHook(Uint64);
 // Call
void CallAllHook(SDL_EventType);
void CallAllHook();
bool CallHook(Uint64);
} // EventHook
} // TFC

#endif // EVENTHOOK_H
