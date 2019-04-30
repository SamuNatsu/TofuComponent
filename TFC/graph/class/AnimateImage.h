/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : EventHookMgr.h
 *Description : An animate structure
 *Version : 1.0
 ************************************************/

#ifndef ANIMATEIMAGE_H
#define ANIMATEIMAGE_H

#include "Image.h"
#include "../../TFC_header.h"

namespace TFC {

class AnimateImage : public Image {
 public:
  //Construction & Destruction
  AnimateImage();
  ~AnimateImage();
  //Play
  void NextFrame(const uint64_t);
  //Set
  void SetFPS(const int);
  void SetFrameInformation(const int, const int);
  bool SetLoopRange(uint64_t, uint64_t);
  //Get
  uint64_t GetFrameNum() const;
  int GetFrameHeight() const;
  int GetFrameWidth() const;
 private:
  //FPS
  int sfps_ = 1;
  //Frame size
  int frameW_ = 0, frameH_ = 0;
  //CPU counts per frame
  uint64_t fpsc_ = 0;
  //Start & End CPU counts
  uint64_t startf_ = 0, endf_ = 0;
  //Last CPU counts
  uint64_t lastc_ = 0;
  //Frame now
  uint64_t nowf_ = 0;
  //Store frame information
  std::vector<SDL_Rect> frameInfo_;
  //Error string
  std::string error_ = "";
};

}

#endif // ANIMATEIMAGE_H
