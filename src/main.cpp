#include "Core/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window = Window(800, 600, nCmdShow, L"Test", hInstance);
	return window.Run();
}
