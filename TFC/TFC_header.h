#ifndef TFC_HEADER_H_INCLUDED
#define TFC_HEADER_H_INCLUDED

#if defined(TFC_X86)
    #include "TFC\SDL2\x86\SDL.h"
    #include "TFC\SDL2\x86\SDL_ttf.h"
    #include "TFC\SDL2\x86\SDL_image.h"
    #include "TFC\SDL2\x86\SDL_mixer.h"
#else
    #include "TFC\SDL2\x64\SDL.h"
    #include "TFC\SDL2\x64\SDL_ttf.h"
    #include "TFC\SDL2\x64\SDL_image.h"
    #include "TFC\SDL2\x64\SDL_mixer.h"
#endif // defined TFC_X86

#endif // TFC_HEADER_H_INCLUDED
