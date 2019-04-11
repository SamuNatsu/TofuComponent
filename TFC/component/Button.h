/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Button.h
 *Description : A button component
 *Version : 1.0
 ************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include "../event/FSM/BaseState.h"
#include "../event/FSM/FiniteStateMachine.h"
#include "../event/EventHookMgr.h"
#include "../graph/Canvas.h"
#include "../graph/Display.h"
#include "../TFC_header.h"

namespace TFC {
class Button {
 //Internal using type
 using VVF = std::function<void()>;
 using BTN = struct {
              bool enabled, pressed;
              int x1, y1, x2, y2;
              TFC::EventHookMgr hookMgr;
             };
 public:
  //Constructor & Destructor
  Button();
  ~Button();
  //Manage
  bool RegisterButton(const char*, int, int, int, int, VVF, VVF, VVF, VVF);
  bool DeleteButton(const char*);
  bool EnableButton(const char*);
  bool IsEnabled(const char*);
  bool DisableButton(const char*);
  bool DrawDebugLayer();
  //Get
  std::string GetError() const;
private:
  std::unordered_map<std::string, BTN> buttons;
  std::string error = "";
  //Internal using function
  bool IsInRangeHover(BTN&) const;
  bool IsInRangePress(BTN&) const;
};
} // TFC

#endif // BUTTON_H
