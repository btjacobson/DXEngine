#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	D3DXCOLOR color;
};

class Window;

class DX_Renderer
{
public:
	DX_Renderer(Window* window);
	~DX_Renderer();

	void RenderFrame();

private:
	void Init();
	void InitDX();
	void InitPipeline();
	void InitGraphics();

	Window* _window;

	IDXGISwapChain* _swapchain;
	ID3D11Device* _device;
	ID3D11DeviceContext* _deviceContext;
	ID3D11RenderTargetView* _backBuffer;
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	ID3D11Buffer* _vertexBuffer;
	ID3D11InputLayout* _layout;
};