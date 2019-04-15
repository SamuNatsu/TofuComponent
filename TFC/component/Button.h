/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Button.h
 *Description : A button component
 *Version : 1.0
 ************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include "../event/EventHookMgr.h"
#include "../graph/Canvas.h"
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
  //Register
  bool RegisterButton(const char*, const int, const int, const int, const int, const VVF, const VVF, const VVF, const VVF);
  //Delete
  void DeleteButton(const char*);
  //Enable & Disable
  bool EnableButton(const char*);
  bool DisableButton(const char*);
  //Get attribute
  std::string GetError() const;
  bool IsButtonExists(const char*) const;
  bool IsEnabled(const char*);
  //Debug
  bool DrawDebugLayer();
private:
  //Buttons
  std::unordered_map<std::string, BTN> buttons_;
  //Error string
  std::string error_ = "";
  //Internal using function
  bool IsInRangeHover(BTN&) const;
  bool IsInRangePress(BTN&) const;
};

}

#endif // BUTTON_H
