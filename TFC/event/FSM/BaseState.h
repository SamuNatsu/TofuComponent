/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : BaseState.h
 *Description : State interface
 *Version : 1.0
 ************************************************/

#ifndef BASESTATE_H
#define BASESTATE_H

#include "FiniteStateMachine.h"
#include "../../TFC_header.h"

namespace TFC {

class FiniteStateMachine;

class BaseState {
 public:
  //Constructor & Destructor
  BaseState();
  ~BaseState();
  //Action
  virtual void Enter() = 0;
  virtual void Exit() = 0;
  virtual void Update() = 0;
  virtual void Input(FiniteStateMachine&, const uint64_t) = 0;
};

}

#endif // BASESTATE_H
