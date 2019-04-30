/*************************************************
 *Copyright (c) 2019-2019 SamuNatsu <samunatsu.cn>
 *File name : TFC.h
 *Description : The main header of TFC
 *Version : 1.0
 ************************************************/

#ifndef TFC_H_INCLUDED
#define TFC_H_INCLUDED

#include "./component/Button.h"
#include "./component/Director.h"

#include "./event/EventHook.h"
#include "./event/EventHookMgr.h"

#include "./event/FSM/BaseState.h"
#include "./event/FSM/FiniteStateMachine.h"

/*
#include "./network/NetworkMain.h"
#include "./network/TCP/TCPServer.h"
#include "./network/TCP/TCPClient.h"
*/

#include "./graph/class/AnimateImage.h"
#include "./graph/class/Image.h"

#include "./graph/Canvas.h"
#include "./graph/MsgBox.h"
#include "./graph/Display.h"

#include "./resource/FileNameGen.h"

#include "./thread/ThreadPool.h"
#include "./thread/LockFreeQueue.h"

#endif // TFC_H_INCLUDED
