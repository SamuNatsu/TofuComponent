/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Font.h
 *Version : 1.0
 ************************************************/

#ifndef TFC_CLASS_FONT_H
#define TFC_CLASS_FONT_H

#include "../TFC_header.h"

namespace TFC {

class Font {
 public:
  //Constructor & Destructor
  Font();
  ~Font();
  //Load & Release
  bool Load(const char*, int);
  void Release();
  //Get
  TTF_Font* GetFont() const;
 private:
   TTF_Font *font = nullptr;
   std::string error = "";
};

}

#endif // TFC_CLASS_FONT_H
