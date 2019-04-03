#include "EventHook.h"

namespace TFC {
namespace EventHook {
namespace EventHookData {
Uint64 hookCounter = 0;
std::unordered_map<Uint64, STF> hook;
std::string error = "";
} // EventHookData
Uint64 AddHook(SDL_EventType eventType, VVF hookFunction) {
     // Add hook
    EventHookData::hook[++EventHookData::hookCounter] = (STF){eventType, hookFunction};
     // Return index
    return EventHookData::hookCounter;
}

bool IsHookExists(Uint64 index) {
     // Return request
    return EventHookData::hook.find(index) != EventHookData::hook.end();
}

void RemoveHook(Uint64 index) {
     // Delete hook
    EventHookData::hook.erase(index);
}

void CallAllHook(SDL_EventType type) {
    for (auto& i : EventHookData::hook) {
        if (i.second.type == type) {
            i.second.hookFunction();
        }
    }
}

void CallAllHook() {
    CallAllHook(static_cast<SDL_EventType>(Display::DisplayData::event.type));
}

bool CallHook(Uint64 index) {
     // If is not exist
    if (!IsHookExists(index)) {
        EventHookData::error = "Invalid index";
        return false;
    }
     // Call hook
    EventHookData::hook[index].hookFunction();
     // Return success
    return true;
}
} // EventHook
} // TFC
