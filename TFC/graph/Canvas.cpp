#include "Canvas.h"

namespace TFC {
namespace Canvas {
namespace CanvasData {
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
std::string error = "";
} // CanvasData
bool Initialize() {
    SDL_SetHint(SDL_HINT_IME_INTERNAL_EDITING, "1");

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2") == SDL_FALSE)
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        TFC::MsgBox::Error("Oops", SDL_GetError());
        return false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(flags) != flags) {
        TFC::MsgBox::Error("Oops", SDL_GetError());
        return false;
    }

    if(TTF_Init() < 0){
        TFC::MsgBox::Error("Oops", SDL_GetError());
        return false;
    }

    return true;
}

void Quit() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Create(const char* title, int w, int h, Uint32 flags) {
	Destroy();

    CanvasData::window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          w,
                                          h,
                                          SDL_WINDOW_HIDDEN | flags);
    if (CanvasData::window == nullptr) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    CanvasData::renderer = SDL_CreateRenderer(CanvasData::window,
                                              -1,
                                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (CanvasData::renderer == nullptr) {
        SDL_DestroyWindow(CanvasData::window);
        CanvasData::window = nullptr;
        CanvasData::error = SDL_GetError();
        return false;
    }

    if (SDL_SetRenderDrawBlendMode(CanvasData::renderer, SDL_BLENDMODE_BLEND) < 0) {
        SDL_DestroyWindow(CanvasData::window);
        SDL_DestroyRenderer(CanvasData::renderer);
        CanvasData::window = nullptr;
        CanvasData::renderer = nullptr;
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool IsCreated() {
    return CanvasData::window != nullptr;
}

void Destroy() {
    if (CanvasData::window != nullptr){
        SDL_DestroyWindow(CanvasData::window);
        SDL_DestroyRenderer(CanvasData::renderer);
        CanvasData::window = nullptr;
        CanvasData::renderer = nullptr;
        CanvasData::error = "";
    }
}

bool RendererClear() {
    if (SDL_RenderClear(CanvasData::renderer) < 0){
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

void RendererFresh() {
    SDL_RenderPresent(CanvasData::renderer);
}

bool GetDrawColor(Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a) {
    if (SDL_GetRenderDrawColor(CanvasData::renderer, &r, &g, &b, &a) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if(SDL_SetRenderDrawColor(CanvasData::renderer, r, g, b, a) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DrawLine(int x1, int y1, int x2, int y2) {
    if (SDL_RenderDrawLine(CanvasData::renderer, x1, y1, x2, y2) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DrawRect(int x, int y, int w, int h) {
    SDL_Rect r = {x, y, w, h};
    if (SDL_RenderDrawRect(CanvasData::renderer, &r) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DrawPoint(int x, int y) {
    if (SDL_RenderDrawPoint(CanvasData::renderer, x, y) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool DrawPolygon(int num, ...) {
    va_list vl;
    va_start(vl, num);

    SDL_Point a = va_arg(vl, SDL_Point);
    SDL_Point b = va_arg(vl, SDL_Point);

    for (int i = 1; i < num; ++i) {
        if (!DrawLine(a.x, a.y, b.x, b.y)) {
            CanvasData::error = SDL_GetError();
            va_end(vl);
            return false;
        }
        else {
            a = b;
            b = va_arg(vl, SDL_Point);
        }
    }

    va_end(vl);

    return true;
}

bool FillRect(int x, int y, int w, int h) {
    SDL_Rect r = {x, y, w, h};
    if (SDL_RenderFillRect(CanvasData::renderer, &r) < 0) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    return true;
}

bool ScreenShot(int x, int y, int w, int h,const char* path) {
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24, SDL_PIXELFORMAT_RGB24);
    if (surface == nullptr) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    SDL_Rect r = {x, y, w, h};
    if (SDL_RenderReadPixels(CanvasData::renderer, &r, SDL_PIXELFORMAT_RGB24, surface->pixels, 3 * w) < 0) {
        SDL_FreeSurface(surface);
        CanvasData::error = SDL_GetError();
        return false;
    }

    if (SDL_SaveBMP(surface,path) < 0) {
        SDL_FreeSurface(surface);
        CanvasData::error = SDL_GetError();
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}

bool ScreenShot(const char* path) {
    int w, h;
    SDL_GetWindowSize(CanvasData::window, &w, &h);
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24, SDL_PIXELFORMAT_RGB24);
    if (surface == nullptr) {
        CanvasData::error = SDL_GetError();
        return false;
    }

    if (SDL_RenderReadPixels(CanvasData::renderer, nullptr, SDL_PIXELFORMAT_RGB24, surface->pixels, 3 * w) < 0) {
        SDL_FreeSurface(surface);
        CanvasData::error = SDL_GetError();
        return false;
    }

    if (SDL_SaveBMP(surface,path) < 0) {
        SDL_FreeSurface(surface);
        CanvasData::error = SDL_GetError();
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}

void ShowWindow() {
    SDL_ShowWindow(CanvasData::window);
}

void HideWindow() {
    SDL_HideWindow(CanvasData::window);
}

void RaiseWindow() {
    SDL_RaiseWindow(CanvasData::window);
}

void MaximizeWindow() {
    SDL_MaximizeWindow(CanvasData::window);
}

void MinimizeWindow() {
    SDL_MinimizeWindow(CanvasData::window);
}

bool SetWindowIcon(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface == nullptr) {
        CanvasData::error = IMG_GetError();
        return false;
    }

    SDL_SetWindowIcon(CanvasData::window, surface);

    SDL_FreeSurface(surface);

    return true;
}
} // Canvas
} // TFC
