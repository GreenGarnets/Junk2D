#include "..\\Headers\\input.h"

Input::Input() // 디폴트 생성자
{
	//-- 키 배열 초기화 --//
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
	//--------------------//

    // mouse data
    mouseX = 0;                         // X 위치
    mouseY = 0;                         // Y 위치
    mouseLButton = false;               // 마우스 왼쪽 버튼을 누를경우 true
    mouseMButton = false;               // 마우스 가운데 버튼을 누를경우 true
    mouseRButton = false;               // 마우스 오른쪽 버튼을 누를경우 true

}

Input::~Input() // 소멸자
{
    if(mouseCaptured)
        ReleaseCapture();               // 마우스 해제
}

void Input::initialize(HWND hwnd, bool capture) // 마우스 초기화, 마우스를 캡쳐하는데 성공시 true값 반환
{
	mouseCaptured = capture;
	SetCapture(hwnd);           // 마우스 캡쳐	
}

void Input::keyDown(WPARAM wParam) // 해당 키에 대해 keysDown과 keyPress 배열을 true로 설정
{
    if (wParam < inputNS::KEYS_ARRAY_LEN) // 키 코드가 버퍼 범위안에 있는지 확인 
    {
        keysDown[wParam] = true;    // 배열 갱신
    }
}

void Input::keyUp(WPARAM wParam) // 해당 키에 대해 keysDown 배열을 false로 설정
{
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = false;
		keysUp[wParam] = true;
	}
}

bool Input::isKeyDown(UCHAR vkey)  // 가상키를 눌렀을 경우 true리턴
{
	if (vkey < inputNS::KEYS_ARRAY_LEN) {
		keysUp[vkey] = keysDown[vkey];
		return keysDown[vkey];
	}
    else
        return false;
}

bool Input::isKeyUp(UCHAR vkey) // 가상키를 눌렀을 경우 true리턴
{
	if (vkey < inputNS::KEYS_ARRAY_LEN && keysDown[vkey] != keysUp[vkey] && keysUp[vkey] == true){
		keysUp[vkey] = false;
		
		return true;
	}
	else
		return false;
}

void Input::clearKeyPress(UCHAR vkey) // 특정 키 입력 정보 클리어
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}

void Input::clear(UCHAR what) // 특정 입력버퍼 클리어
{
    if(what & inputNS::KEYS_DOWN)       
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysDown[i] = false;
    }
    if(what & inputNS::KEYS_PRESSED)    
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysPressed[i] = false;
    }
    if(what & inputNS::MOUSE)           
    {
        mouseX = 0;
        mouseY = 0;
    }
}

void Input::mouseIn(LPARAM lParam) // 마우스 좌표값 저장
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::mouseRawIn(LPARAM lParam) // 정밀 마우스 좌표값을 mouseRawX, mouseRawY에 저장
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
}
