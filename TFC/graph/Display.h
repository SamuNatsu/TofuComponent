/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : Display.h
 *Version : 1.0
 ************************************************/

#ifndef TFC_GRAPH_DISPLAY_H
#define TFC_GRAPH_DISPLAY_H

#include "../TFC_header.h"

#include "class/Image.h"
#include "class/AnimateImage.h"

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
