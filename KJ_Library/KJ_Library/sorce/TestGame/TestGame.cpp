#include "../KJ_Lib/KJ_library.h"


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma warning(disable:4482)
#pragma warning(disable:4005)

using namespace Klibrary;
using namespace std;


//--------------------------------------------------------
//			WinMain
//--------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(158);

	App::m_pGameFramework = new GameFramework();
	HRESULT result = -1;

	//ウィンドウ作成
	result = InitializeWindow(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, "KJ_Library");

	if (SUCCEEDED(result)){

		//初期化
		result = App::m_pGameFramework->GameStartUp();
		App::m_pGameFramework->ChangeScene(SCENE_STATE::TEST1);

		if (SUCCEEDED(result)){
			//アプリループ
			App::m_pGameFramework->GameBegin();
		}
	}

	if (App::m_pGameFramework){
		App::m_pGameFramework->Release();
		delete App::m_pGameFramework;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return MsgProc(hWnd, uMsg, wParam, lParam);
}

//--------------------------------------------------------
//			ウィンドウ初期化
//--------------------------------------------------------
HRESULT InitializeWindow(HINSTANCE hInstance, INT windowWidth, INT windowHeight, LPCSTR windowName){

	//ウィンドウの定義(アイコンやら、名前やらなんやら)

	//ウィンドウサイズ設定
	RECT windowSize = { 0, 0, windowWidth, windowHeight };

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = windowName;
	wc.lpszMenuName = NULL;
	RegisterClassEx(&wc);

	//ウィンドウクライアント領域指定
	AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウ作成
	WindowSystem::hWnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW, NULL, NULL, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, 0, 0, hInstance, NULL);

	if (!WindowSystem::hWnd){
		MessageBox(0, "ウィンドウ作成失敗。", NULL, MB_OK);
		return E_FAIL;
	}

	//ウィンドウ表示
	ShowWindow(WindowSystem::hWnd, SW_SHOW);
	UpdateWindow(WindowSystem::hWnd);   //随時アップデートすればウィンドウスタイルもコロコロ変えられる

	return S_OK;
}


//--------------------------------------------------------
//			ウィンドウプロシージャる
//--------------------------------------------------------
LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Klibrary::WindowsMsg::hWnd = hWnd;
	Klibrary::WindowsMsg::lastMassage = Klibrary::WindowsMsg::message;
	Klibrary::WindowsMsg::message = message;
	Klibrary::WindowsMsg::wParam = wParam;
	Klibrary::WindowsMsg::lParam = lParam;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//case WM_KEYDOWN:
	//case WM_KEYUP:
	case WM_CHAR:
		if ((char)wParam == VK_ESCAPE){
			PostQuitMessage(0);
			break;
		}

		break;

	//case WM_MOUSEMOVE:
	//case WM_LBUTTONDOWN:
	//case WM_RBUTTONDOWN:

	//	break;


	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}