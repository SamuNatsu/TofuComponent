#include "Image.h"

namespace TFC {
Image::Image() {}

Image::~Image() {
    Release();
}

bool Image::Load(const char* path) {
    Release();

    SDL_Surface* surface = IMG_Load(path);
    if (surface == nullptr) {
        error = IMG_GetError();
        return false;
    }

    texture = SDL_CreateTextureFromSurface(Canvas::CanvasData::renderer, surface);
    if (texture == nullptr) {
        SDL_FreeSurface(surface);
        error = SDL_GetError();
        return false;
    }

    if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) < 0) {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        texture = nullptr;
        error = SDL_GetError();
        return false;
    }

    width = surface->w;
    height = surface->h;
    alpha = 255;
    SDL_FreeSurface(surface);

    return true;
}

bool Image::IsLoaded() const {
    return texture != nullptr;
}

void Image::Release() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        width = height = 0;
        alpha = 255;
        error = "";
        texture = nullptr;
    }
}

Uint8 Image::GetAlpha() const {
    return alpha;
}

int Image::GetWidth() const {
    return width;
}

int Image::GetHeight() const {
    return height;
}

bool Image::GetModColor(Uint8 &r, Uint8 &g, Uint8 &b) {
    if (SDL_GetTextureColorMod(texture, &r, &g, &b) < 0) {
        error = SDL_GetError();
        return false;
    }

    return true;
}

std::string Image::GetError() const {
    return error;
}

SDL_Texture* Image::GetTexture() const {
    return texture;
}

bool Image::SetAlpha(Uint8 a) {
    if (SDL_SetTextureAlphaMod(texture, a) < 0) {
        error = SDL_GetError();
        return false;
    }

    alpha = a;

    return true;
}

bool Image::SetModColor(Uint8 r, Uint8 g, Uint8 b) {
    if (SDL_SetTextureColorMod(texture, r, g, b) < 0) {
        error = SDL_GetError();
        return false;
    }

    return true;
}

};
