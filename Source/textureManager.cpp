#include "..\\Headers\\textureManager.h"

std::vector<std::pair<LP_TEXTURE, const char*>> TextureManager::TextureList;

// 기본 생성자
TextureManager::TextureManager()
{
    texture = NULL;
    width = 0;
    height = 0;
    file = NULL;
    graphics = NULL;
    initialized = false;            
}

// 소멸자
TextureManager::~TextureManager()
{
    SAFE_RELEASE(texture);
}

void TextureManager::AddTextureList(LP_TEXTURE inTexture, const char *file)
{
	TextureList.push_back(std::make_pair(inTexture, file));
}

// 텍스처 로드, 초기화, 실패시 false값 리턴
bool TextureManager::initialize(Graphics *g, const char *f)
{
	graphics = g;                       // graphics 객체
	file = f;                           // 텍스처 파일

	hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);

	initialized = true;                    // 성공적으로 초기화 했을시 true로 설정
	

    return true;
}


