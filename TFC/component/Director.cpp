#include "director.h"

#include "../event/EventHook.h"

namespace {

void EventLoop(TFC::Director::VVF eventFunvtion) {
  //Set static variables
  static bool &flag = TFC::Director::Data::stopFlag;
  static SDL_Event &event = TFC::Director::Data::event;
  static uint32_t &sTPS = TFC::Director::Data::sTPS;
  static uint32_t &rTPS = TFC::Director::Data::rTPS;
  static uint64_t &cTPS = TFC::Director::Data::cTPS;
  static const uint64_t cpuFreq = SDL_GetPerformanceFrequency();
  //Initialize
  event.type = 0;
  uint64_t tickS = SDL_GetPerformanceCounter(), tickE = 0;
  //Loop
  while(!flag) {
    //Successfully get
    while (SDL_PollEvent(&event) > 0) {
      TFC::EventHook::CallAllHook();
      eventFunvtion();
    }
    //Reset
    event.type = 0;
    //Delay
    tickE = SDL_GetPerformanceCounter();
    if(tickS + cTPS >= tickE) {
      rTPS = sTPS;
      tickS += cTPS;
      SDL_Delay(1000.0 * (tickS - tickE) / cpuFreq);
      do {
        tickE = SDL_GetPerformanceCounter();
      }
      while(tickS >= tickE);
    }
    else {
      rTPS = static_cast<double>(cpuFreq) / (tickE - tickS);
    }
    tickS = SDL_GetPerformanceCounter();
  }
}

void RenderLoop(TFC::Director::VVF renderFunction) {
  //Set static variables
  static bool &flag = TFC::Director::Data::stopFlag;
  static uint32_t &sFPS = TFC::Director::Data::sFPS;
  static uint32_t &rFPS = TFC::Director::Data::rFPS;
  static uint64_t &cFPS = TFC::Director::Data::cFPS;
  static uint64_t &tickS = TFC::Director::Data::rTickS;
  static uint64_t &tickE = TFC::Director::Data::rTickE;
  static const uint64_t cpuFreq = SDL_GetPerformanceFrequency();
  //Initialize
  tickS = SDL_GetPerformanceCounter();
  tickE = 0;
  //Loop
  while(!flag) {
    //Draw
    renderFunction();
    //Delay
    tickE = SDL_GetPerformanceCounter();
    if(tickS + cFPS >= tickE) {
      rFPS = sFPS;
      tickS += cFPS;
      SDL_Delay(1000.0 * (tickS - tickE) / cpuFreq);
      do {
        tickE = SDL_GetPerformanceCounter();
      }
      while(tickS >= tickE);
    }
    else {
      rFPS = static_cast<double>(cpuFreq) / (tickE - tickS);
    }
    tickS = SDL_GetPerformanceCounter();
  }
}

}

namespace TFC {
namespace Director {
namespace Data {
uint64_t rTickS = 0, rTickE = 0;
bool stopFlag = true;
SDL_Event event;
uint32_t sFPS = 1, rFPS = 0, sTPS = 1, rTPS = 0;
uint64_t cFPS = 0, cTPS = 0;
std::string error = "";
}

void SetFPS(int fps) {
  Data::sFPS = fps;
  Data::rFPS = 0;
  Data::cFPS = 1.0 / fps * SDL_GetPerformanceFrequency();
}

void SetTPS(int tps) {
  Data::sTPS = tps;
  Data::rTPS = 0;
  Data::cTPS = 1.0 / tps * SDL_GetPerformanceFrequency();
}

void StartMainLoop(VVF _EF, VVF _RF) {
  //Initialize
  Data::stopFlag = false;
  //Run rendering loop
  std::thread rTrd(::RenderLoop, _RF);
  //Run event loop
  ::EventLoop(_EF);
  //Wait rendering loop to stop
  if (rTrd.joinable()) {
    rTrd.join();
  }
}

void StopMainLoop() {
  Data::stopFlag = true;
}

}
}
