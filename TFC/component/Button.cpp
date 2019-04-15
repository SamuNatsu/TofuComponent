#include "Button.h"

namespace TFC {

Button::Button() {}

Button::~Button() {}

/*======================================================
 *Function name : RegisterButton
 *Parameter :
 *  const char *name : The custom name of the button
 *  const int x1 : The left-top X
 *  const int y1 : The left-top Y
 *  const int x2 : The right-button X
 *  const int y2 : The right-button Y
 *  const Button::VVF hover : The action while mouse hover
 *  const Button::VVF press : The action while mouse press
 *  const Button::VVF release : The action while mouse release
 *  const Button::VVF leave : The action while mouse leave
 *Description : Register a button
 *Return : TRUE on success, FALSE on error
 =====================================================*/
bool Button::RegisterButton(const char *name,
                            const int x1, const int y1, const int x2, const int y2,
                            const Button::VVF hover, const Button::VVF press, const Button::VVF release, const Button::VVF leave) {
  //If name used
  if (IsButtonExists(name)) {
    error_ = "The name has been used";
    return false;
  }
  //Create button
  buttons_[name].enabled = buttons_[name].pressed = false;
  buttons_[name].x1 = x1;
  buttons_[name].y1 = y1;
  buttons_[name].x2 = x2;
  buttons_[name].y2 = y2;
  buttons_[name].hookMgr.AddHook(
    "Hover&Leave",
    SDL_MOUSEMOTION,
    [this, name, hover, leave]() {
      static std::string nameStr = name;
      static VVF hoverFunction = hover;
      static VVF leaveFunction = leave;
      if (buttons_[nameStr.c_str()].enabled && !buttons_[nameStr.c_str()].pressed) {
        if (IsInRangeHover(buttons_[name])) {
          hoverFunction();
        }
        else {
          leaveFunction();
        }
      }
    }
  );
  buttons_[name].hookMgr.AddHook(
    "Press",
    SDL_MOUSEBUTTONDOWN,
    [this, name, press]() {
      static std::string nameStr = name;
      static VVF pressFunction = press;
      if (buttons_[nameStr.c_str()].enabled && IsInRangePress(buttons_[name])) {
        buttons_[nameStr.c_str()].pressed = true;
        pressFunction();
      }
    }
  );
  buttons_[name].hookMgr.AddHook(
    "Release&Hover",
    SDL_MOUSEBUTTONUP,
    [this, name, release, hover]() {
      static std::string nameStr = name;
      static VVF releaseFunction = release;
      static VVF hoverFunction = hover;
      if (buttons_[nameStr.c_str()].enabled && IsInRangePress(buttons_[name])) {
        buttons_[nameStr.c_str()].pressed = false;
        releaseFunction();
        hoverFunction();
      }
    }
  );
  //Initialize button
  EventHook::CallHook(buttons_[name].hookMgr.GetHookID("Hover&Leave"));
  EventHook::CallHook(buttons_[name].hookMgr.GetHookID("Press"));
  EventHook::CallHook(buttons_[name].hookMgr.GetHookID("Release&Hover"));
  buttons_[name].enabled = true;
  //Return success
  return true;
}

/*==================================================
 *Function name : DeleteButton
 *Parameter :
 *  const char *name : The custom name of the button
 *Description : Delete a button
 =================================================*/
void Button::DeleteButton(const char *name) {
  //Delete
  buttons_.erase(name);
}

/*==================================================
 *Function name : EnableButton
 *Parameter :
 *  const char *name : The custom name of the button
 *Description : Enable a button
 *Return : TRUE on success, FALSE on error
 =================================================*/
bool Button::EnableButton(const char *name) {
  //If not found
  if (!IsButtonExists(name)) {
    error_ = "Button not found";
    return false;
  }
  //Enable
  buttons_[name].enabled = true;
  //Return success
  return true;
}

/*==================================================
 *Function name : DisableButton
 *Parameter :
 *  const char *name : The custom name of the button
 *Description : Disable a button
 *Return : TRUE on success, FALSE on error
 =================================================*/
bool Button::DisableButton(const char *name) {
  //If not found
  if (!IsButtonExists(name)) {
    error_ = "Button not found";
    return false;
  }
  //Disable
  buttons_[name].enabled = false;
  //Return success
  return true;
}

/*=================================
 *Function name : GetError
 *Description : Return error string
 *Return : Error string
 ================================*/
std::string Button::GetError() const {
  //Return query
  return error_;
}

/*==================================================
 *Function name : IsButtonExists
 *Parameter :
 *  const char *name : The custom name of the button
 *Description : Return whether the button is existed
 *Return : TRUE on existed, FALSE on not existed
 =================================================*/
bool Button::IsButtonExists(const char *name) const {
  //Return query
  return buttons_.find(name) != buttons_.end();
}

/*====================================================
 *Function name : IsEnabled
 *Parameter :
 *  const char *name : The custom name of the button
 *Description : Return whether the button is enabled
 *Return : TRUE on enabled, FALSE on disabled or error
 ===================================================*/
bool Button::IsEnabled(const char *name) {
  //If not found
  if (!IsButtonExists(name)) {
    error_ = "Button not found";
    return false;
  }
  //Return query
  return buttons_[name].enabled;
}

/*====================================================
 *Function name : DrawDebugLayer
 *Description : Draw debug layer
 *Return : TRUE on success, FALSE on error
 ===================================================*/
bool Button::DrawDebugLayer() {
  //Record default renderer color
  Uint8 r, g, b, a;
  if (!TFC::Canvas::GetDrawColor(r, g, b, a)) {
    error_ = TFC::Canvas::CanvasData::error;
    return false;
  }
  //Draw rectangles for every button
  for (auto& i : buttons_) {
    if (i.second.enabled) {
      TFC::Canvas::SetDrawColor(0x0, 0xFF, 0x0);
      TFC::Canvas::DrawRect(i.second.x1, i.second.y1, i.second.x2 - i.second.x1, i.second.y2 - i.second.y1);
    }
    else {
      TFC::Canvas::SetDrawColor(0xFF, 0x0, 0x0);
      TFC::Canvas::DrawRect(i.second.x1, i.second.y1, i.second.x2 - i.second.x1, i.second.y2 - i.second.y1);
    }
  }
  //Set renderer color to default
  if (!TFC::Canvas::SetDrawColor(r, g, b, a)) {
    error_ = TFC::Canvas::CanvasData::error;
    return false;
  }
  //Return success
  return true;
}

/*==========================================================
 *Function name : IsInRangeHover
 *Parameter :
 *  Button::BTN &button : Button structure
 *Description : Return whether the button in detecting range
 *Return : TRUE on detected, FALSE on not detected
 ========================================================*/
bool Button::IsInRangeHover(Button::BTN &button) const {
    return button.x1 <= TFC::Display::DisplayData::event.motion.x && button.x2 >= TFC::Display::DisplayData::event.motion.x && button.y1 <= TFC::Display::DisplayData::event.motion.y && button.y2 >= TFC::Display::DisplayData::event.motion.y;
}

/*==========================================================
 *Function name : IsInRangePress
 *Parameter :
 *  Button::BTN &button : Button structure
 *Description : Return whether the button in detecting range
 *Return : TRUE on detected, FALSE on not detected
 ========================================================*/
bool Button::IsInRangePress(Button::BTN &button) const {
    return button.x1 <= TFC::Display::DisplayData::event.button.x && button.x2 >= TFC::Display::DisplayData::event.button.x && button.y1 <= TFC::Display::DisplayData::event.button.y && button.y2 >= TFC::Display::DisplayData::event.button.y;
}

}
