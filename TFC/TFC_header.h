/*************************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : TFC_header.h
 *Description : The internal using header file
 *Version : 1.0
 ************************************************************/

#ifndef TFC_HEADER_H_INCLUDED
#define TFC_HEADER_H_INCLUDED

/****************************************************************
 *Warning : Maybe some compilers do not support this header file.
 ***************************************************************/
#include <bits/stdc++.h>

/***************************************
 *If you want to use x86 version of TFC,
 *  please enable the definition below,
 *  or using other ways to enable.
 **************************************/

//#define TFC_X86

#if defined(TFC_X86)
    #include ".\SDL2\x86\SDL.h"
    #include ".\SDL2\x86\SDL_ttf.h"
    #include ".\SDL2\x86\SDL_image.h"
    #include ".\SDL2\x86\SDL_mixer.h"
#else
    #include ".\SDL2\x64\SDL.h"
    #include ".\SDL2\x64\SDL_ttf.h"
    #include ".\SDL2\x64\SDL_image.h"
    #include ".\SDL2\x64\SDL_mixer.h"
#endif

#endif // TFC_HEADER_H_INCLUDED
