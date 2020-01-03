#ifndef _GAME_H                 // �������� ����
#define _GAME_H                 
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <list>

#include "graphics.h"
#include "input.h"
#include "Junk2DSprite.h"
#include "ObjectManager.h"
#include "Sounds.h"

class Game
{
protected:

	HWND    hwnd;               // ������ �ڵ�
	HRESULT hr;                 // ǥ�� ��ȯ Ÿ��
	LARGE_INTEGER timeStart;    // ���� ī���� ���۰�
	LARGE_INTEGER timeEnd;      // ���� ī���� ���� ��
	LARGE_INTEGER timerFreq;    // ���� ī���� �󵵼�
	float   frameTime;          // ������ �����ӿ� �ʿ��� �ð�
	float   fps;                // �ʴ� �����Ӽ�
	DWORD   sleepTime;          // ������ ������ ��� ���� �ð�
	bool    paused;             // ���� �Ͻ����� ����
	bool    initialized;        // �ʱ�ȭ



	int Maps[1000][1000];
	int mapMaxX, mapMaxY;
	

public:
	Game(); // ������
	virtual ~Game(); // �Ҹ���

	static Graphics		*graphics;  // Graphics ��ü ������
	static Input		*input;     // Input ��ü ������
	static Junk2DSound	*audio;		// ���� 

	static Game *nowScene;

					 // --------- ��� �Լ� ---------//

	//������ �޼��� �ڵ鷯
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// ���� �ʱ�ȭ
	virtual void initialize(HWND hwnd); // hwnd�� ������ �ڵ鷯
	virtual void run(HWND);				// �ݺ� ȣ��, ��� ����
	virtual void releaseAll() {};          // �׷��� ����̽� ����
	virtual void resetAll() {};			// ǥ�� ����� �� ��� ��ü ����
	virtual void deleteAll();           // ����� ��� �޸� ����
	virtual void renderGame();          // ���� ������

	Graphics* getGraphics() { return graphics; }	// Graphics ��ü ������ ��ȯ
	Input* getInput() { return input; }		// Input ��ü ������ ��ȯ

	virtual void Update() = 0;		// ���ӿ�� ����
	virtual void render() = 0;		// ������

	virtual void ChangeScene(Game* var);
};


#endif
