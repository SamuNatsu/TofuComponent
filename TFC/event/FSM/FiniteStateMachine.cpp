#include "FiniteStateMachine.h"

namespace TFC {

FiniteStateMachine::FiniteStateMachine() {}

FiniteStateMachine::~FiniteStateMachine() {}

/*=================================================
 *Function name : RegisterState
 *Parameter :
 *  const char *name : The custom name of the state
 *  const BaseState& state : The state structure
 *Description : Register a state
 *Return : TRUE on success, FALSE on error
 ================================================*/
bool FiniteStateMachine::RegisterState(const char *name, BaseState &state) {
  //If name used
  if (IsStateExists(name)) {
    error_ = "Name exists";
    return false;
  }
  //Store the state
  stateMap_[name] = &state;
  //Return success
  return true;
}

/*=================================================
 *Function name : DeleteState
 *Parameter :
 *  const char *name : The custom name of the state
 *Description : Delete a state
 ================================================*/
void FiniteStateMachine::DeleteState(const char *name) {
  //Delete
  stateMap_.erase(name);
}

/*=================================================
 *Function name : Reset
 *Parameter :
 *  const char *name : The custom name of the state
 *Description : Reset FSM
 ================================================*/
bool FiniteStateMachine::Reset(const char *name) {
  //If not found
  if (!IsStateExists(name)) {
    error_ = "Invalid name";
    return false;
  }
  //Set FSM state
  nowState_ = stateMap_.find(name);
  //Return success
  return true;
}

/*========================
 *Function name : Update
 *Description : Update FSM
 =======================*/
void FiniteStateMachine::Update() {
  //Update
  nowState_->second->Update();
}

/*===========================
 *Function name : Input
 *Description : Process input
 ==========================*/
void FiniteStateMachine::Input(const uint64_t input) {
  //Process input
  nowState_->second->Input(*this, input);
}

/*=================================================
 *Function name : Transition
 *Parameter :
 *  const char *name : The custom name of the state
 *Description : State transition
 *Return : TRUE on success, FALSE on error
 ================================================*/
bool FiniteStateMachine::Transition(const char *name) {
  //If no found
  if (!IsStateExists(name)) {
    error_ = "Invalid name";
    return false;
  }
  //Transition
  nowState_->second->Exit();
  nowState_ = stateMap_.find(name);
  nowState_->second->Enter();
  //Return success
  return true;
}

/*==============================
 *Function name : GetError
 *Description : Get error string
 *Return : Error string
 =============================*/
std::string FiniteStateMachine::GetError() const {
  //Return query
  return error_;
}

/*=================================================
 *Function name : IsStateExists
 *Parameter :
 *  const char *name : The custom name of the state
 *Description : Return whether the state is existed
 *Return : TRUE on existed, FALSE on not existed
 ================================================*/
bool FiniteStateMachine::IsStateExists(const char *name) {
  return stateMap_.find(name) != stateMap_.end();
}

}
