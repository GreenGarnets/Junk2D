#include "..\\Headers\\Junk2DSprite.h"

// ������, �Ҹ���
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

// Junk2DSprite ��ü �ʱ�ȭ
// �����ϸ� true, �����ϸ� false ��ȯ
// Graphics�� ����Ű�� ������
// �̹����� �ȼ� ���� ��, ����, �ؽ�ó�� �� ��(1 ~ n)
// TextureManager�� ����Ű�� ������
bool Junk2DSprite::initialize(Graphics *g, int width, int height, int ncols,
	TextureManager *textureM)
{
	graphics = g;                               // graphics ��ü
	textureManager = textureM;                  // �ؽ�ó ��ü�� ����Ű�� ������

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
// color�� ���ͷ� ����Ͽ� �̹����� �׸�
// ������ spriteBegin()�� ȣ�� �Ǹ�,
// ���� spriteEnd() �� ȣ�� �ȴ�.
//=============================================================================
void Junk2DSprite::draw(COLOR_ARGB color)
{
	spriteData.texture = textureManager->getTexture();
	graphics->drawSprite(spriteData, color);        // color�� ���ͷ� ���
}

void Junk2DSprite::draw(SpriteData sd, COLOR_ARGB color)
{
	sd.rect = spriteData.rect;  
	sd.texture = textureManager->getTexture();
	graphics->drawSprite(sd, color);        // color�� ���ͷ� ���
}

void Junk2DSprite::update(float frameTime)
{
	if (endFrame - startFrame > 0)          // �ִϸ��̼� ������ �ִ� ��������Ʈ �� ���
	{
		animTimer += frameTime;             // ��ü ��� �ð� �߰�
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)            // �ݺ��ϴ� �ִϸ��̼��� ���
					currentFrame = startFrame;
				else                         // �ݺ����� �ʴ� �ִϸ��̼��� ���
				{
					currentFrame = endFrame;
					animComplete = true;     // �ִϸ��̼� �Ϸ�
				}
			}
			setRect();                       // spriteData.rect �ٽ� ����
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
	// �ؽ��� ����, �ʱ�ȭ
	texture.initialize(g, filename);
	this->initialize(g, 0, 0, 0, &texture);
}

void Junk2DSprite::settingTexture(Graphics * g, const char * filename, int width, int height, int nCols)
{
	// �ؽ��� �ʱ�ȭ
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

// �ִϸ��̼� ���� �Լ�
void Junk2DSprite::setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay)
{
	startFrame = FrameStart; 
	endFrame = FrameEnd;
	frameDelay = FrameDelay;
	this->setCurrentFrame(currentFrame);
}

// currentFrame�� �׸��� ���Ͽ� spriteData.rect�� ����
inline void Junk2DSprite::setRect()
{
	// currentFrame�� �׸��� ���Ͽ� spriteData.rect�� ����
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// right edge + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// bottom edge + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}


