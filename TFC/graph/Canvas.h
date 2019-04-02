#ifndef CANVAS_H
#define CANVAS_H

#include "../TFC_header.h"
#include "MsgBox.h"

#include <string>

namespace TFC {
namespace Canvas {
namespace CanvasData {
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern std::string error;
} // CanvasData
 // Initialize & Quit
bool Initialize();
void Quit();
 // Create & Destroy
bool Create(const char*, int, int, Uint32 = 0);
bool IsCreated();
void Destroy();
 // Renderer
bool RendererClear();
void RendererFresh();
bool GetDrawColor(Uint8&, Uint8&, Uint8&, Uint8&);
bool SetDrawColor(Uint8, Uint8, Uint8, Uint8 = 255);
bool DrawLine(int, int, int, int);
bool DrawRect(int, int, int, int);
bool DrawPoint(int, int);
bool DrawPolygon(int, ...);
bool FillRect(int, int, int, int);
bool ScreenShot(int, int, int, int, const char*);
bool ScreenShot(const char*);
 // Window
void ShowWindow();
void HideWindow();
void RaiseWindow();
void MaximizeWindow();
void MinimizeWindow();
bool SetWindowIcon(const char*);
} // Canvas
} // TFC

#endif // CANVAS_H
