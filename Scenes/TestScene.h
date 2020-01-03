#ifndef _TESTSCENE_H             
#define _TESTSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class TestScene : public Game
{
private:
	// ������Ʈ �Ŵ���, ������Ʈ���� ���⿡ ��� �����Ѵ�.
	ObjectManager* objectManager;

	// ��������Ʈ ����
	Junk2DSprite* bg;

public:
	TestScene();
	virtual ~TestScene();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
