#include "EventHookMgr.h"

namespace TFC {

EventHookMgr::EventHookMgr() {}

EventHookMgr::~EventHookMgr() {
    RemoveAllHook();
}

/*=============================================================
 *Function name : AddHook
 *Parameter :
 *  const char* name : The custom name of the hook
 *  const SDL_EventType eventType : Which kind event to hook on
 *  const VVF hookFunction : Hook function
 *Description : Add a hook
 *Return : TRUE on success, FALSE on error
 ============================================================*/
bool EventHookMgr::AddHook(const char *name, const SDL_EventType type, const VVF hookFunction) {
  //If name used
  if (IsHookExists(name)) {
    error_ = "Name existed";
    return false;
  }
  //Create hook
  hook_[name] = EventHook::AddHook(type, hookFunction);
  //Return success
  return true;
}

/*==============================
 *Function name : RemoveAllHook
 *Description : Remove all hooks
 =============================*/
void EventHookMgr::RemoveAllHook() {
  //Scan all hooks
  for (auto &i : hook_) {
    EventHook::RemoveHook(i.second);
  }
  //Clear hooks
  hook_.clear();
}

/*================================================
 *Function name : RemoveHook
 *Parameter :
 *  const char* name : The custom name of the hook
 *Description : Delete a hook
 *Return : TRUE on success, FALSE on error
 ===============================================*/
bool EventHookMgr::RemoveHook(const char *name) {
  //If not found
  if (!IsHookExists(name)) {
    error_ = "Invalid name";
    return false;
  }
  //Delete
  EventHook::RemoveHook(hook_[name]);
  hook_.erase(name);
  //Return success
  return true;
}

/*=================================
 *Function name : GetError
 *Description : Return error string
 *Return : Error string
 ================================*/
std::string EventHookMgr::GetError() const {
    return error_;
}

/*=========================================================
 *Function name : GetHookID
 *Parameter :
 *  const char* name : The custom name of the hook
 *Description : Return the index of the hook by custom name
 *Return : Positive number on success, 0 on error
 ========================================================*/
uint64_t EventHookMgr::GetHookID(const char *name) {
  //If not found
  if (!IsHookExists(name)) {
    error_ = "Invalid name";
    return 0;
  }
  //Return query
  return hook_[name];
}

/*================================================
 *Function name : IsHookExists
 *Parameter :
 *  const char* name : The custom name of the hook
 *Description : Return whether the hook is existed
 *Return : TRUE on existed, FALSE on not existed
 ===============================================*/
bool EventHookMgr::IsHookExists(const char *name) {
  //Return query
  return hook_.find(name) != hook_.end();
}

} // TFC
