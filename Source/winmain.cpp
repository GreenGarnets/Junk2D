#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>             
#include <crtdbg.h>             

#include "..\\Scenes\MainTitle.h"

// �Լ� ������Ÿ��
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 

// ���� ������
Game*			game;
Game*			beforeScene;
Game*			nextScene;
Game* 			Game::nowScene = NULL;

HWND hwnd = NULL;

BOOL switchScene = false;

//extern int SceneNum;

// ������ ���ø����̼� ��������(����)
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // ���� ����
    game = new MainTitle;

	Game::graphics = new Graphics();
	Game::input = new Input();
	Game::audio = new Junk2DSound();

    // ������ ����
	CreateMainWindow(hwnd, hInstance, nCmdShow);

    game->Game::initialize(hwnd);
	game->initialize(hwnd);

    // ���� �޼��� ����
    int done = 0;

    while (!done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                done = 1;

            TranslateMessage(&msg); // WinProc�� �޼��� ����
            DispatchMessage(&msg);
        } 
		else {
			game->run(hwnd); // ���� ���� ����
		}


		if (switchScene) {

			game = nextScene;
		
			beforeScene->~Game();
			SAFE_DELETE(beforeScene);

			game->initialize(hwnd);

			switchScene = false;
		}
    }


    return msg.wParam;
   

	SAFE_DELETE(game);     // �������� �޸� ����
	
    
    return 0;
}

// ������ �̺�Ʈ �ݹ�
LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return (game->messageHandler(hwnd, msg, wParam, lParam));
}

// ������ ����
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) 
{ 
    WNDCLASSEX wcx; 
 
	// Window Ŭ���� ����ü�� ���� �����쿡 ���� ������ ä��
    wcx.cbSize = sizeof(wcx);           // ����ü�� ũ�� 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // ũ�Ⱑ ���Ұ�� �ٽ� �׸�
    wcx.lpfnWndProc = WinProc;          // ������ ���ν����� ��ٸ�
    wcx.cbClsExtra = 0;                 // ������ Ŭ����,������ �޸𸮴� �ʿ� ����.
    wcx.cbWndExtra = 0;                 
    wcx.hInstance = hInstance;          // �ν��Ͻ��� �ڵ�
    wcx.hIcon = NULL; 
    wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // �̸� ���ǵ� ȭ��ǥ
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // ���
    wcx.lpszMenuName =  NULL;           // �޴� ���ҽ� �̸�
    wcx.lpszClassName = CLASS_NAME;     // ������ Ŭ������ �̸� 
    wcx.hIconSm = NULL;                 // ���� Ŭ���� ������
 
    // ������ Ŭ������ ���
    if (RegisterClassEx(&wcx) == 0)    // ��������
        return false;

    //������ Ǯ��ũ�� ����
    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_DLGMODALFRAME | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW;


    // ������ ����
    hwnd = CreateWindow(
        CLASS_NAME,             // ������ Ŭ���� �̸�
        GAME_TITLE,             // ����ǥ������ �ؽ�Ʈ
        style,                  // ������ ��Ÿ��
        CW_USEDEFAULT,          // �������� ������ġ
        CW_USEDEFAULT,          // ���� ��ġ
        GAME_WIDTH,             // ��
        GAME_HEIGHT,            // ����
        (HWND) NULL,            // �θ� ������ ����
        (HMENU) NULL,           // �޴� ����
        hInstance,              // ���ø����̼� �ν��Ͻ��� �ڵ�
        (LPVOID) NULL);         // ������ �Ű����� ����

    if (!hwnd) // ���� ����
        return false;

    if(!FULLSCREEN)             // �������� ���
    {
        // Ŭ���̾�Ʈ ������ âũ�� ����
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);   // ������ �� �κ� ũ��
        MoveWindow(hwnd,
                   0,                                           // ����
                   0,                                           // ��
                   GAME_WIDTH+(GAME_WIDTH-clientRect.right),    // ������
                   GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), // �Ʒ���
                   TRUE);                                       // ������ �ٽ�ĥ��
    }

    // ������ ǥ��
    ShowWindow(hwnd, nCmdShow);

    return true;
}


