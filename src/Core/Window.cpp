#include "Window.h"

Window::Window(int width, int height, LPCWSTR title)
{
	_width = width;
	_height = height;
	_title = title;

	InitWindow();
}

Window::~Window()
{

}

void Window::Run()
{
	ProcessMessages();
}

void Window::InitWindow()
{
	HWND hWnd;
	WNDCLASSEX wc;
	RECT windowsRect = { 0, 0, 500, 400 };
	AdjustWindowRect(&windowsRect, WS_OVERLAPPEDWINDOW, FALSE);

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass1", _title, WS_OVERLAPPEDWINDOW, 300, 300,
		_width, _height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	_isRunning = true;
}

int Window::ProcessMessages()
{
	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{

		}

		//RenderFrame();
	}

	return msg.wParam;
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}