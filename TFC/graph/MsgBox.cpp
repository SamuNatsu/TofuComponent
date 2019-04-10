#include "MsgBox.h"

namespace TFC {
namespace MsgBox{
namespace MsgBoxData {
std::string error = "";
}

/*==============================================
 *Function name : Information
 *Parameter :
 *  const char *title : The title string
 *  const char *msg : The message string
 *  SDL_Window *window : The parent window
 *Description : Show the information message box
 *Return : TRUE on success, FALSE on error
 =============================================*/
bool Information(const char *title, const char *msg, SDL_Window *window) {
  //If show message box failed
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, msg, window) < 0) {
    MsgBoxData::error = SDL_GetError();
    return false;
  }
  //Return success
  return true;
}

/*==========================================
 *Function name : Warning
 *Parameter :
 *  const char *title : The title string
 *  const char *msg : The message string
 *  SDL_Window *window : The parent window
 *Description : Show the warning message box
 *Return : TRUE on success, FALSE on error
 =========================================*/
bool Warning(const char *title, const char *msg, SDL_Window *window) {
  //If show message box failed
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, msg, window) < 0) {
    MsgBoxData::error = SDL_GetError();
    return false;
  }
  //Return success
  return true;
}

/*========================================
 *Function name : Error
 *Parameter :
 *  const char *title : The title string
 *  const char *msg : The message string
 *  SDL_Window *window : The parent window
 *Description : Show the error message box
 *Return : TRUE on success, FALSE on error
 =======================================*/
bool Error(const char *title, const char *msg, SDL_Window *window) {
  //If show message box failed
  if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, msg, window) < 0) {
    MsgBoxData::error = SDL_GetError();
    return false;
  }
  //Return success
  return true;
}

}
}
