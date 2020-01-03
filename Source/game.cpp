#include "..\\Headers\\game.h"

Graphics*		Game::graphics = new Graphics();
Input*			Game::input = new Input();
Junk2DSound*	Game::audio = new Junk2DSound();

Game::Game()
{
    paused = false;   
    initialized = false;
}

Game::~Game()
{
    ShowCursor(true);           // Ŀ�� ǥ��
}

LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) // ������ �޼��� ��鷯
{
    if(initialized)     // �ʱ�ȭ ���� ��쿡�� ó��
    {
        switch( msg )
        {

			// ������ �ڵ鷯 �ڵ带 InputŬ�󽺷� ����

            case WM_DESTROY:
                PostQuitMessage(0);        // ����
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // Ű ����
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // Ű ��
                input->keyUp(wParam);
                return 0;
            case WM_MOUSEMOVE:                      // ���콺 ������
                input->mouseIn(lParam);
                return 0;
            case WM_INPUT:                          // ���콺 �����Ͱ� ����
                input->mouseRawIn(lParam);
                return 0;
            case WM_LBUTTONDOWN:                    // ���콺 ���ʹ�ư ����
                input->setMouseLButton(true);
                input->mouseIn(lParam);             // ���콺 ��ġ
                return 0;
            case WM_LBUTTONUP:                      // ���콺 ���ʹ�ư ��
                input->setMouseLButton(false);
				input->setMouseLButtonDown(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONDOWN:                    // ���콺 ��� ��ư ����
                input->setMouseMButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONUP:                      // ���콺 ��� ��ư ��
                input->setMouseMButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONDOWN:                    // ���콺 ������ ��ư ����
                input->setMouseRButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONUP:                      // ���콺 ������ ��ư ��
                input->setMouseRButton(false);
                input->mouseIn(lParam);             
                return 0;
			case WM_SETCURSOR:
				graphics->device3d->ShowCursor(TRUE);
				return TRUE; // prevent Windows from setting cursor to window class cursor

				break;

        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // �����찡 ó���ϰ� ��
}

// ���� �ʱ�ȭ
void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // ������ �ڵ� ����
   
	// ��üȭ��� �׷��� ��ü�� �ι� �����Ǹ鼭 ������ ����µ���. �����ʿ�.
	// �׷��� ��ü ���� static���� ����� ��� �ҵ���.
   
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);	// ���� ������ ��´�

	audio->initialize();

    // Input��ü �ʱ�ȭ
    input->initialize(hwnd, false);            

    // Ÿ�̸� ���
	QueryPerformanceFrequency(&timerFreq);
        
    QueryPerformanceCounter(&timeStart);        // ���� �ð� ��������

	// ������ �̴ϼȶ����� ��
    initialized = true;
}

// ���� ������
void Game::renderGame()
{
	graphics->beginScene();
    render();               // �Ļ�Ŭ�������� render�� ȣ��
    graphics->endScene();	// �������� �����

    graphics->showBackbuffer(); // �� ���� ǥ��
}

void Game::run(HWND hwnd)
{
    if(graphics == NULL)            
        return;

	// ������ ����Ʈ ���
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / 
                (float)timerFreq.QuadPart;

	// ���� �ڵ�, Winnm.lib �ʿ�
    if (frameTime < MIN_FRAME_TIME) 
    {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         
        Sleep(sleepTime);           // cpu�� �����Ѵ�.
        timeEndPeriod(1);           
        return;
    }

    if (frameTime > 0.0)
        fps = (fps*0.99f) + (0.01f/frameTime);  // ��� FPS

    if (frameTime > MAX_FRAME_TIME) // ������ �ӵ��� ������� �ִ� frameTime���� ����
        frameTime = MAX_FRAME_TIME; // �ִ� frameTime���� ����

    timeStart = timeEnd;

	renderGame();                   // ��� ��� ������
    if (!paused)                    
    {
        Update();                   // ��� ���ӿ�� ����
		input->InputEventReset(); // �Էµ� ����
    }

    input->clear(inputNS::KEYS_PRESSED); // �ԷµȰ� �ʱ�ȭ

}

// Scene ��ȯ
void Game::ChangeScene(Game* var)
{
	extern BOOL switchScene;
	extern Game* beforeScene;
	extern Game* nextScene;

	beforeScene = this;
	nextScene = var;

	switchScene = true;
}

void Game::deleteAll()
{
    releaseAll();    
	SAFE_DELETE(audio);
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
    initialized = false;
}