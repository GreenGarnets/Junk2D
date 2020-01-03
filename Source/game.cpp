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
    ShowCursor(true);           // 커서 표시
}

LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) // 윈도우 메세지 헨들러
{
    if(initialized)     // 초기화 됐을 경우에만 처리
    {
        switch( msg )
        {

			// 윈도우 핸들러 코드를 Input클라스로 전달

            case WM_DESTROY:
                PostQuitMessage(0);        // 종료
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // 키 누름
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // 키 뗌
                input->keyUp(wParam);
                return 0;
            case WM_MOUSEMOVE:                      // 마우스 움직임
                input->mouseIn(lParam);
                return 0;
            case WM_INPUT:                          // 마우스 데이터가 들어옴
                input->mouseRawIn(lParam);
                return 0;
            case WM_LBUTTONDOWN:                    // 마우스 왼쪽버튼 누름
                input->setMouseLButton(true);
                input->mouseIn(lParam);             // 마우스 위치
                return 0;
            case WM_LBUTTONUP:                      // 마우스 왼쪽버튼 뗌
                input->setMouseLButton(false);
				input->setMouseLButtonDown(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONDOWN:                    // 마우스 가운데 버튼 누름
                input->setMouseMButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_MBUTTONUP:                      // 마우스 가운데 버튼 뗌
                input->setMouseMButton(false);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONDOWN:                    // 마우스 오른쪽 버튼 누름
                input->setMouseRButton(true);
                input->mouseIn(lParam);             
                return 0;
            case WM_RBUTTONUP:                      // 마우스 오른쪽 버튼 뗌
                input->setMouseRButton(false);
                input->mouseIn(lParam);             
                return 0;
			case WM_SETCURSOR:
				graphics->device3d->ShowCursor(TRUE);
				return TRUE; // prevent Windows from setting cursor to window class cursor

				break;

        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // 윈도우가 처리하게 함
}

// 게임 초기화
void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // 윈도우 핸들 저장
   
	// 전체화면시 그래픽 객체가 두번 생성되면서 에러가 생기는듯함. 수정필요.
	// 그래픽 객체 역시 static으로 만들어 줘야 할듯함.
   
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);	// 게임 에러를 뱉는다

	audio->initialize();

    // Input객체 초기화
    input->initialize(hwnd, false);            

    // 타이머 사용
	QueryPerformanceFrequency(&timerFreq);
        
    QueryPerformanceCounter(&timeStart);        // 시작 시간 가져오기

	// 게임이 이니셜라이즈 됨
    initialized = true;
}

// 게임 렌더링
void Game::renderGame()
{
	graphics->beginScene();
    render();               // 파생클래스에서 render를 호출
    graphics->endScene();	// 렌더링을 멈춘다

    graphics->showBackbuffer(); // 백 버퍼 표시
}

void Game::run(HWND hwnd)
{
    if(graphics == NULL)            
        return;

	// 프레임 레이트 계산
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / 
                (float)timerFreq.QuadPart;

	// 절전 코드, Winnm.lib 필요
    if (frameTime < MIN_FRAME_TIME) 
    {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
        timeBeginPeriod(1);         
        Sleep(sleepTime);           // cpu를 쉬게한다.
        timeEndPeriod(1);           
        return;
    }

    if (frameTime > 0.0)
        fps = (fps*0.99f) + (0.01f/frameTime);  // 평균 FPS

    if (frameTime > MAX_FRAME_TIME) // 프레임 속도가 느릴경우 최대 frameTime으로 제한
        frameTime = MAX_FRAME_TIME; // 최대 frameTime으로 제한

    timeStart = timeEnd;

	renderGame();                   // 모든 요소 렌더링
    if (!paused)                    
    {
        Update();                   // 모든 게임요소 갱신
		input->InputEventReset(); // 입력들 리셋
    }

    input->clear(inputNS::KEYS_PRESSED); // 입력된것 초기화

}

// Scene 전환
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