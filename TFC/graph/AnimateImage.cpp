#include "AnimateImage.h"

namespace TFC {

AnimateImage::AnimateImage() {}

AnimateImage::~AnimateImage() {}

void AnimateImage::NextFrame(const uint64_t counter) {
  nowf_ = (nowf_ + (counter - lastc_) / fpsc_) % (endf_ - startf_ + 1);
  SetRenderAttribute(frameInfo_[nowf_].x, frameInfo_[nowf_].y, frameW_,frameH_);
}

/*=========================
 *Function name : SetFPS
 *Parameter :
 *  const int fps : The FPS
 *Description : Set FPS
 ========================*/
void AnimateImage::SetFPS(const int fps) {
  //Set FPS
  sfps_ = fps;
  //Set CPU count per second
  fpsc_ = 1.0 / fps * SDL_GetPerformanceFrequency();
}

void AnimateImage::SetFrameInformation(const int w, const int h) {
  frameW_ = GetWidth() / w, frameH_ = GetHeight() / h;
  for (int i = 0, nw = 0; i < w; ++i, nw += frameW_) {
    for (int j = 0, nh = 0; j < h; ++j, nh += frameH_) {
        frameInfo_.emplace_back((SDL_Rect){nw, nh, frameW_, frameH_});
    }
  }
}

bool AnimateImage::SetLoopRange(uint64_t s, uint64_t e) {
  if (s < 0) {
    s = 0;
  }
  if (e >= GetFrameNum()) {
    e = GetFrameNum() - 1;
  }
  if (s > e) {
    error_ = "Invalid range";
    return false;
  }
  startf_ = s;
  endf_ = e;
  return true;
}

uint64_t AnimateImage::GetFrameNum() const {
  return frameInfo_.size();
}

}
