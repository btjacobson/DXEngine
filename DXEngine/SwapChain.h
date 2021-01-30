#pragma once

#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Init(HWND hwnd, UINT width, UINT height);
	bool Release();
	bool Present(bool vsync);

private:
	friend class DeviceContext;

	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
};
