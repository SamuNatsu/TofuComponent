#include "AnimateImage.h"

namespace TFC {
AnimateImage::AnimateImage() {}

AnimateImage::~AnimateImage() {}

void AnimateImage::SetFPS(int fps) {
    sfps = fps;
    fpsc = 1.0 / fps * SDL_GetPerformanceFrequency();
}

void AnimateImage::SetFrameSize(int w, int h) {
    frameInfo.x = frameInfo.y = 0;
    frameInfo.w = w;
    frameInfo.h = h;
}

} // TFC
