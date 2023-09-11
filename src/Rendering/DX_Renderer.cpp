#include "DX_Renderer.h"

#include "../Core/Window.h"

DX_Renderer::DX_Renderer(Window* window)
{
	_window = window;

	Init();
}

DX_Renderer::~DX_Renderer()
{
	_window = nullptr;

	_swapchain->SetFullscreenState(FALSE, NULL);

	_layout->Release();
	_vertexShader->Release();
	_pixelShader->Release();
	_vertexBuffer->Release();
	_swapchain->Release();
	_backBuffer->Release();
	_device->Release();
	_deviceContext->Release();
}

void DX_Renderer::RenderFrame()
{
	_deviceContext->ClearRenderTargetView(_backBuffer, D3DXCOLOR(0.22f, 0.22f, 0.22f, 1.0f));

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	_deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_deviceContext->Draw(3, 0);

	_swapchain->Present(0, 0);
}

void DX_Renderer::Init()
{
	InitDX();
	InitPipeline();
	InitGraphics();
}

void DX_Renderer::InitDX()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = _window->GetWidth();
	swapChainDesc.BufferDesc.Height = _window->GetWidth();
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = _window->GetHandle();
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapchain,
		&_device,
		NULL,
		&_deviceContext);

	ID3D11Texture2D* tBackBuffer;
	_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tBackBuffer);

	_device->CreateRenderTargetView(tBackBuffer, NULL, &_backBuffer);
	tBackBuffer->Release();

	_deviceContext->OMSetRenderTargets(1, &_backBuffer, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = _window->GetWidth();
	viewport.Height = _window->GetHeight();

	_deviceContext->RSSetViewports(1, &viewport);
}

void DX_Renderer::InitPipeline()
{
	ID3D10Blob* vs;
	ID3D10Blob* ps;

	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vs, 0, 0);
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &ps, 0, 0);

	_device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &_vertexShader);
	_device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &_pixelShader);

	_deviceContext->VSSetShader(_vertexShader, 0, 0);
	_deviceContext->PSSetShader(_pixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	_device->CreateInputLayout(ied, 2, vs->GetBufferPointer(), vs->GetBufferSize(), &_layout);
	_deviceContext->IASetInputLayout(_layout);
}

void DX_Renderer::InitGraphics()
{
	Vertex vertices[] =
	{
		{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{-0.45, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	D3D11_BUFFER_DESC bDesc;
	ZeroMemory(&bDesc, sizeof(bDesc));

	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.ByteWidth = sizeof(Vertex) * 3;
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	_device->CreateBuffer(&bDesc, NULL, &_vertexBuffer);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	_deviceContext->Map(_vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
	memcpy(mappedSubresource.pData, vertices, sizeof(vertices));
	_deviceContext->Unmap(_vertexBuffer, NULL);
}
