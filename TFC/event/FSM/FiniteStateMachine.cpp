#include "FiniteStateMachine.h"

namespace TFC {
namespace FSM {
FiniteStateMachine::FiniteStateMachine() {}

FiniteStateMachine::~FiniteStateMachine() {}

bool FiniteStateMachine::RegisterState(const char* name, BaseState& state) {
    if (IsStateExists(name)) {
        error = "Name exists";
        return false;
    }

    stateMap[name] = &state;

    return true;
}

bool FiniteStateMachine::IsStateExists(const char* name) {
    return stateMap.find(name) != stateMap.end();
}

void FiniteStateMachine::DeleteState(const char* name) {
    stateMap.erase(name);
}

bool FiniteStateMachine::Reset(const char* name) {
    if (!IsStateExists(name)) {
        error = "Invalid name";
        return false;
    }

    nowState = stateMap.find(name);

    return true;
}

void FiniteStateMachine::Update() {
    nowState->second->Update();
}

void FiniteStateMachine::Input(Uint64 input) {
    nowState->second->Input(*this, input);
}

bool FiniteStateMachine::Transition(const char* name) {
    if (!IsStateExists(name)) {
        error = "Invalid name";
        return false;
    }

    nowState->second->Exit();
    nowState = stateMap.find(name);
    nowState->second->Enter();

    return true;
}

std::string FiniteStateMachine::GetError() const {
    return error;
}
} // FSM
} // TFC
