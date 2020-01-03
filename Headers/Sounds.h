#ifndef _SOUNDS_H               
#define _SOUNDS_H               
#define WIN32_LEAN_AND_MEAN

#include <xact3.h>
#include "constants.h"

class Junk2DSound
{
	// properties
private:
	IXACT3Engine* xactEngine;   // XACT 사운드 엔진을 가리키는 포인터
	IXACT3WaveBank* waveBank;   // XACT 웨이브 뱅크를 가리키는 포인터
	IXACT3SoundBank* soundBank; // XACT 사운드 뱅크를 가리키는 포인터
	XACTINDEX cueI;             // XACT 사운드 인덱스
	void* mapWaveBank;          // 파일 해제
	void* soundBankData;
	bool coInitialized;         // 초기화 여부

public:
	Junk2DSound();
	virtual ~Junk2DSound();

	// 멤버 함수들
	HRESULT initialize();
	void run();						// 주기적으로 사운드 엔진 작업을 수행
	void playCue(const char cue[]); // 재생
	void stopCue(const char cue[]); // 정지
};

#endif
