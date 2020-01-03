#include "Scenes.h"

TestScene::TestScene()
{
	// ������, �������� �޸� �Ҵ��� ���⼭ ���ش�.

	objectManager = new ObjectManager;

	bg = new Junk2DSprite;
}

TestScene::~TestScene()
{
	// �Ҹ��� SAFE_DELETE�� ������Ʈ���� �������ش�.
	objectManager->RemoveAllObject();

	//SAFE_DELETE(player);
}

void TestScene::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���, �ʱ�ȭ
	QueryPerformanceFrequency(&timerFreq);

	audio->stopCue("mainbgm");

	// �̴ϼȶ���� ������
	initialized = true;

	return;
}

// ������Ʈ �Լ�, �̰����� ������ �̺�Ʈ�� ���۵��� �ִ´�.
void TestScene::Update()
{
	// Ű �Է�
	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}
	if (input->isKeyUp(VK_RETURN)) {
		// �ӽ� GameŬ������ ����, �� Ŭ������ ���� �ٲ۴�
		Game *temp = new MainTitle;

		ChangeScene(temp);
	}
	// ����Ű�� ������ �� ��ȯ
	if (input->isKeyUp(VK_RETURN)) {
	}

	//exitGame();
}

// ���� �Լ�, ������Ʈ���� ó���� ���� �̰����� ������
void TestScene::render()
{
	graphics->spriteBegin();

	// �̰��� �׷��� ������Ʈ���� �׷��ش�. //

	// ������Ʈ �Ŵ����� ��ϵ� ��� ������Ʈ���� �׷��ش�.
	objectManager->RenderAllObject(0);

	//////////////////////////////////////////

	graphics->spriteEnd();
}
