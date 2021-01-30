#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{

}

SwapChain::~SwapChain()
{

}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::GetInstance()->m_D3dDevice;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = true;

	HRESULT hr = GraphicsEngine::GetInstance()->m_DxgiFactory->CreateSwapChain(device, &desc, &m_SwapChain);
	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* buffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_RenderTargetView);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::Release()
{
	m_SwapChain->Release();
	delete this;

	return true;
}

bool SwapChain::Present(bool vsync)
{
	m_SwapChain->Present(vsync, NULL);

	return true;
}
