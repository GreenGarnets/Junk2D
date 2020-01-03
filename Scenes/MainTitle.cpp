#include "Scenes.h"

MainTitle::MainTitle()
{
	// ������, �������� �޸� �Ҵ��� ���⼭ ���ش�.

	objectManager = new ObjectManager;

	player = new Junk2DSprite;
	bullet = new Junk2DSprite;
}

MainTitle::~MainTitle()
{
	// �Ҹ��� SAFE_DELETE�� ������Ʈ���� �������ش�.
	objectManager->RemoveAllObject();

	SAFE_DELETE(bullet);
}

void MainTitle::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���, �ʱ�ȭ
	QueryPerformanceFrequency(&timerFreq);

	// �ؽ��� �ҷ�����, �ʱ�ȭ
	// settingTexture(�׷��Ȱ�ü, �����̸�, ����, ����, ��������Ʈ�� ��� ���ٴ� ��� ��������Ʈ�� �ִ���)
	player->settingTexture(graphics, "..\\Resources\\player.png", 128, 256, 6);

	// �Ѿ��� �ؽ��ĸ� �̸� �������°�
	bullet->settingTexture(graphics, "..\\Resources\\player.png", 128, 256, 6);

	// �ִϸ��̼� ���� //

	player->loop = true; // �ִϸ��̼��� ��������
	// �ִϸ��̼� �����Լ�(���� ������, �� ������, ���� �̹����� ������, �ִϸ��̼� ����)
	player->setAnimation(0, 47, 0, 0.2f); 
		/////////////////////

	// ������Ʈ�� ��ġ ����
	player->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	
	// ������Ʈ�� ũ�� ����
	player->setScaleX(4.0f); // (0.5��)
	//player->setScaleX(2.0f);
	bullet->setScale(0.5f); // (0.5��)

	// ������Ʈ �Ŵ����� ���
	// AddObject(����� ������Ʈ, �±�)
	objectManager->AddObject(player, "player");
	
	// bullet������ �Ѿ��� �ؽ��ĸ� �������� ���̱� ������ ������Ʈ �Ŵ����� �߰��� �ʿ� ����
	// ���� ���� ������ �������
	//objectManager->AddObject(bullet, "bullet");

	// ����� ���
	audio->playCue("mainbgm");

	// �̴ϼȶ���� ������
	initialized = true;

	return;
}

// ������Ʈ �Լ�, �̰����� ������ �̺�Ʈ�� ���۵��� �ִ´�.
void MainTitle::Update()
{
	// Ű �Է�
	if (input->isKeyDown(VK_DOWN)) {
		// �÷��̾��� Y�� ���� ����
		player->setY(player->spriteData.y + speed);

		// �ִϸ��̼� ������Ʈ
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_UP)) {
		// �÷��̾��� Y�� ���� ����
		player->setY(player->spriteData.y - speed);
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_LEFT)) {
		// �÷��̾��� X�� ���� ����
		player->setX(player->spriteData.x - speed);
		player->update(frameTime);
	}
	else if (input->isKeyDown(VK_RIGHT)) {
		// �÷��̾��� X�� ���� ����
		player->setX(player->spriteData.x + speed);
		player->update(frameTime);
	}

	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}

	// �Ѿ� �߰�
	if (input->isKeyUp(VK_SPACE)) {
		// �� Junk2DSprite�� ����� ����Ʈ�� �־���
		bullets.push_back(new Junk2DSprite());

		// bullets.back() = ����Ʈ�� ���� ����
		// newSprite(������ ��������Ʈ ������, �׷��Ȱ�ä)
		bullets.back()->newSprite(bullet,graphics);
		bullets.back()->cols = 6;
		//bullets.back()->loop = true; // �ִϸ��̼��� ��������
		bullets.back()->setAnimation(0, 47, 0, 0.2f);

		bullets.back()->setXY(player->spriteData.x, player->spriteData.y);
		objectManager->AddObject(bullets.back(), "bullet");
	}

	// ����Ű�� ������ �� ��ȯ
	if (input->isKeyUp(VK_RETURN)) {
		// �ӽ� GameŬ������ ����, �� Ŭ������ ���� �ٲ۴�
		Game *temp = new TestScene;

		ChangeScene(temp);
	}

	if (input->getMouseX() >= 1200 && input->getMouseLButtonDown()) {
		exit(0);
	}

	// �Ѿ˵� �̵�, �Ÿ� �̻� �־����� ����
	// for (auto i : bullets) = STL�ڷᱸ������ ����Ҽ� �ִ� Ư�� for��
	// bullets��� ����Ʈ�� ó������ ������ �����ϸ�, �Ѱ��� ���Ҵ� i�� �ȴ�.

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

// ���� �Լ�, ������Ʈ���� ó���� ���� �̰����� ������
void MainTitle::render()
{
	graphics->spriteBegin();

	// �̰��� �׷��� ������Ʈ���� �׷��ش�. //

	// ������Ʈ �Ŵ����� ��ϵ� ��� ������Ʈ���� �׷��ش�.
	objectManager->RenderAllObject(0);

	//////////////////////////////////////////

	graphics->spriteEnd();
}
