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
    const int KEYS_ARRAY_LEN = 256;		// Ű �迭 ũ��
    
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}				

class Input
{
private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // Ư�� Ű�� ���� ��� true�� �Ǵ� �迭 
	bool keysUp[inputNS::KEYS_ARRAY_LEN];     // Ư�� Ű�� �� ��� true�� �Ǵ� �迭 
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // ���� ������ �����ϴ� ���� Ư�� Ű�� ���� ��� true�� �Ǵ� �迭 
    int  mouseX, mouseY;                        // ȭ�� ���� ���콺 ��ġ
    bool mouseCaptured;                         // ���콺�� ĸ�ĵ� ��� true�� ��
    bool mouseLButton;                          // ���콺 ���� ��ư�� ���� ��� true�� 

	bool mouseLButtonDown;                          // ���콺 ���� ��ư�� ���� ��� true�� ��

    bool mouseMButton;                          // ���콺 ��� ��ư�� ���� ��� true�� ��
    bool mouseRButton;                          // ���콺 ������ ��ư�� ���� ��� true�� ��

public:
    Input(); // ������
    virtual ~Input(); // �Ҹ���

    void initialize(HWND hwnd, bool capture); // �Է� �ʱ�ȭ

    void keyDown(WPARAM);	// Ű ���� ����
    void keyUp(WPARAM);

	bool isKeyUp(UCHAR vkey);			//	
    bool isKeyDown(UCHAR vkey);		// ����Ű�� ������ ��� true����

    void clearKeyPress(UCHAR vkey);						// Ư�� Ű �Է� ���� Ŭ����
    void clear(UCHAR what);								// Ư�� �Է¹��� Ŭ����
    void clearAll() {clear(inputNS::KEYS_MOUSE_TEXT);}	// ��� �Է� ���� Ŭ����

    void mouseIn(LPARAM);		// ���콺 ��ǥ���� mouseX, mouseY�� ����
    void mouseRawIn(LPARAM);	// ���� ���콺 ��ǥ���� mouseRawX, mouseRawY�� ����

	//---- ���콺 ��ư ���� ���� ----//
    void setMouseLButton(bool b) { mouseLButton = b; }
	void setMouseLButtonDown(bool b) { mouseLButtonDown = b; }
    void setMouseMButton(bool b) { mouseMButton = b; } 
    void setMouseRButton(bool b) { mouseRButton = b; } 
    //-------------------------------//

	// ���콺 ��ġ�� ��ȯ
    int  getMouseX()        const { return mouseX; }
    int  getMouseY()        const { return mouseY; }

    // ��ư ���� ��ȯ
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

