#include "Display.h"

namespace {

void EventLoop(TFC::Display::VVF eventFunvtion) {
  TFC::Display::DisplayData::event.type = 0;
  uint64_t startc = SDL_GetPerformanceCounter(), endc = 0;
  while(!TFC::Display::DisplayData::stopFlag) {
    if (SDL_PollEvent(&TFC::Display::DisplayData::event) > 0) {
      TFC::EventHook::CallAllHook();
      TFC::Display::DisplayData::event.type = 0;
    }
    eventFunvtion();
    endc = SDL_GetPerformanceCounter();
    if(startc + TFC::Display::DisplayData::tpsc >= endc) {
      TFC::Display::DisplayData::rtps = TFC::Display::DisplayData::stps;
      startc += TFC::Display::DisplayData::tpsc;
      SDL_Delay(1000.0 * (startc - endc) / TFC::Display::DisplayData::cpuFreq);
      do {
        endc = SDL_GetPerformanceCounter();
      }
      while(startc >= endc);
    }
    else {
      TFC::Display::DisplayData::rtps = static_cast<double>(TFC::Display::DisplayData::cpuFreq) / (endc - startc);
    }
    startc = SDL_GetPerformanceCounter();
  }
}

void RenderLoop(TFC::Display::VVF renderFunction) {
  while(!TFC::Display::DisplayData::stopFlag) {
    std::unique_lock<std::mutex> lock(TFC::Display::DisplayData::rMutex);

    SDL_RenderClear(TFC::Canvas::CanvasData::renderer);
    renderFunction();

    TFC::Display::DisplayData::RenderData::endc.store(SDL_GetPerformanceCounter());
    if(TFC::Display::DisplayData::RenderData::startc.load() + TFC::Display::DisplayData::fpsc >= endc) {
      TFC::Display::DisplayData::rfps = TFC::Display::DisplayData::sfps;
      startc += TFC::Display::DisplayData::fpsc;
      SDL_Delay(1000.0 * (startc - endc) / TFC::Display::DisplayData::cpuFreq);
      do {
        endc = SDL_GetPerformanceCounter();
      }
      while(startc >= endc);
    }
    else {
      TFC::Display::DisplayData::rfps = static_cast<double>(TFC::Display::DisplayData::cpuFreq) / (endc - startc);
    }
    startc = SDL_GetPerformanceCounter();
  }
}

}

namespace TFC {
namespace Display {
namespace DisplayData {
namespace RenderData {
std::atomic<uint64_t> startc(0), endc(0);
}
int sfps = 0, rfps = 0, stps = 0, rtps = 0;
bool stopFlag = true;
Uint64 fpsc = 0, tpsc = 0, cpuFreq = 0;
SDL_Event event;
std::mutex eMutex, rMutex;
std::string error = "";
} // DisplayData
void SetFPS(int fps) {
    DisplayData::sfps = fps;
    DisplayData::rfps = 0;

    if (DisplayData::cpuFreq == 0){
        DisplayData::cpuFreq = SDL_GetPerformanceFrequency();
    }

    DisplayData::fpsc = 1.0 / fps * DisplayData::cpuFreq;
}

void SetTPS(int tps) {
    DisplayData::stps = tps;
    DisplayData::rtps = 0;

    if (DisplayData::cpuFreq == 0){
        DisplayData::cpuFreq = SDL_GetPerformanceFrequency();
    }

    DisplayData::tpsc = 1.0 / tps * DisplayData::cpuFreq;
}

void FreshDisplay() {
    SDL_RenderPresent(TFC::Canvas::CanvasData::renderer);
}

void StartMainLoop(VVF _EF,VVF _RF) {
    DisplayData::stopFlag = false;

    std::thread rTrd(::RenderLoop);

  ::EventLoop(_EF);

  if (rTrd.joinable()) {
    rTrd.join();
  }
}

void StopMainLoop() {
    DisplayData::stopFlag = true;
}

bool DisplayImage(Image& img, int x, int y, int w, int h, double angle, int cx, int cy, SDL_RendererFlip flip){
    SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
    SDL_Point p = {cx, cy};
    if (SDL_RenderCopyEx(TFC::Canvas::CanvasData::renderer, img.GetTexture(), &rs, &r, angle, &p, flip) < 0) {
        DisplayData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DisplayImage(Image& img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, w, h, angle, img.GetWidth()>>1, img.GetHeight()>>1, flip);
}

bool DisplayImage(Image& img, int x, int y, double angle, int cx, int cy, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, img.GetWidth(), img.GetHeight(), angle, cx, cy, flip);
}

bool DisplayImage(Image& img, int x, int y, double angle, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, angle, img.GetWidth()>>1, img.GetHeight()>>1, flip);
}

bool DisplayImage(Image& img, int x, int y, int w,int h) {
    SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
    if (SDL_RenderCopy(TFC::Canvas::CanvasData::renderer, img.GetTexture(), &rs, &r) < 0) {
        DisplayData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DisplayImage(Image& img, int x, int y) {
    return DisplayImage(img, x, y, img.GetWidth(), img.GetHeight());
}

bool DisplayAnimate(AnimateImage& img, int x, int y, int w, int h, double angle, int cx, int cy, SDL_RendererFlip flip){
    SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
    SDL_Point p = {cx, cy};
    if (SDL_RenderCopyEx(TFC::Canvas::CanvasData::renderer, img.GetTexture(), &rs, &r, angle, &p, flip) < 0) {
        DisplayData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DisplayAnimate(AnimateImage& img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, w, h, angle, img.GetWidth()>>1, img.GetHeight()>>1, flip);
}

bool DisplayAnimate(AnimateImage& img, int x, int y, double angle, int cx, int cy, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, img.GetWidth(), img.GetHeight(), angle, cx, cy, flip);
}

bool DisplayAnimate(AnimateImage& img, int x, int y, double angle, SDL_RendererFlip flip){
    return DisplayImage(img, x, y, angle, img.GetWidth()>>1, img.GetHeight()>>1, flip);
}

bool DisplayAnimate(AnimateImage& img, int x, int y, int w,int h) {
    SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
    if (SDL_RenderCopy(TFC::Canvas::CanvasData::renderer, img.GetTexture(), &rs, &r) < 0) {
        DisplayData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DisplayAnimate(AnimateImage& img, int x, int y) {
    return DisplayImage(img, x, y, img.GetWidth(), img.GetHeight());
}

}
}
