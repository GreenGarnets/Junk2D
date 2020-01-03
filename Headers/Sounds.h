#ifndef _SOUNDS_H               
#define _SOUNDS_H               
#define WIN32_LEAN_AND_MEAN

#include <xact3.h>
#include "constants.h"

class Junk2DSound
{
	// properties
private:
	IXACT3Engine* xactEngine;   // XACT ���� ������ ����Ű�� ������
	IXACT3WaveBank* waveBank;   // XACT ���̺� ��ũ�� ����Ű�� ������
	IXACT3SoundBank* soundBank; // XACT ���� ��ũ�� ����Ű�� ������
	XACTINDEX cueI;             // XACT ���� �ε���
	void* mapWaveBank;          // ���� ����
	void* soundBankData;
	bool coInitialized;         // �ʱ�ȭ ����

public:
	Junk2DSound();
	virtual ~Junk2DSound();

	// ��� �Լ���
	HRESULT initialize();
	void run();						// �ֱ������� ���� ���� �۾��� ����
	void playCue(const char cue[]); // ���
	void stopCue(const char cue[]); // ����
};

#endif
