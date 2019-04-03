#include "EventHookMgr.h"

namespace TFC {
EventHookMgr::EventHookMgr() {}

EventHookMgr::~EventHookMgr() {
	 // Delete hook
    RemoveAllHook();
}

bool EventHookMgr::AddHook(const char* name, SDL_EventType type, VVF hookFunction) {
	 // If is exist
    if (IsHookExists(name)) {
        error = "Name existed";
        return false;
    }
	 // Add hook
    hook[name] = EventHook::AddHook(type, hookFunction);
	 // Return success
    return true;
}

bool EventHookMgr::IsHookExists(const char* name) {
    return hook.find(name) != hook.end();
}

void EventHookMgr::RemoveAllHook() {
    for (auto& i : hook) {
        EventHook::RemoveHook(i.second);
    }

    hook.clear();
}

bool EventHookMgr::RemoveHook(const char* name) {
    if (!IsHookExists(name)) {
        error = "Invalid name";
        return false;
    }

    EventHook::RemoveHook(hook[name]);
    hook.erase(name);

    return true;
}

Uint64 EventHookMgr::GetHookID(const char* name) {
    if (!IsHookExists(name)) {
        error = "Invalid name";
        return 0;
    }

    return hook[name];
}

std::string EventHookMgr::GetError() const {
    return error;
}
} // TFC
