/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : EventHook.h
 *Description : Some functions about hooking
 *Version : 1.0
 ************************************************/

#ifndef EVENTHOOK_H
#define EVENTHOOK_H

#include "../TFC_header.h"

namespace TFC {
namespace EventHook {
//Internal using type
using VVF = std::function<void()>;
using STF = struct {
             SDL_EventType type;
             VVF hookFunction;
            };
//Internal using data
namespace EventHookData {
//The non-decline counter of the hook
extern uint64_t hookCounter;
//Hooks
extern std::unordered_map<uint64_t, STF> hook;
//Error string
extern std::string error;
}
//Add
uint64_t AddHook(const SDL_EventType, const VVF);
//Remove
void RemoveHook(const uint64_t);
//Call
void CallAllHook(const SDL_EventType);
void CallAllHook();
bool CallHook(const uint64_t);
//Get attribute
bool IsHookExists(const uint64_t);
}
//Preset functions
void TFC_HOOK_QUIT();
}

#endif // EVENTHOOK_H
