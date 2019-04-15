#ifndef DISPLAY_H
#define DISPLAY_H

#include "../event/EventHook.h"
#include "../TFC_header.h"
#include "Image.h"
#include "Canvas.h"
#include "AnimateImage.h"

namespace TFC {
class Image;
namespace Display {
namespace DisplayData {
namespace RenderData {
extern std::atomic<uint64_t> startc, endc;
}
extern int sfps, rfps, stps, rtps;
extern bool stopFlag;
extern Uint64 fpsc, tpsc, cpuFreq;
extern SDL_Event event;
extern std::mutex eMutex, rMutex;
extern std::string error;
}
 // Display method
using VVF = std::function<void()>;
 // Control
void SetFPS(int);
void SetTPS(int);
void FreshDisplay();
void StartMainLoop(VVF, VVF);
void StopMainLoop();
//AnimateImage
bool DisplayAnimate(AnimateImage&, int, int, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayAnimate(AnimateImage&, int, int, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayAnimate(AnimateImage&, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayAnimate(AnimateImage&, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayAnimate(AnimateImage&, int, int, int, int);
bool DisplayAnimate(AnimateImage&, int, int);
// Image
bool DisplayImage(Image&, int, int, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool DisplayImage(Image&, int, int, int, int);
bool DisplayImage(Image&, int, int);
}
}

#endif // DISPLAY_H
