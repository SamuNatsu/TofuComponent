/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Display.h
 *Version : 1.0
 ************************************************/

#ifndef TFC_GRAPH_DISPLAY_H
#define TFC_GRAPH_DISPLAY_H

#include "../TFC_header.h"

#include "../class/AnimateImage.h"
#include "../class/Font.h"
#include "../class/Image.h"

namespace TFC {
namespace Display {
namespace Data {
extern std::string error;
}
//AnimateImage
bool D_Animate(AnimateImage&, int, int, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Animate(AnimateImage&, int, int, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Animate(AnimateImage&, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Animate(AnimateImage&, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Animate(AnimateImage&, int, int, int, int);
bool D_Animate(AnimateImage&, int, int);
//Text
bool D_Text(Font&, const char*, int, int, int, int, uint8_t, uint8_t, uint8_t, uint8_t = 255);
bool D_Text(Font&, const char*, int, int, uint8_t, uint8_t, uint8_t, uint8_t = 255);
//Image
bool D_Image(Image&, int, int, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Image(Image&, int, int, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Image(Image&, int, int, double, int, int, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Image(Image&, int, int, double, SDL_RendererFlip = SDL_FLIP_NONE);
bool D_Image(Image&, int, int, int, int);
bool D_Image(Image&, int, int);
}
}

#endif // TFC_GRAPH_DISPLAY_H
