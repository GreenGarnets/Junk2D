#include "Scenes.h"

TestScene::TestScene()
{
	// 생성자, 변수들의 메모리 할당을 여기서 해준다.

	objectManager = new ObjectManager;

	bg = new Junk2DSprite;
}

TestScene::~TestScene()
{
	// 소멸자 SAFE_DELETE로 오브젝트들을 삭제해준다.
	objectManager->RemoveAllObject();

	//SAFE_DELETE(player);
}

void TestScene::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용, 초기화
	QueryPerformanceFrequency(&timerFreq);

	audio->stopCue("mainbgm");

	// 이니셜라이즈에 성공함
	initialized = true;

	return;
}

// 업데이트 함수, 이곳에서 게임의 이벤트나 조작등을 넣는다.
void TestScene::Update()
{
	// 키 입력
	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}
	if (input->isKeyUp(VK_RETURN)) {
		// 임시 Game클래스를 선언, 이 클래스로 씬을 바꾼다
		Game *temp = new MainTitle;

		ChangeScene(temp);
	}
	// 엔터키를 누르면 씬 전환
	if (input->isKeyUp(VK_RETURN)) {
	}

	//exitGame();
}

// 랜더 함수, 업데이트에서 처리한 이후 이곳에서 렌더링
void TestScene::render()
{
	graphics->spriteBegin();

	// 이곳에 그려줄 오브젝트들을 그려준다. //

	// 오브젝트 매니저에 등록된 모든 오브젝트들을 그려준다.
	objectManager->RenderAllObject(0);

	//////////////////////////////////////////

	graphics->spriteEnd();
}
