#include "Display.h"

#include "../component/Director.h"
#include "../event/EventHook.h"

#include "Canvas.h"

namespace TFC {
namespace Display {
namespace Data {
std::string error = "";
}

bool D_Animate(AnimateImage &img, int x, int y, int w, int h, double angle, int cx, int cy, SDL_RendererFlip flip) {
  //Get next frame
  img.NextFrame(TFC::Director::Data::rTickS);
  //Size & position
  SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
  //Rotate center
  SDL_Point p = {cx, cy};
  //Fail to draw
  if (SDL_RenderCopyEx(TFC::Canvas::Data::renderer, img.GetTexture(), &rs, &r, angle, &p, flip) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool D_Animate(AnimateImage &img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip) {
  return D_Animate(img, x, y, w, h, angle, img.GetWidth() >> 1, img.GetHeight() >> 1, flip);
}

bool D_Animate(AnimateImage &img, int x, int y, double angle, int cx, int cy, SDL_RendererFlip flip) {
  return D_Animate(img, x, y, img.GetWidth(), img.GetHeight(), angle, cx, cy, flip);
}

bool D_Animate(AnimateImage &img, int x, int y, double angle, SDL_RendererFlip flip) {
  return D_Animate(img, x, y, angle, img.GetWidth() >> 1, img.GetHeight() >> 1, flip);
}

bool D_Animate(AnimateImage &img, int x, int y, int w,int h) {
  //Get next frame
  img.NextFrame(TFC::Director::Data::rTickS);
  //Size & position
  SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
  //Fail to draw
  if (SDL_RenderCopy(TFC::Canvas::Data::renderer, img.GetTexture(), &rs, &r) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool D_Animate(AnimateImage &img, int x, int y) {
  return D_Animate(img, x, y, img.GetFrameWidth(), img.GetFrameHeight());
}

bool D_Text(Font& font, const char *text, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_Surface *surface = TTF_RenderUTF8_Blended(font.GetFont(), text, (SDL_Color){r, g, b, a});
  if (surface == nullptr) {
    Data::error = TTF_GetError();
    return false;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Canvas::Data::renderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    Data::error = SDL_GetError();
    return false;
  }
  //Size & position
  SDL_Rect rt = {x, y, w, h};
  //Fail to draw
  if (SDL_RenderCopy(TFC::Canvas::Data::renderer, texture, nullptr, &rt) < 0) {
    Data::error = SDL_GetError();
    SDL_DestroyTexture(texture);
    return false;
  }
  SDL_DestroyTexture(texture);
  return true;
}

bool D_Text(Font& font, const char *text, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_Surface *surface = TTF_RenderUTF8_Blended(font.GetFont(), text, (SDL_Color){r, g, b, a});
  //Size & position
  SDL_Rect rt = {x, y, surface->w, surface->h};
  if (surface == nullptr) {
    Data::error = TTF_GetError();
    return false;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Canvas::Data::renderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    Data::error = SDL_GetError();
    return false;
  }
  //Fail to draw
  if (SDL_RenderCopy(TFC::Canvas::Data::renderer, texture, nullptr, &rt) < 0) {
    Data::error = SDL_GetError();
    SDL_DestroyTexture(texture);
    return false;
  }
  SDL_DestroyTexture(texture);
  return true;
}

bool D_Image(Image &img, int x, int y, int w, int h, double angle, int cx, int cy, SDL_RendererFlip flip) {
  //Size & position
  SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
  //Rotate center
  SDL_Point p = {cx, cy};
  //Fail to draw
  if (SDL_RenderCopyEx(TFC::Canvas::Data::renderer, img.GetTexture(), &rs, &r, angle, &p, flip) < 0) {
      Data::error = SDL_GetError();
      return false;
  }
  return true;
}

bool D_Image(Image &img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip) {
  return D_Image(img, x, y, w, h, angle, img.GetWidth() >> 1, img.GetHeight() >> 1, flip);
}

bool D_Image(Image &img, int x, int y, double angle, int cx, int cy, SDL_RendererFlip flip) {
    return D_Image(img, x, y, img.GetWidth(), img.GetHeight(), angle, cx, cy, flip);
}

bool D_Image(Image &img, int x, int y, double angle, SDL_RendererFlip flip) {
  return D_Image(img, x, y, angle, img.GetWidth() >> 1, img.GetHeight() >> 1, flip);
}

bool D_Image(Image &img, int x, int y, int w,int h) {
  //Size & position
  SDL_Rect rs = img.GetRenderAttribute(), r = {x, y, w, h};
  //Fail to draw
  if (SDL_RenderCopy(TFC::Canvas::Data::renderer, img.GetTexture(), &rs, &r) < 0) {
    Data::error = SDL_GetError();
    return false;
  }
  return true;
}

bool D_Image(Image &img, int x, int y) {
  return D_Image(img, x, y, img.GetWidth(), img.GetHeight());
}

}
}
