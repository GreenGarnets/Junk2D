#include "..\\Headers\\Junk2DSprite.h"

// 생성자, 소멸자
Junk2DSprite::Junk2DSprite()
{
	initialized = false;            // set true when successfully initialized
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.scaleX = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       // used to select one frame from multi-frame Junk2DSprite
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;      // the sprite texture (picture)
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	textureManager = NULL;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0;               // default to 1 second per frame of animation
	animTimer = 0.0;
	visible = true;                 // the Junk2DSprite is visible
	loop = true;                    // loop frames
	animComplete = false;
	graphics = NULL;                // link to graphics system
	colorFilter = D3DCOLOR_ARGB(255, 255, 255, 255);; // WHITE for no change
}
Junk2DSprite::~Junk2DSprite()
{}

// Junk2DSprite 객체 초기화
// 성공하면 true, 실패하면 false 반환
// Graphics를 가리키는 포인터
// 이미지의 픽셀 단위 폭, 높이, 텍스처의 행 수(1 ~ n)
// TextureManager를 가리키는 포인터
bool Junk2DSprite::initialize(Graphics *g, int width, int height, int ncols,
	TextureManager *textureM)
{
	graphics = g;                               // graphics 객체
	textureManager = textureM;                  // 텍스처 객체를 가리키는 포인터

	spriteData.texture = textureManager->getTexture();
	spriteData.width = width;
	spriteData.height = height;
	cols = ncols;

	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	
	initialized = true;
	return true;
}


//=============================================================================
// color를 필터로 사용하여 이미지를 그림
// 이전에 spriteBegin()이 호출 되며,
// 이후 spriteEnd() 이 호출 된다.
//=============================================================================
void Junk2DSprite::draw(COLOR_ARGB color)
{
	spriteData.texture = textureManager->getTexture();
	graphics->drawSprite(spriteData, color);        // color를 필터로 사용
}

void Junk2DSprite::draw(SpriteData sd, COLOR_ARGB color)
{
	sd.rect = spriteData.rect;  
	sd.texture = textureManager->getTexture();
	graphics->drawSprite(sd, color);        // color를 필터로 사용
}

void Junk2DSprite::update(float frameTime)
{
	if (endFrame - startFrame > 0)          // 애니메이션 동작이 있는 스프라이트 일 경우
	{
		animTimer += frameTime;             // 전체 경과 시간 추가
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)            // 반복하는 애니메이션일 경우
					currentFrame = startFrame;
				else                         // 반복하지 않는 애니메이션일 경우
				{
					currentFrame = endFrame;
					animComplete = true;     // 애니메이션 완료
				}
			}
			setRect();                       // spriteData.rect 다시 설정
		}
	}
}

void Junk2DSprite::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect();                          // set spriteData.rect
	}
}

void Junk2DSprite::settingTexture(Graphics *g, const char *filename)
{
	// 텍스쳐 설정, 초기화
	texture.initialize(g, filename);
	this->initialize(g, 0, 0, 0, &texture);
}

void Junk2DSprite::settingTexture(Graphics * g, const char * filename, int width, int height, int nCols)
{
	// 텍스쳐 초기화
	texture.initialize(g, filename);
	this->initialize(g, width, height, nCols, &texture);
}

void Junk2DSprite::newSprite(Junk2DSprite * oldSprite, Graphics *_graphics)
{
	this->setTextureManager(oldSprite->getTexture());
	this->graphics = _graphics;
	this->texture = oldSprite->texture;
	this->spriteData = oldSprite->spriteData;
}

// 애니메이션 설정 함수
void Junk2DSprite::setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay)
{
	startFrame = FrameStart; 
	endFrame = FrameEnd;
	frameDelay = FrameDelay;
	this->setCurrentFrame(currentFrame);
}

// currentFrame에 그리기 위하여 spriteData.rect를 설정
inline void Junk2DSprite::setRect()
{
	// currentFrame에 그리기 위하여 spriteData.rect를 설정
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// right edge + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// bottom edge + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}


