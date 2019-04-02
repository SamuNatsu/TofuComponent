#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include "../../graph/Display.h"
#include "../../TFC_header.h"
#include "BaseState.h"

#include <string>
#include <unordered_map>

namespace TFC {
namespace FSM {
class BaseState;
class FiniteStateMachine {
public:
     // Construction & Destruction
    FiniteStateMachine();
    ~FiniteStateMachine();
     // Register & Delete
    bool RegisterState(const char*, BaseState&);
    bool IsStateExists(const char*);
    void DeleteState(const char*);
     // Control
    bool Reset(const char*);
    void Update();
    void Input(Uint64);
    bool Transition(const char*);
     // Get
    std::string GetError() const;
private:
    std::unordered_map<const char*, BaseState*>::iterator nowState;
    std::unordered_map<const char*, BaseState*> stateMap;
    std::string error = "";
};
} // FSM
} // TFC

#endif // FINITESTATEMACHINE_H
