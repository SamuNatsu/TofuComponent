#include "Image.h"

namespace TFC {

Image::Image() {}

Image::~Image() {
  Release();
}

/*=======================================================
 *Function name : Load
 *Parameter :
 *  const char *file : The file to load
 *Description : Load a picture into the texture structure
 *Return : TRUE on success, FALSE on error
 ======================================================*/
bool Image::Load(const char *file) {
  //Release old texture
  Release();
  //Load new picture
  SDL_Surface *surface = IMG_Load(file);
  if (surface == nullptr) {
    error_ = IMG_GetError();
    return false;
  }
  //Transfer the picture into texture
  texture_ = SDL_CreateTextureFromSurface(Canvas::CanvasData::renderer, surface);
  if (texture_ == nullptr) {
    SDL_FreeSurface(surface);
    error_ = SDL_GetError();
    return false;
  }
  //Set texture blend mode
  if (SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND) < 0) {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    error_ = SDL_GetError();
    return false;
  }
  //Set texture attriute
  width_ = surface->w;
  height_ = surface->h;
  alpha_ = 255;
  rect_ = {0, 0, surface->w, surface->h};
  //Free temporary data
  SDL_FreeSurface(surface);
  //Return success
  return true;
}

/*===============================
 *Function name : Release
 *Description : Release the Image
 ==============================*/
void Image::Release() {
  //If loaded
  if (IsLoaded()) {
    SDL_DestroyTexture(texture_);
    width_ = height_ = 0;
    alpha_ = 255;
    texture_ = nullptr;
    error_ = "";
  }
}

/*======================================================
 *Function name : IsLoaded
 *Description : Return whether the Image has been loaded
 *Return : TRUE on loaded, FALSE on not
 =====================================================*/
bool Image::IsLoaded() const {
  //Return query
  return texture_ != nullptr;
}

/*===========================================
 *Function name : GetAlpha
 *Description : Return the alpha of the Image
 *Return : Alpha
 ==========================================*/
uint8_t Image::GetAlpha() const {
  //Return query
  return alpha_;
}

/*==================================================
 *Function name : GetError
 *Description : Return the error string of the Image
 *Return : Error string
 =================================================*/
std::string Image::GetError() const {
  //Return query
  return error_;
}

/*==================================================
 *Function name : GetFilterColor
 *Parameter :
 *  uint8_t &r : Red color
 *  uint8_t &g : Green color
 *  uint8_t &b : Blue color
 *Description : Return the filter color of the Image
 *Return : TRUE on success, FALSE on error
 =================================================*/
bool Image::GetFilterColor(uint8_t &r, uint8_t &g, uint8_t &b) {
  //If get failed
  if (SDL_GetTextureColorMod(texture_, &r, &g, &b) < 0) {
      error_ = SDL_GetError();
      return false;
  }
  //Return success
  return true;
}

/*============================================
 *Function name : GetHeight
 *Description : Return the height of the Image
 *Return : Height
 ===========================================*/
int Image::GetHeight() const {
  //Return query
  return height_;
}

/*======================================================
 *Function name : GetRenderAttribute
 *Description : Return the render rectangle of the Image
 *Return : Render rectangle
 =====================================================*/
SDL_Rect Image::GetRenderAttribute() const {
  //Return query
  return rect_;
}

/*=====================================================
 *Function name : GetTexture
 *Description : Return the texture pointer of the Image
 *Return : Texture pointer
 ====================================================*/
SDL_Texture* Image::GetTexture() const {
  //Return query
  return texture_;
}

/*===========================================
 *Function name : GetWidth
 *Description : Return the width of the Image
 *Return : Width
 ==========================================*/
int Image::GetWidth() const {
  //Return query
  return width_;
}

/*========================================
 *Function name : SetAlpha
 *Parameter :
 *  const uint8_t a : Alpha
 *Description : Set the alpha of the Image
 *Return : TRUE on success, FALSE on error
 =======================================*/
bool Image::SetAlpha(const uint8_t a) {
  //If set failed
  if (SDL_SetTextureAlphaMod(texture_, a) < 0) {
    error_ = SDL_GetError();
    return false;
  }
  //Set texture attribute
  alpha_ = a;
  //Return success
  return true;
}

/*===============================================
 *Function name : SetFilterColor
 *Parameter :
 *  const uint8_t r : Red color
 *  const uint8_t g : Green color
 *  const uint8_t b : Blue color
 *Description : Set the filter color of the Image
 *Return : TRUE on success, FALSE on error
 ==============================================*/
bool Image::SetFilterColor(const uint8_t r, const uint8_t g, const uint8_t b) {
  //If set failed
  if (SDL_SetTextureColorMod(texture_, r, g, b) < 0) {
    error_ = SDL_GetError();
    return false;
  }
  //Return success
  return true;
}

/*===================================================
 *Function name : SetRenderAttribute
 *Parameter :
 *  const int x : X
 *  const int y : Y
 *  const int w : Width
 *  const int h : Height
 *Description : Set the render rectangle of the Image
 ==================================================*/
void Image::SetRenderAttribute(const int x, const int y, const int w, const int h) {
  rect_ = {x, y, w, h};
}

};
