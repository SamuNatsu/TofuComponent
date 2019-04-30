/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Canvas.h
 *Version : 1.0
 ************************************************/

#ifndef TFC_GRAPH_CANVAS_H
#define TFC_GRAPH_CANVAS_H

#include "../TFC_header.h"

namespace TFC {
namespace Canvas {
namespace Data {
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern std::string error;
}
//Initialize & Quit
bool Initialize();
void Quit();
//Create & Destroy
bool Create(const char*, const int, const int, const uint32_t = 0, const int = -1);
bool IsCreated();
void Destroy();
//Renderer
bool RendererClear();
void RendererFresh();
bool GetDrawColor(uint8_t&, uint8_t&, uint8_t&, uint8_t&);
bool SetDrawColor(const uint8_t, const uint8_t, const uint8_t, const uint8_t = 255);
bool DrawLine(const int, const int, const int, const int);
bool DrawRect(const int, const int, const int, const int);
bool DrawPoint(const int, const int);
bool FillRect(const int, const int, const int, const int);
bool ScreenShot(const int, const int, const int, const int, const char*);
 bool ScreenShot(const char*);
 // Window
void HideWindow();
void ShowWindow();
void RaiseWindow();
void RestoreWindow();
void MaximizeWindow();
void MinimizeWindow();
bool SetWindowIcon(const char*);
}
}

#endif // TFC_GRAPH_CANVAS_H
