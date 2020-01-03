#ifndef _GRAPHICS_H            
#define _GRAPHICS_H             
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"

// DirectX ������ Ÿ��
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define LP_SPRITE	LPD3DXSPRITE
#define LP_TEXTURE  LPDIRECT3DTEXTURE9  // 
#define VECTOR2		D3DXVECTOR2 

// ���� ����
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

struct SpriteData
{
	int			width;			// ��������Ʈ�� ��, ���� (������ �ȼ�)
	int			height;
	float		x;				// ȭ�� ��ġ
	float		y;
	float		scale;			// ũ��
	float		scaleX;			// ũ��
	float		angle;			// ���� ������ ȸ������
	RECT		rect;			// ū �ؽ�ó���� ����� �̹��� ����
	LP_TEXTURE	texture;		// ý��ó�� ����Ű�� ������
	bool		flipHorizontal;	// true�� ��� ��������Ʈ�� �������� ������
	bool		flipVertical;	// true�� ��� ��������Ʈ�� �������� ������
};

class Graphics
{
public:
	// DirectX ������
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE	sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// �ٸ� ������
	HRESULT     result;         // ������ ���� ���
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // ����

								// D3D �Ķ���� ����
	void    initD3Dpp();

	Graphics();
	virtual ~Graphics();

	void    releaseAll();

	// �ؽ�ó�� �ҷ����� �Լ�
	HRESULT loadTexture(const char *filename, COLOR_ARGB transcolor,
		UINT &width, UINT &height, LP_TEXTURE &Texture, D3DPOOL SystemMemory = D3DPOOL_DEFAULT);


	// SpriteData ����ü�� ������ ���� ��������Ʈ �׸�
	void drawSprite(const SpriteData &spriteData, COLOR_ARGB color);

	// DirectX �׷��� �ʱ�ȭ
	// hw = handle to window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// ȭ�鿡 ����� ǥ��
	HRESULT showBackbuffer();

	// ��Ͱ� ȣȯ�Ǵ��� üũ��
	bool    isAdapterCompatible();


	//============================================
	// ���� �ӵ��� ���� �ζ��� �Լ�.
	// �Լ� ȣ�� ������带 ���� ����ӵ��� ����.
	//============================================

	// ȭ�� Ŭ����
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	// Sprite �׸��� ����
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	// Sprite �׸��� ����
	void spriteEnd()
	{
		sprite->End();
	}

	// Scene ����, ����� Ŭ����
	HRESULT beginScene() {
		// ����۸� �������� Ŭ����
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene();          // �� �׸��� ����
		return result;
	}

	// Scene ����
	HRESULT endScene() {
		result = device3d->EndScene();
		return result;
	}
};

#endif
