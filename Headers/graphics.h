#ifndef _GRAPHICS_H            
#define _GRAPHICS_H             
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"

// DirectX 포인터 타입
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define LP_SPRITE	LPD3DXSPRITE
#define LP_TEXTURE  LPDIRECT3DTEXTURE9  // 
#define VECTOR2		D3DXVECTOR2 

// 색상 정의
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

struct SpriteData
{
	int			width;			// 스프라이트의 폭, 높이 (단위는 픽셀)
	int			height;
	float		x;				// 화면 위치
	float		y;
	float		scale;			// 크기
	float		scaleX;			// 크기
	float		angle;			// 라디안 단위의 회전각도
	RECT		rect;			// 큰 텍스처에서 사용할 이미지 선택
	LP_TEXTURE	texture;		// 첵스처를 가리키는 포인터
	bool		flipHorizontal;	// true일 경우 스프라이트를 수평으로 뒤집음
	bool		flipVertical;	// true일 경우 스프라이트를 수직으로 뒤집음
};

class Graphics
{
public:
	// DirectX 포인터
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE	sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// 다른 변수들
	HRESULT     result;         // 윈도우 생성 결과
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB  backColor;      // 배경색

								// D3D 파라미터 수정
	void    initD3Dpp();

	Graphics();
	virtual ~Graphics();

	void    releaseAll();

	// 텍스처를 불러오는 함수
	HRESULT loadTexture(const char *filename, COLOR_ARGB transcolor,
		UINT &width, UINT &height, LP_TEXTURE &Texture, D3DPOOL SystemMemory = D3DPOOL_DEFAULT);


	// SpriteData 구조체의 정보를 토대로 스프라이트 그림
	void drawSprite(const SpriteData &spriteData, COLOR_ARGB color);

	// DirectX 그래픽 초기화
	// hw = handle to window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// 화면에 백버퍼 표시
	HRESULT showBackbuffer();

	// 어뎁터가 호환되는지 체크함
	bool    isAdapterCompatible();


	//============================================
	// 실행 속도를 위한 인라인 함수.
	// 함수 호출 오버헤드를 없애 실행속도를 높임.
	//============================================

	// 화면 클리어
	void setBackColor(COLOR_ARGB c) { backColor = c; }

	// Sprite 그리기 시작
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}

	// Sprite 그리기 종료
	void spriteEnd()
	{
		sprite->End();
	}

	// Scene 시작, 백버퍼 클리어
	HRESULT beginScene() {
		// 백버퍼를 배경색으로 클리어
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene();          // 씬 그리기 시작
		return result;
	}

	// Scene 종료
	HRESULT endScene() {
		result = device3d->EndScene();
		return result;
	}
};

#endif

