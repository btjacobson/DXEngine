#include <Windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	D3DXCOLOR color;
};

// global declarations
IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
ID3D11Device* dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
ID3D11RenderTargetView* backBuffer;
ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;
ID3D11Buffer* vertexBuffer;
ID3D11InputLayout* layout;

// function prototypes
void InitD3D(HWND hWnd);     // sets up and initializes Direct3D
void InitPipeline();
void InitGraphics();
void RenderFrame();
void CleanD3D();         // closes Direct3D and releases memorys

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	hWnd = CreateWindowEx(NULL, L"WindowClass1", L"Engine", WS_OVERLAPPEDWINDOW, 300, 300,
		SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	InitD3D(hWnd);

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

		RenderFrame();
	}

	return msg.wParam;
}

void InitD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
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
		&swapchain,
		&dev,
		NULL,
		&devcon);

	ID3D11Texture2D* tBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tBackBuffer);

	dev->CreateRenderTargetView(tBackBuffer, NULL, &backBuffer);
	tBackBuffer->Release();

	devcon->OMSetRenderTargets(1, &backBuffer, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	devcon->RSSetViewports(1, &viewport);

	InitPipeline();
	InitGraphics();
}

void InitPipeline()
{
	ID3D10Blob* vs;
	ID3D10Blob* ps;

	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vs, 0, 0);
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &ps, 0, 0);

	dev->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), NULL, &vertexShader);
	dev->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), NULL, &pixelShader);

	devcon->VSSetShader(vertexShader, 0, 0);
	devcon->PSSetShader(pixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	dev->CreateInputLayout(ied, 2, vs->GetBufferPointer(), vs->GetBufferSize(), &layout);
	devcon->IASetInputLayout(layout);
}

void InitGraphics()
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

	dev->CreateBuffer(&bDesc, NULL, &vertexBuffer);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	devcon->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
	memcpy(mappedSubresource.pData, vertices, sizeof(vertices));
	devcon->Unmap(vertexBuffer, NULL);
}

void RenderFrame()
{
	devcon->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.22f, 0.22f, 0.22f, 1.0f));

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		devcon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		devcon->Draw(3, 0);

	swapchain->Present(0, 0);
}

void CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);

	layout->Release();
	vertexShader->Release();
	pixelShader->Release();
	vertexBuffer->Release();
	swapchain->Release();
	backBuffer->Release();
	dev->Release();
	devcon->Release();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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