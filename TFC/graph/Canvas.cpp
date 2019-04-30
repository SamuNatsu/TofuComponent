#include "Canvas.h"

#include "MsgBox.h"

namespace TFC {
namespace Canvas {
namespace Data {
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
std::string error = "";
}

bool Initialize() {
  //SDL initialize failed
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    TFC::MsgBox::Error("Oops", SDL_GetError());
    return false;
  }
  //IMG initialize failed
  int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  if (IMG_Init(flags) != flags) {
    TFC::MsgBox::Error("Oops", IMG_GetError());
    return false;
  }
  //TTF initialize failed
  if(TTF_Init() < 0){
    TFC::MsgBox::Error("Oops", TTF_GetError());
    return false;
  }
  return true;
}

void Quit() {
  //Quit all libraries
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool Create(const char *title, const int w, const int h, const uint32_t flags, const int index) {
  //Destroy old canvas
	Destroy();
	//Create a window
  Data::window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  w,
                                  h,
                                  SDL_WINDOW_HIDDEN | flags);
  //Fail to create
  if (Data::window == nullptr) {
    Data::error = SDL_GetError();
    return false;
  }
  //Create a renderer
  Data::renderer = SDL_CreateRenderer(Data::window,
                                      index,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  //Fail to create
  if (Data::renderer == nullptr) {
    SDL_DestroyWindow(Data::window);
    Data::window = nullptr;
    Data::error = SDL_GetError();
    return false;
  }
  //Fail to set blend mode
  if (SDL_SetRenderDrawBlendMode(Data::renderer, SDL_BLENDMODE_BLEND) < 0) {
    SDL_DestroyWindow(Data::window);
    SDL_DestroyRenderer(Data::renderer);
    Data::window = nullptr;
    Data::renderer = nullptr;
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool IsCreated() {
  return Data::window != nullptr;
}

void Destroy() {
  if (IsCreated()){
    SDL_DestroyWindow(Data::window);
    SDL_DestroyRenderer(Data::renderer);
    Data::window = nullptr;
    Data::renderer = nullptr;
    Data::error = "";
  }
}

bool RendererClear() {
  //Fail to clear
  if (SDL_RenderClear(Data::renderer) < 0){
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

void RendererFresh() {
  SDL_RenderPresent(Data::renderer);
}

bool GetDrawColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
  //Fail to get
  if (SDL_GetRenderDrawColor(Data::renderer, &r, &g, &b, &a) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool SetDrawColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
  //Fail to set
  if(SDL_SetRenderDrawColor(Data::renderer, r, g, b, a) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool DrawLine(const int x1, const int y1, const int x2, const int y2) {
  //Fail to draw
  if (SDL_RenderDrawLine(Data::renderer, x1, y1, x2, y2) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool DrawRect(const int x, const int y, const int w, const int h) {
  //Size & position
  SDL_Rect r = {x, y, w, h};
  //Fail to draw
  if (SDL_RenderDrawRect(Data::renderer, &r) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool DrawPoint(const int x, const int y) {
  //Fail to draw
  if (SDL_RenderDrawPoint(Data::renderer, x, y) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool FillRect(const int x, const int y, const int w, const int h) {
  //Size & position
  SDL_Rect r = {x, y, w, h};
  //Fail to fill
  if (SDL_RenderFillRect(Data::renderer, &r) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool ScreenShot(const int x, const int y, const int w, const int h, const char *path) {
  //Create a temperary surface
  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 24, SDL_PIXELFORMAT_RGB24);
  //Fail to create
  if (surface == nullptr) {
    Data::error = SDL_GetError();
    return false;
  }
  //Size & position
  SDL_Rect r = {x, y, w, h};
  //Fail to get pixels
  if (SDL_RenderReadPixels(Data::renderer, &r, SDL_PIXELFORMAT_RGB24, surface->pixels, 3 * w) < 0) {
    SDL_FreeSurface(surface);
    Data::error = SDL_GetError();
    return false;
  }
  //Fail to save picture
  if (SDL_SaveBMP(surface, path) < 0) {
    SDL_FreeSurface(surface);
    Data::error = SDL_GetError();
    return false;
  }
  //Free temperary surface
  SDL_FreeSurface(surface);
  return true;
}

bool ScreenShot(const char *path) {
  int w, h;
  SDL_GetWindowSize(Data::window, &w, &h);
  return ScreenShot(0, 0, w, h, path);
}

void HideWindow() {
  SDL_HideWindow(Data::window);
}

void ShowWindow() {
  SDL_ShowWindow(Data::window);
}

void RaiseWindow() {
  SDL_RaiseWindow(Data::window);
}

void RestoreWindow() {
  SDL_RestoreWindow(Data::window);
}

void MaximizeWindow() {
  //Only resizable windows can use this function
  if ((SDL_GetWindowFlags(Data::window) & SDL_WINDOW_RESIZABLE) != 0) {
    SDL_MaximizeWindow(Data::window);
  }
}

void MinimizeWindow() {
  SDL_MinimizeWindow(Data::window);
}

bool SetWindowIcon(const char *path) {
  //Load icon
  SDL_Surface* surface = IMG_Load(path);
  //Fail to load
  if (surface == nullptr) {
    Data::error = IMG_GetError();
    return false;
  }
  SDL_SetWindowIcon(Data::window, surface);
  //Free temperary icon surface
  SDL_FreeSurface(surface);
  return true;
}

} // Canvas
} // TFC
