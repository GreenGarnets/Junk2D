#include "..\\Headers\\Sounds.h"

Junk2DSound::Junk2DSound()
{
	xactEngine = NULL;
	waveBank = NULL;
	soundBank = NULL;
	cueI = 0;
	mapWaveBank = NULL;         
	soundBankData = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	coInitialized = true;
}

Junk2DSound::~Junk2DSound()
{
	// XACT 엔진 종료
	if (xactEngine)
	{
		xactEngine->ShutDown(); // 리소스 해제, 엔진 종료
		xactEngine->Release();
	}

	if (soundBankData)
		delete[] soundBankData;
	soundBankData = NULL;

	// 매핑된 메모리를 해제
	if (mapWaveBank)
		UnmapViewOfFile(mapWaveBank);
	mapWaveBank = NULL;

	if (coInitialized)       
		CoUninitialize();
}

HRESULT Junk2DSound::initialize()
{
	HRESULT result = E_FAIL;
	HANDLE hFile;
	DWORD fileSize;
	DWORD bytesRead;
	HANDLE hMapFile;

	XACT3CreateEngine(0, &xactEngine);

	// XACT 런타임 초기화 & 생성
	XACT_RUNTIME_PARAMETERS xactParams = { 0 };
	xactParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	xactEngine->Initialize(&xactParams);

	// 메모리에 매핑된 파일 IO를 사용해 메모리 내부에서 생성
	hFile = CreateFile(WAVE_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
			if (hMapFile)
			{
				mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (mapWaveBank)
					xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank);

				CloseHandle(hMapFile);    // 불필요한 핸들을 닫아줌
			}
		}
		CloseHandle(hFile);   
	}

	// 사운드 뱅크 파일을 읽고 등록
	hFile = CreateFile(SOUND_BANK, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		fileSize = GetFileSize(hFile, NULL);
		if (fileSize != -1)
		{
			soundBankData = new BYTE[fileSize];    // 사운드 뱅크를 위해 예약된 메모리
			if (soundBankData)
			{
				if (0 != ReadFile(hFile, soundBankData, fileSize, &bytesRead, NULL))
					result = xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank);
			}
		}
		CloseHandle(hFile);
	}

	return S_OK;
}

void Junk2DSound::run()
{
	if (xactEngine == NULL)
		return;
	xactEngine->DoWork();
}

void Junk2DSound::playCue(const char cue[])
{
	if (soundBank == NULL)
		return;
	cueI = soundBank->GetCueIndex(cue);        // 사운드 뱅크로부터 재생할 사운드의 큐를 가져온다
	soundBank->Play(cueI, 0, 0, NULL);
}

void Junk2DSound::stopCue(const char cue[])
{
	if (soundBank == NULL)
		return;
	cueI = soundBank->GetCueIndex(cue);        // 사운드 뱅크로부터 멈출 사운드의 큐를 가져온다
	soundBank->Stop(cueI, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
}
