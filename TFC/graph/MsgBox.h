#ifndef MSGBOX_H
#define MSGBOX_H

#include <string>

#include "../TFC_header.h"

namespace TFC {
namespace MsgBox {
namespace MsgBoxData {
//Error string
extern std::string error;
}
//Preset Message Box
bool Information(const char*, const char*, SDL_Window* = nullptr); //Show information message box
bool Warning(const char*, const char*, SDL_Window* = nullptr); //Show warning message box
bool Error(const char*, const char*, SDL_Window* = nullptr); //Show error message box
}
}

#endif // MSGBOX_H
