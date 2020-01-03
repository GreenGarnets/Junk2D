#ifndef _IMAGE_H                 
#define _IMAGE_H               
#define WIN32_LEAN_AND_MEAN

#include "textureManager.h"
#include "constants.h"

class Junk2DSprite
{
	// Image ����
public :
	TextureManager *textureManager; // texture manager ��ü�� ����Ű�� ������
	TextureManager texture;

	COLOR_ARGB colorFilter; // ��������Ʈ�� �׸� �� ���ͷ� ������ ����. �ƹ��� ��ȭ�� ������� WHITE����
	int     cols;           // ���� �������� ���� ��������Ʈ�� �� ��
	int     startFrame;     // ���� �������� ���� �ִϸ��̼��� ù��° ������ ��ȣ
	int     endFrame;       // ���� �������� ���� �ִϸ��̼��� ������ ������ ��ȣ
	int     currentFrame;   // �ִϸ��̼��� ���� ������ ��ȣ
	float   frameDelay;     // �ִϸ��̼��� �� �������� ������ �ð��̴�.
	float   animTimer;      // ���ϸ��̼��� �ð��� ���ϱ� ���� ����ϴ� ����
	HRESULT hr;             // ǥ�� ��ȯ��
	bool    loop;           // �ִϸ��̼� �ݺ� ����
	bool    visible;        // �̹����� ���̰� �� ��� true�� ��
	bool    initialized;    // �ʱ�ȭ ����
	bool    animComplete;   // �ִϸ��̼��� �Ϸ� �� ��� true�� ��

	Graphics *graphics;     // graphics ��ü�� ����Ű�� ������
	SpriteData spriteData;  // Graphics::drawSprite() �Լ��� �䱸�ϴ� �����͸� ������ ����ü

	Junk2DSprite();			// ������
	virtual ~Junk2DSprite();	// �Ҹ���

	bool drawable = true;

	////////////////////////////////////////
	//             Set  �Լ���            //
	////////////////////////////////////////

	// X ��ġ ����
	virtual void setX(float newX) { spriteData.x = newX; }
	// Y ��ġ ����
	virtual void setY(float newY) { spriteData.y = newY; }
	// X Y ��ġ ���� ����
	virtual void setXY(float newX, float newY) { spriteData.x = newX;  spriteData.y = newY; }
	// ũ�� ����
	virtual void setScale(float s) { spriteData.scale = s; }
	virtual void setScaleX(float s) { spriteData.scaleX = s; }

	// ȸ�������� �� ������ �����Ѵ�. 0���� ����, ������ �ð� �������� ������.
	virtual void setDegrees(float deg) { spriteData.angle = deg*((float)PI / 180.0f); }

	// visible �Ű������� ����
	virtual void setVisible(bool v) { visible = v; }
	virtual void setCurrentFrame(int c);

	// spriteData.rect�� ���� currentFrame�� �׸��� ����
	virtual void setRect();

	//// Set TextureManager
	virtual void setTextureManager(TextureManager *textureM)
	{
		textureManager = textureM;
	}

	////////////////////////////////////////
	//            �ٸ� �Լ���             //
	////////////////////////////////////////

	// �ʱ�ȭ �Լ� (�ڼ��� ������ .cpp��)
	virtual bool Junk2DSprite::initialize(Graphics *g, int width, int height,
		int ncols, TextureManager *textureM);

	// �̹��� �������� ������
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }
	// �̹��� �������� ������
	virtual void flipVertical(bool flip) { spriteData.flipVertical = flip; }

	// �Լ� ������Ÿ��, �⺻ ������ ���
	virtual void draw(COLOR_ARGB color = D3DCOLOR_ARGB(255, 255, 255, 255));

	virtual void setAnimation(float FrameStart, int FrameEnd, int currentFrame, float FrameDelay);

	// ��������Ʈ �����Ϳ� ���� ���� ��� �ش� �Լ� ȣ��,
	//	��������Ʈ �����͸� �̿��� �׸�
	virtual void draw(SpriteData sd, COLOR_ARGB color = D3DCOLOR_ARGB(255, 255, 255, 255));

	virtual void update(float frameTime);

	virtual void settingTexture(Graphics *g, const char *filename);
	virtual void settingTexture(Graphics *g, const char *filename, int width, int height, int nCols);

	virtual TextureManager* getTexture() { return textureManager; };

	// �ٸ� ��������Ʈ���� ������ ���� �����Ͽ� ���ο� junk2Dsprite�� ����
	virtual void newSprite(Junk2DSprite * oldSprite, Graphics *_graphics);
};

#endif

