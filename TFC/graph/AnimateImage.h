#ifndef ANIMATEIMAGE_H
#define ANIMATEIMAGE_H

#include "../TFC_header.h"
#include "Image.h"

#include <string>

namespace TFC {
class AnimateImage : public Image{
public:
     // Construction & Destruction
    AnimateImage();
    ~AnimateImage();
     // Set
    void SetFPS(int);
    void SetFrameSize(int, int);
private:
    int sfps;
    Uint64 fpsc, lastc;
    SDL_Rect frameInfo;
};
} // TFC

#endif // ANIMATEIMAGE_H
