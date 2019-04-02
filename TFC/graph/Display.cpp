#include "Display.h"

namespace TFC {
namespace Display {
namespace DisplayData {
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

    std::thread rTrd(
        [&](){
            Uint64 startc = SDL_GetPerformanceCounter(), endc = 0;
            DisplayData::event.type = 0;

            while(!DisplayData::stopFlag) {
                std::unique_lock<std::mutex> lock(DisplayData::rMutex);

                SDL_RenderClear(TFC::Canvas::CanvasData::renderer);
                _RF();

                endc = SDL_GetPerformanceCounter();
                if(startc + DisplayData::fpsc >= endc) {
                    DisplayData::rfps = DisplayData::sfps;
                    startc += DisplayData::fpsc;
                    SDL_Delay(1000.0 * (startc - endc) / DisplayData::cpuFreq);
                    do {
                        endc = SDL_GetPerformanceCounter();
                    }
                    while(startc >= endc);
                }
                else {
                    DisplayData::rfps = static_cast<double>(DisplayData::cpuFreq) / (endc - startc);
                }
                startc = SDL_GetPerformanceCounter();
            }
        });

    Uint64 startc = SDL_GetPerformanceCounter(), endc = 0;

    while(!DisplayData::stopFlag) {
        if (SDL_PollEvent(&DisplayData::event) > 0) {
            EventHook::CallAllHook();
            DisplayData::event.type = 0;
        }

        _EF();

        endc = SDL_GetPerformanceCounter();
        if(startc + DisplayData::tpsc >= endc) {
            DisplayData::rtps = DisplayData::stps;
            startc += DisplayData::tpsc;
            SDL_Delay(1000.0 * (startc - endc) / DisplayData::cpuFreq);
            do {
                endc = SDL_GetPerformanceCounter();
            }
            while(startc >= endc);
        }
        else {
            DisplayData::rtps = static_cast<double>(DisplayData::cpuFreq) / (endc - startc);
        }
        startc = SDL_GetPerformanceCounter();
    }

    if (rTrd.joinable()) {
        rTrd.join();
    }
}

void StopMainLoop() {
    DisplayData::stopFlag = true;
}

bool DisplayImage(Image& img, int x, int y, int w, int h, double angle, int cx, int cy, SDL_RendererFlip flip){
    SDL_Rect r = {x, y, w, h};
    SDL_Point p = {cx, cy};
    if (SDL_RenderCopyEx(TFC::Canvas::CanvasData::renderer, img.GetTexture(), nullptr, &r, angle, &p, flip) < 0) {
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
    SDL_Rect r = {x, y, w, h};
    if (SDL_RenderCopy(TFC::Canvas::CanvasData::renderer, img.GetTexture(), nullptr, &r) < 0) {
        DisplayData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DisplayImage(Image& img, int x, int y) {
    return DisplayImage(img, x, y, img.GetWidth(), img.GetHeight());
}
} // Display
} // TFC
