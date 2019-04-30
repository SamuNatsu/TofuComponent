/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Director.h
 *Version : 1.0
 ************************************************/

#ifndef TFC_COMPONENT_DIRECTOR_H
#define TFC_COMPONENT_DIRECTOR_H

#include "../TFC_header.h"

namespace TFC {
namespace Director {
namespace Data {
extern uint64_t rTickS, rTickE;
extern bool stopFlag;
extern SDL_Event event;
extern uint32_t sFPS, rFPS, sTPS, rTPS;
extern uint64_t cFPS, cTPS;
extern std::string error;
}
//Internal using type
using VVF = std::function<void()>;
//Settings
void SetFPS(int);
void SetTPS(int);
//Controlling
void StartMainLoop(VVF, VVF);
void StopMainLoop();
}
}

#endif // TFC_COMPONENT_DIRECTOR_H
