#pragma once

#include <Windows.h>
#include <windowsx.h>

class Window
{
public:
	Window(int width, int height, LPCWSTR title);
	~Window();

	void Run();

protected:

private:
	void InitWindow();

	int ProcessMessages();
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int _width;
	int _height;
	bool _isRunning;
	LPCWSTR _title;
};