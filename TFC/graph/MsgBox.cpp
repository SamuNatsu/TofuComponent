#include "MsgBox.h"

namespace TFC {
namespace MsgBox{
namespace MsgBoxData {
std::string error = "";
} // MsgBoxData
bool InfoMsgBox(const char* title,const char* msg, SDL_Window* window) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, msg, window) < 0) {
        MsgBoxData::error = SDL_GetError();
        return false;
    }
    return true;
}

bool WarnMsgBox(const char* title,const char* msg, SDL_Window* window) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, msg, window) < 0) {
        MsgBoxData::error = SDL_GetError();
        return false;
    }
    return true;
}

bool ErrorMsgBox(const char* title,const char* msg, SDL_Window* window) {
    if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, msg, window) < 0) {
        MsgBoxData::error = SDL_GetError();
        return false;
    }
    return true;
}
} // MsgBox
} // TFC
