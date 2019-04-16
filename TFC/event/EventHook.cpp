#include "EventHook.h"

namespace TFC {
namespace EventHook {
namespace EventHookData {
uint64_t hookCounter = 0;
std::unordered_map<uint64_t, STF> hook;
std::string error = "";
}

/*=============================================================
 *Function name : AddHook
 *Parameter :
 *  const SDL_EventType eventType : Which kind event to hook on
 *  const VVF hookFunction : Hook function
 *Description : Add a hook
 *Return : The index of the hook
 ============================================================*/
uint64_t AddHook(const SDL_EventType eventType, const VVF hookFunction) {
  //Create hook
  EventHookData::hook[++EventHookData::hookCounter] = (STF){eventType, hookFunction};
  //Return index
  return EventHookData::hookCounter;
}

/*==============================================
 *Function name : RemoveHook
 *Parameter :
 *  const uint64_t index : The index of the hook
 *Description : Delete a hook
 =============================================*/
void RemoveHook(const uint64_t index) {
  //Delete
  EventHookData::hook.erase(index);
}

/*=====================================================
 *Function name : CallAllHook
 *Parameter :
 *  const SDL_EventType type : Which kind event to call
 *Description : Call all the hooks by a certain type
 ===============================================-====*/
void CallAllHook(const SDL_EventType type) {
  //Scan all hooks
  for (auto &i : EventHookData::hook) {
    if (i.second.type == type) {
      i.second.hookFunction();
    }
  }
}

/*=====================================================
 *Function name : CallAllHook
 *Description : Call all the hooks by global event type
 ====================================================*/
void CallAllHook() {
  //Call hooks
  CallAllHook(static_cast<SDL_EventType>(Display::DisplayData::event.type));
}

/*==============================================
 *Function name : CallHook
 *Parameter :
 *  const uint64_t index : The index of the hook
 *Description : Call a hook by index
 *Return : TRUE on success, FALSE on error
 =============================================*/
bool CallHook(const uint64_t index) {
  //If not found
  if (!IsHookExists(index)) {
    EventHookData::error = "Invalid index";
    return false;
  }
  //Call hook
  EventHookData::hook[index].hookFunction();
  //Return success
  return true;
}

/*===============================================
 *Function name : IsHookExists
 *Parameter :
 *  const uint64_t index : The index of the hook
 *Description : Return whether a index is existed
 *Return : TRUE on existed, FALSE on not existed
 ==============================================*/
bool IsHookExists(const uint64_t index) {
  //Return query
  return EventHookData::hook.find(index) != EventHookData::hook.end();
}

}

void TFC_HOOK_QUIT() {
  TFC::Display::StopMainLoop();
}

} // TFC
