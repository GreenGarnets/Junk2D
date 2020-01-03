#ifndef _INPUT_H                
#define _INPUT_H                
#define WIN32_LEAN_AND_MEAN

class Input;

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "constants.h"

namespace inputNS
{
    const int KEYS_ARRAY_LEN = 256;		// 키 배열 크기
    
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}				

class Input
{
private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // 특정 키를 누른 경우 true가 되는 배열 
	bool keysUp[inputNS::KEYS_ARRAY_LEN];     // 특정 키를 뗀 경우 true가 되는 배열 
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // 게임 루프가 동작하는 동안 특정 키를 누른 경우 true가 되는 배열 
    int  mouseX, mouseY;                        // 화면 위의 마우스 위치
    bool mouseCaptured;                         // 마우스가 캡쳐된 경우 true가 됨
    bool mouseLButton;                          // 마우스 왼쪽 버튼을 누른 경우 true가 

	bool mouseLButtonDown;                          // 마우스 왼쪽 버튼을 누른 경우 true가 됨

    bool mouseMButton;                          // 마우스 가운데 버튼을 누른 경우 true가 됨
    bool mouseRButton;                          // 마우스 오른쪽 버튼을 누른 경우 true가 됨

public:
    Input(); // 생성자
    virtual ~Input(); // 소멸자

    void initialize(HWND hwnd, bool capture); // 입력 초기화

    void keyDown(WPARAM);	// 키 상태 저장
    void keyUp(WPARAM);

	bool isKeyUp(UCHAR vkey);			//	
    bool isKeyDown(UCHAR vkey);		// 가상키를 눌렀을 경우 true리턴

    void clearKeyPress(UCHAR vkey);						// 특정 키 입력 정보 클리어
    void clear(UCHAR what);								// 특정 입력버퍼 클리어
    void clearAll() {clear(inputNS::KEYS_MOUSE_TEXT);}	// 모든 입력 정보 클리어

    void mouseIn(LPARAM);		// 마우스 좌표값을 mouseX, mouseY에 저장
    void mouseRawIn(LPARAM);	// 정밀 마우스 좌표값을 mouseRawX, mouseRawY에 저장

	//---- 마우스 버튼 상태 저장 ----//
    void setMouseLButton(bool b) { mouseLButton = b; }
	void setMouseLButtonDown(bool b) { mouseLButtonDown = b; }
    void setMouseMButton(bool b) { mouseMButton = b; } 
    void setMouseRButton(bool b) { mouseRButton = b; } 
    //-------------------------------//

	// 마우스 위치값 반환
    int  getMouseX()        const { return mouseX; }
    int  getMouseY()        const { return mouseY; }

    // 버튼 상태 반환
    bool getMouseLButton()  const { return mouseLButton; }
	bool getMouseLButtonDown()  const { return mouseLButtonDown; }
    bool getMouseMButton()  const { return mouseMButton; }
    bool getMouseRButton()  const { return mouseRButton; }

	void InputEventReset() {
		mouseLButtonDown = false;
		for (int i = 0; i < 256;i++) {
			keysUp[i] = false;
		}

	};
};

#endif

