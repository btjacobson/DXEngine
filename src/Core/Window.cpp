#include "Window.h"

#include "../Rendering/DX_Renderer.h"

Window::Window(int width, int height, int nCmdShow, LPCWSTR title, HINSTANCE hInstance)
{
	_width = width;
	_height = height;
	_cmdShow = nCmdShow;
	_title = title;
	_hInstance = hInstance;

	_dxRenderer = new DX_Renderer(this);

	_message = { 0 };
	_wndRect = { 0, 0, _width, _height };

	InitWindow();
}

Window::~Window()
{
	delete _dxRenderer;
	_dxRenderer = nullptr;
}

int Window::Run()
{
	ProcessMessages();

	return _message.wParam;
}

int Window::GetWidth()
{
	return _width;
}

int Window::GetHeight()
{
	return _height;
}

HWND& Window::GetHandle()
{
	return _wndHandle;
}

void Window::InitWindow()
{
	AdjustWindowRect(&_wndRect, WS_OVERLAPPEDWINDOW, FALSE);
	ZeroMemory(&_wndClass, sizeof(WNDCLASSEX));

	_wndClass.cbSize = sizeof(WNDCLASSEX);
	_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	_wndClass.lpfnWndProc = WindowProc;
	_wndClass.hInstance = _hInstance;
	_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	_wndClass.lpszClassName = L"WindowClass1";

	RegisterClassEx(&_wndClass);

	_wndHandle = CreateWindowEx(NULL, L"WindowClass1", _title, WS_OVERLAPPEDWINDOW, 300, 300,
		_width, _height, NULL, NULL, _hInstance, NULL);

	ShowWindow(_wndHandle, _cmdShow);

	_isRunning = true;
}

void Window::ProcessMessages()
{
	while (TRUE)
	{
		if (PeekMessage(&_message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_message);
			DispatchMessage(&_message);

			if (_message.message == WM_QUIT)
			{
				break;
			}
		}

		_dxRenderer->RenderFrame();
	}
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