#include "AnimateImage.h"

namespace TFC {

AnimateImage::AnimateImage() {}

AnimateImage::~AnimateImage() {}

/*=========================
 *Function name : NextFrame
 *Parameter :
 *  const uint64_t counter : Internal counter
 *Description : Set FPS
 ========================*/
void AnimateImage::NextFrame(const uint64_t counter) {
  if (counter - lastc_ < fpsc_) {
    return;
  }
  nowf_ = (nowf_ + (counter - lastc_) / fpsc_) % (endf_ - startf_ + 1);
  lastc_ = counter;
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
  //Set frame size
  frameW_ = GetWidth() / w, frameH_ = GetHeight() / h;
  //Generate frame information
  for (int i = 0, nw = 0; i < w; ++i, nw += frameW_) {
    for (int j = 0, nh = 0; j < h; ++j, nh += frameH_) {
      frameInfo_.emplace_back((SDL_Rect){nw, nh, frameW_, frameH_});
    }
  }
  //Set first frame
  SetRenderAttribute(0, 0, frameW_, frameH_);
}

bool AnimateImage::SetLoopRange(uint64_t s, uint64_t e) {
  //Range check
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
  //Set loop range
  startf_ = s;
  endf_ = e;
  //Return success
  return true;
}

uint64_t AnimateImage::GetFrameNum() const {
  //Return query
  return frameInfo_.size();
}

int AnimateImage::GetFrameHeight() const {
  //Return query
  return frameH_;
}

int AnimateImage::GetFrameWidth() const {
  //Return query
  return frameW_;
}

}
