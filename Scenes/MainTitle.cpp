#include "Scenes.h"

MainTitle::MainTitle()
{
	// 생성자, 변수들의 메모리 할당을 여기서 해준다.

	objectManager = new ObjectManager;

	player = new Junk2DSprite;
	bullet = new Junk2DSprite;
}

MainTitle::~MainTitle()
{
	// 소멸자 SAFE_DELETE로 오브젝트들을 삭제해준다.
	objectManager->RemoveAllObject();

	SAFE_DELETE(bullet);
}

void MainTitle::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용, 초기화
	QueryPerformanceFrequency(&timerFreq);

	// 텍스쳐 불러오기, 초기화
	// settingTexture(그래픽객체, 파일이름, 가로, 세로, 스프라이트의 경우 한줄당 몇개의 스프라이트가 있는지)
	player->settingTexture(graphics, "..\\Resources\\player.png", 128, 256, 6);

	// 총알의 텍스쳐만 미리 가져오는것
	bullet->settingTexture(graphics, "..\\Resources\\player.png", 128, 256, 6);

	// 애니메이션 설정 //

	player->loop = true; // 애니메이션의 루프여부
	// 애니메이션 설정함수(시작 프레임, 끝 프레임, 지금 이미지의 프레임, 애니메이션 간격)
	player->setAnimation(0, 47, 0, 0.2f); 
		/////////////////////

	// 오브젝트의 위치 조정
	player->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	
	// 오브젝트의 크기 조정
	player->setScaleX(4.0f); // (0.5배)
	//player->setScaleX(2.0f);
	bullet->setScale(0.5f); // (0.5배)

	// 오브젝트 매니저에 등록
	// AddObject(등록할 오브젝트, 태그)
	objectManager->AddObject(player, "player");
	
	// bullet변수는 총알의 텍스쳐만 가져오는 것이기 때문에 오브젝트 매니저에 추가할 필요 없음
	// 따라서 수동 삭제를 해줘야함
	//objectManager->AddObject(bullet, "bullet");

	// 오디오 재생
	audio->playCue("mainbgm");

	// 이니셜라이즈에 성공함
	initialized = true;

	return;
}

// 업데이트 함수, 이곳에서 게임의 이벤트나 조작등을 넣는다.
void MainTitle::Update()
{
	// 키 입력
	if (input->isKeyDown(VK_DOWN)) {
		// 플레이어의 Y축 방향 조절
		player->setY(player->spriteData.y + speed);

		// 애니메이션 업데이트
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_UP)) {
		// 플레이어의 Y축 방향 조절
		player->setY(player->spriteData.y - speed);
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_LEFT)) {
		// 플레이어의 X축 방향 조절
		player->setX(player->spriteData.x - speed);
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_RIGHT)) {
		// 플레이어의 X축 방향 조절
		player->setX(player->spriteData.x + speed);
		player->update(frameTime);
	}

	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}

	// 총알 추가
	if (input->isKeyUp(VK_SPACE)) {
		// 새 Junk2DSprite를 만들어 리스트에 넣어줌
		bullets.push_back(new Junk2DSprite());

		// bullets.back() = 리스트의 제일 뒤쪽
		// newSprite(복사할 스프라이트 데이터, 그래픽객채)
		bullets.back()->newSprite(bullet,graphics);
		bullets.back()->cols = 6;
		//bullets.back()->loop = true; // 애니메이션의 루프여부
		bullets.back()->setAnimation(0, 47, 0, 0.2f);

		bullets.back()->setXY(player->spriteData.x, player->spriteData.y);
		objectManager->AddObject(bullets.back(), "bullet");
	}

	// 엔터키를 누르면 씬 전환
	if (input->isKeyUp(VK_RETURN)) {
		// 임시 Game클래스를 선언, 이 클래스로 씬을 바꾼다
		Game *temp = new TestScene;

		ChangeScene(temp);
	}

	if (input->getMouseX() >= 1200 && input->getMouseLButtonDown()) {
		exit(0);
	}

	// 총알들 이동, 거리 이상 멀어지면 삭제
	// for (auto i : bullets) = STL자료구조들이 사용할수 있는 특수 for문
	// bullets라는 리스트의 처음부터 끝까지 수행하며, 한개의 원소는 i가 된다.

	if (bullets.back() != NULL) bullets.back()->update(frameTime);
	for (auto i : bullets) {

		i->update(frameTime);
		i->setX(i->spriteData.x + 2);
		if (i->spriteData.x >= 1200) {
			bullets.remove(i);
			objectManager->RemoveObject(i);
		}
	}

	//exitGame();
}

// 랜더 함수, 업데이트에서 처리한 이후 이곳에서 렌더링
void MainTitle::render()
{
	graphics->spriteBegin();

	// 이곳에 그려줄 오브젝트들을 그려준다. //

	// 오브젝트 매니저에 등록된 모든 오브젝트들을 그려준다.
	objectManager->RenderAllObject(0);

	//////////////////////////////////////////

	graphics->spriteEnd();
}
