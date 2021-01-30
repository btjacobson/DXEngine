#include "Window.h"

Window* window = nullptr;

Window::Window()
{

}

Window::~Window()
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
		window->SetHWND(hwnd);
		window->OnCreate();
		break;

	case WM_DESTROY:
		window->OnDestroy();
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::Init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) 
	{
		return false;
	}

	if (!window)
	{
		window = this;
	}

	m_Hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);
	if (!m_Hwnd)
	{
		return false;
	}

	::ShowWindow(m_Hwnd, SW_SHOW);
	::UpdateWindow(m_Hwnd);

	m_IsRunning = true;
	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	window->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Sleep(1);

	return true;
}

bool Window::Release()
{
	if (::DestroyWindow(m_Hwnd))
	{
		return false;
	}
	return true;
}

bool Window::IsRunning()
{
	return m_IsRunning;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(m_Hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd)
{
	m_Hwnd = hwnd;
}

void Window::OnDestroy()
{
	m_IsRunning = false;
}
