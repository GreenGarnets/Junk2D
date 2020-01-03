#include "..\\Headers\\input.h"

Input::Input() // ����Ʈ ������
{
	//-- Ű �迭 �ʱ�ȭ --//
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
	//--------------------//

    // mouse data
    mouseX = 0;                         // X ��ġ
    mouseY = 0;                         // Y ��ġ
    mouseLButton = false;               // ���콺 ���� ��ư�� ������� true
    mouseMButton = false;               // ���콺 ��� ��ư�� ������� true
    mouseRButton = false;               // ���콺 ������ ��ư�� ������� true

}

Input::~Input() // �Ҹ���
{
    if(mouseCaptured)
        ReleaseCapture();               // ���콺 ����
}

void Input::initialize(HWND hwnd, bool capture) // ���콺 �ʱ�ȭ, ���콺�� ĸ���ϴµ� ������ true�� ��ȯ
{
	mouseCaptured = capture;
	SetCapture(hwnd);           // ���콺 ĸ��	
}

void Input::keyDown(WPARAM wParam) // �ش� Ű�� ���� keysDown�� keyPress �迭�� true�� ����
{
    if (wParam < inputNS::KEYS_ARRAY_LEN) // Ű �ڵ尡 ���� �����ȿ� �ִ��� Ȯ�� 
    {
        keysDown[wParam] = true;    // �迭 ����
    }
}

void Input::keyUp(WPARAM wParam) // �ش� Ű�� ���� keysDown �迭�� false�� ����
{
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = false;
		keysUp[wParam] = true;
	}
}

bool Input::isKeyDown(UCHAR vkey)  // ����Ű�� ������ ��� true����
{
	if (vkey < inputNS::KEYS_ARRAY_LEN) {
		keysUp[vkey] = keysDown[vkey];
		return keysDown[vkey];
	}
    else
        return false;
}

bool Input::isKeyUp(UCHAR vkey) // ����Ű�� ������ ��� true����
{
	if (vkey < inputNS::KEYS_ARRAY_LEN && keysDown[vkey] != keysUp[vkey] && keysUp[vkey] == true){
		keysUp[vkey] = false;
		
		return true;
	}
	else
		return false;
}

void Input::clearKeyPress(UCHAR vkey) // Ư�� Ű �Է� ���� Ŭ����
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}

void Input::clear(UCHAR what) // Ư�� �Է¹��� Ŭ����
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

void Input::mouseIn(LPARAM lParam) // ���콺 ��ǥ�� ����
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}

void Input::mouseRawIn(LPARAM lParam) // ���� ���콺 ��ǥ���� mouseRawX, mouseRawY�� ����
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
}
