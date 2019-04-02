#ifndef DISPLAY_H
#define DISPLAY_H

#include "../event/EventHook.h"
#include "../TFC_header.h"
#include "Image.h"
#include "Canvas.h"

#include <mutex>
#include <atomic>
#include <string>
#include <thread>
#include <functional>

namespace TFC {
class Image;
namespace Display {
namespace DisplayData {
extern int sfps, rfps, stps, rtps;
extern bool stopFlag;
extern Uint64 fpsc, tpsc, cpuFreq;
extern SDL_Event event;
extern std::mutex eMutex, rMutex;
extern std::string error;
} // DisplayData
 // Display method
using VVF = std::function<void()>;
 // Control
void SetFPS(int);
void SetTPS(int);
void FreshDisplay();
void StartMainLoop(VVF, VVF);
void StopMainLoop();
 // Image
bool DisplayImage(Image&, int, int, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, int, int);
bool DisplayImage(Image&, int, int);
} // Display
} // TFC

#endif // DISPLAY_H
