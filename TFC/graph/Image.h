#ifndef IMAGE_H
#define IMAGE_H

#include "../TFC_header.h"
#include "Canvas.h"

#include <string>

namespace TFC {
class Image {
public:
     // Construction & Destruction
    Image();
    Image(const Image&) = delete;
    ~Image();
     // No copy
    Image& operator=(const Image&) = delete;
     // Load & Release
    bool Load(const char*);
    bool IsLoaded() const;
    void Release();
     // Get attribute
    Uint8 GetAlpha() const;
    int GetWidth() const;
    int GetHeight() const;
    bool GetModColor(Uint8&, Uint8&, Uint8&);
    std::string GetError() const;
    SDL_Texture* GetTexture() const;
     // Set attribute
    bool SetAlpha(Uint8);
    bool SetModColor(Uint8, Uint8, Uint8);
private:
    int width = 0, height = 0;
    Uint8 alpha = 255;
    std::string error = "";
    SDL_Texture *texture = nullptr;
};
} // TFC

#endif // IMAGE_H
