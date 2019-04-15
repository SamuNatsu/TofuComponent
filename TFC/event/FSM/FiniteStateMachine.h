/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : FiniteStateMachine.h
 *Description : A finite state machine structure
 *Version : 1.0
 ************************************************/

#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include "BaseState.h"
#include "../../TFC_header.h"

namespace TFC {

class BaseState;

class FiniteStateMachine {
 public:
  //Constructor & Destructor
  FiniteStateMachine();
  ~FiniteStateMachine();
  //Register
  bool RegisterState(const char*, BaseState&);
  //Delete
  void DeleteState(const char*);
  //Control
  bool Reset(const char*);
  void Update();
  void Input(const uint64_t);
  bool Transition(const char*);
  //Get attribute
  std::string GetError() const;
  bool IsStateExists(const char*);
 private:
  //FSM state now
  std::unordered_map<const char*, BaseState*>::iterator nowState_;
  //States
  std::unordered_map<const char*, BaseState*> stateMap_;
  //Error string
  std::string error_ = "";
};

}

#endif // FINITESTATEMACHINE_H
