#ifndef _TESTSCENE_H             
#define _TESTSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class TestScene : public Game
{
private:
	// 오브젝트 매니저, 오브젝트들을 여기에 담아 관리한다.
	ObjectManager* objectManager;

	// 스프라이트 변수
	Junk2DSprite* bg;

public:
	TestScene();
	virtual ~TestScene();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
