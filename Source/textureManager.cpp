#include "..\\Headers\\textureManager.h"

std::vector<std::pair<LP_TEXTURE, const char*>> TextureManager::TextureList;

// �⺻ ������
TextureManager::TextureManager()
{
    texture = NULL;
    width = 0;
    height = 0;
    file = NULL;
    graphics = NULL;
    initialized = false;            
}

// �Ҹ���
TextureManager::~TextureManager()
{
    SAFE_RELEASE(texture);
}

void TextureManager::AddTextureList(LP_TEXTURE inTexture, const char *file)
{
	TextureList.push_back(std::make_pair(inTexture, file));
}

// �ؽ�ó �ε�, �ʱ�ȭ, ���н� false�� ����
bool TextureManager::initialize(Graphics *g, const char *f)
{
	graphics = g;                       // graphics ��ü
	file = f;                           // �ؽ�ó ����

	hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);

	initialized = true;                    // ���������� �ʱ�ȭ ������ true�� ����
	

    return true;
}


