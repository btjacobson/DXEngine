#pragma once

#include <Windows.h>
#include <windowsx.h>

class DX_Renderer;

class Window
{
public:
	Window(int width, int height, int nCmdShow, LPCWSTR title, HINSTANCE hInstance);
	~Window();

	int Run();
	int GetWidth();
	int GetHeight();
	HWND& GetHandle();

private:
	void InitWindow();
	void ProcessMessages();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DX_Renderer* _dxRenderer;

	int _width;
	int _height;
	int _cmdShow;
	bool _isRunning;

	LPCWSTR _title;
	HINSTANCE _hInstance;
	MSG _message;
	HWND _wndHandle;
	WNDCLASSEX _wndClass;
	RECT _wndRect;
};