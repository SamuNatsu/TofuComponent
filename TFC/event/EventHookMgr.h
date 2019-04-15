/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : EventHookMgr.h
 *Description : Manage a set of hooks
 *Version : 1.0
 ************************************************/

#ifndef EVENTHOOKMGR_H
#define EVENTHOOKMGR_H

#include "EventHook.h"
#include "../TFC_header.h"

namespace TFC {

class EventHookMgr {
//Internal using type
using VVF = std::function<void()>;
 public:
  //Construction & Destruction
  EventHookMgr();
  ~EventHookMgr();
  //Add
  bool AddHook(const char*, const SDL_EventType, const VVF);
  //Remove
  void RemoveAllHook();
  bool RemoveHook(const char*);
  //Get
  std::string GetError() const;
  uint64_t GetHookID(const char*);
  bool IsHookExists(const char*);
 private:
  //Hooks
  std::unordered_map<const char*, uint64_t> hook_;
  //Error string
  std::string error_ = "";
};

}

#endif // EVENTHOOKMGR_H
