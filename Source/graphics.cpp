#include "..\\Headers\\graphics.h"

Graphics::Graphics(){
    direct3d = NULL;
    device3d = NULL;
    fullscreen = false;
    width = GAME_WIDTH;    // 게임 가로 세로크기 초기화
    height = GAME_HEIGHT;
    backColor = SETCOLOR_ARGB(255,0,0,0); // 배경색
}

Graphics::~Graphics(){
    releaseAll();
}

void Graphics::releaseAll(){
    SAFE_RELEASE(device3d);
    SAFE_RELEASE(direct3d);
}

// DirectX 초기화
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
    hwnd = hw;
    width = w;
    height = h;
    fullscreen = full;

    // Direct3D 초기화
    direct3d = Direct3DCreate9(D3D_SDK_VERSION);

    initD3Dpp();        // D3D 프리젠테이션 파라미터 초기화
    if(isAdapterCompatible()) d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;

    D3DCAPS9 caps;
    DWORD behavior;
    result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  

    //Direct3D 디바이스 생성
    result = direct3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        behavior,
        &d3dpp, 
        &device3d);

	result = D3DXCreateSprite(device3d,&sprite);
 
}

// D3D 프리젠테이션 파라미터 초기화
void Graphics::initD3Dpp(){
        ZeroMemory(&d3dpp, sizeof(d3dpp));     
		
        d3dpp.BackBufferWidth   = width;			   // 해상도 조정, width와 height은 constants에 포함되어 있음
        d3dpp.BackBufferHeight  = height;

		if (fullscreen)                                // 풀스크린 여부
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24비트 색상
        else
            d3dpp.BackBufferFormat  = D3DFMT_UNKNOWN;   // 데스크톱에 맞춘 셋팅

        d3dpp.BackBufferCount   = 1;
        d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow     = hwnd;
        d3dpp.Windowed          = (!fullscreen);					  // 윈도우or 풀스크린 여부
        d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE; // 수직 동기화 옵션


    
}

void Graphics::drawSprite(const SpriteData &spriteData, COLOR_ARGB color){	
	if (spriteData.texture == NULL) // 텍스처가 없을경우 그냥 종료
		return;

	// 스프라이트의 중심을 찾음
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(
		(float)(spriteData.width/2 * spriteData.scaleX),
		(float)(spriteData.height/2 * spriteData.scale));

	// 스프라이트의 화면 위치
	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x, (float)spriteData.y);

	// x, y 크기 조정
	D3DXVECTOR2 scaling(spriteData.scaleX, spriteData.scale);

	// 수평으로 뒤집기
	if (spriteData.flipHorizontal) {
		scaling.x *= -1;
		// 뒤집은 이미지의 중심을 가져옴
		spriteCenter.x -= (float)(spriteData.width / 2 * spriteData.scale);
		// 뒤집은 이미지를 오른쪽으로 이동시켜 원래 위치에 있게함
		translate.x += (float)(spriteData.width * spriteData.scale);
	}

	// 수직으로 뒤집기
	if (spriteData.flipVertical) {
		scaling.y *= -1;
		spriteCenter.y -= (float)(spriteData.height / 2 * spriteData.scale);
		translate.y += (float)(spriteData.height * spriteData.scale);
	}

	// 스프라이트를 회전, 크기 조정, 배치하기 위한 행렬을 생성한다.
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,					// 행렬
		NULL,						// 기준점을 왼쪽 상단으로 유지
		0.0f,						// 크기 조정 회전 없음
		&scaling,					// 크기 조정 값
		&spriteCenter,				// 회전 중심
		(float)(spriteData.angle),	// 회전 각도
		&translate					// X, Y 위치
	);

	// 스프라이트에게 행렬에 대해 알려준다.
	sprite->SetTransform(&matrix);

	// 스프라이트를 그린다.
	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);

	// ------------------------------------------------------------------ //
	// 그래픽스 신 시작 -> 스프라이트 시작 -> 행렬을 통한 스프라이트 변환 // 
	// -> 스프라이트 그리기(또는 행렬을 통한 스프라이트 변환으로 반복) -> //
	// 스프라이트 종료 -> 그래픽스 신 종료		                          //
	// ------------------------------------------------------------------ //
}

HRESULT Graphics::loadTexture(const char *filename, COLOR_ARGB transcolor,
								UINT &width, UINT &height, LP_TEXTURE &texture, D3DPOOL SystemMemory){
	
	// 파일 정보를 읽기 위한 구조체
	D3DXIMAGE_INFO info;

	// 파일로부터 폭과 높이를 얻어냄
	result = D3DXGetImageInfoFromFile(filename,&info);
	if (result != D3D_OK) {
		return result;
	}
	width = info.Width;
	height = info.Height;
		
	// 파일을 불러와 새 택스처 생성
	result = D3DXCreateTextureFromFileEx(
		device3d,			// 3D 디바이스			
		filename,			// 이미지 파일명
		info.Width,			// 텍스처 폭, 높이
		info.Height,
		1,					// 밉맵 수준(연결하지 않을 시 1사용)
		0,					// 사용할것 (DWORD Usage)
		D3DFMT_UNKNOWN,		// 표면형식
		SystemMemory,	// 텍스처를 위한 메모리 클래스
		D3DX_DEFAULT,		// 이미지 필터
		D3DX_DEFAULT,		// 밉 필터
		transcolor,			// 투명도를 위한 색상 키
		&info,				// 비트맵 파일 정보
		NULL,				// 색상 팔레트
		&texture			// 텍스처
		);

	return result;
}

// 디스플레이 백버퍼
HRESULT Graphics::showBackbuffer(){
    result = E_FAIL;    // 평소에는 FAIL로, 성공하면 전환
    // 백버퍼 스크린 설정
    result = device3d->Present(NULL, NULL, NULL, NULL);
    return result;
}

// 어뎁터가 호환되는지 체크
bool Graphics::isAdapterCompatible(){
    UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, 
                                            d3dpp.BackBufferFormat);
    for(UINT i=0; i<modes; i++){
        result = direct3d->EnumAdapterModes( D3DADAPTER_DEFAULT, 
                                        d3dpp.BackBufferFormat,
                                        i, &pMode);
        if( pMode.Height == d3dpp.BackBufferHeight &&
            pMode.Width  == d3dpp.BackBufferWidth &&
            pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
            return true;
    }
    return false;
}

