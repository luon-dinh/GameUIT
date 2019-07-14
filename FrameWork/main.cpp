#include"Global.h"
#include"Game.h"
LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY||WM_QUIT:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

HWND Create(HINSTANCE hInstance, int ncmdShow, int width, int height)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = (WNDPROC)WinProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	auto hwnd = CreateWindow(WINDOW_CLASS_NAME, GAME_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, ncmdShow);
	UpdateWindow(hwnd);

	return hwnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpcmdLine, int ncmdShow)
{
	HWND hwnd = Create(hInstance, ncmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	Game *game=new Game(hwnd, hInstance);
	game->Run();
	delete game;
	return 0;
}