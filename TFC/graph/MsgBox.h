#ifndef MSGBOX_H
#define MSGBOX_H

#include "../TFC_header.h"

#include <string>

namespace TFC {
namespace MsgBox {
namespace MsgBoxData {
extern std::string error;
} // MsgBoxData
 //Preset Message Box
bool InfoMsgBox(const char*, const char*, SDL_Window* = nullptr);
bool WarnMsgBox(const char*, const char*, SDL_Window* = nullptr);
bool ErrorMsgBox(const char*, const char*, SDL_Window* = nullptr);
 //Custom Message Box
 /*Comming soon*/
} //MsgBox
} // TFC

#endif // MSGBOX_H
