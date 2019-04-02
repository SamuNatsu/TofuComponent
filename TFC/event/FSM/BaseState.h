#ifndef BASESTATE_H
#define BASESTATE_H

#include "FiniteStateMachine.h"

namespace TFC {
namespace FSM {
class FiniteStateMachine;
class BaseState {
public:
     // Interface
    BaseState();
    virtual ~BaseState();
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update() = 0;
    virtual void Input(FiniteStateMachine&, Uint64) = 0;
};
} // FSM
} // TFC

#endif // BASESTATE_H
