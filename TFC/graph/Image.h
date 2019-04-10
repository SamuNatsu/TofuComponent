/**************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Image.h
 *Description : A texture data structure
 *Version : 1.0
 **************************************************/

#ifndef TFC_GRAPH_IMAGE_H
#define TFC_GRAPH_IMAGE_H

#include <stdint.h>

#include <string>

#include "../TFC_header.h"
#include "Canvas.h"

namespace TFC {

class Image {
 public:
  //Constructor & Destructor
  Image(); //Constructor
  Image(const Image&) = delete; //Not allowed to use copy constructor
  ~Image(); //Destructor
  //Operator
  Image& operator=(const Image&) = delete; //Not allowed to use copy-assignment operator
  //Load
  bool Load(const char*); //Load
  //Release
  void Release(); //Release
  //Get Attribute
  bool IsLoaded() const; //Return whether it has been loaded
  uint8_t GetAlpha() const; //Return alpha
  std::string GetError() const; //Get error string
  bool GetFilterColor(uint8_t&, uint8_t&, uint8_t&); //Get filter color
  int GetHeight() const; //Return height
  SDL_Rect GetRenderAttribute() const; //Get render area
  SDL_Texture* GetTexture() const; //Get internal texture structure
  int GetWidth() const; //Return width
  //Set Attribute
  bool SetAlpha(const uint8_t); //Set alpha
  bool SetFilterColor(const uint8_t, const uint8_t, const uint8_t); //Set filter color
  void SetRenderAttribute(const int, const int, const int, const int); //Set render area
 private:
  //Attribute
  int width_ = 0, height_ = 0;
  uint8_t alpha_ = 0;
  SDL_Rect rect_ = {0, 0, 0, 0};
  //Texture pointer
  SDL_Texture *texture_ = nullptr;
  //Error string
  std::string error_ = "";
};

}

#endif // TFC_GRAPH_IMAGE_H
