#ifndef _CONSTANTS_H            
#define _CONSTANTS_H            
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>

#include "graphics.h"
#include "Sounds.h"
#include "input.h"

#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255) 

//-------- 매크로들 --------//
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }

#define VOLUME_FULL     0L
#define VOLUME_SILENCE  -10000L

//-----------------------------------------------
//                  상수들
//-----------------------------------------------

// 윈도우
const char CLASS_NAME[] = "Endless Time";
const char GAME_TITLE[] = "Endless Time";
const bool FULLSCREEN = FALSE;
const UINT GAME_WIDTH = 1280;
const UINT GAME_HEIGHT = 720;

// 게임
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

// 키 맵핑
const UCHAR ESC_KEY = VK_ESCAPE;   // esc키
const UCHAR ALT_KEY = VK_MENU;     // Alt키
const UCHAR ENTER_KEY = VK_RETURN;   // 엔터키

// 플레이어 어빌리티
const UINT PlayerAbility = 4;
//const UINT PlayerItemSlot[10] = {0,};

const UINT MapXY = 300;
	
// .xwb의 위치
const char WAVE_BANK[] = "..\\Resources\\Sounds\\Win\\WavesExample1.xwb";
// .xsb의 위치
const char SOUND_BANK[] = "..\\Resources\\Sounds\\Win\\SoundsExample1.xsb";

#endif
