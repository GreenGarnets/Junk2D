#ifndef _MAINTITLE_H             
#define _MAINTITLE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainTitle : public Game
{
private:
	// ������Ʈ �Ŵ���, ������Ʈ���� ���⿡ ��� �����Ѵ�.
	ObjectManager* objectManager;

	// ��������Ʈ ����
	Junk2DSprite* player;
	Junk2DSprite* bullet;

	std::list<Junk2DSprite*> bullets;

	int speed = 1;

	int scene = 0;

	float timeCount = 0;

public:
	MainTitle();
	virtual ~MainTitle();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
