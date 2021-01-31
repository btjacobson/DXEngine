#include "AppWindow.h"
#include <Windows.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	unsigned int m_Time;
};

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}

void AppWindow::OnCreate()
{
	//Window::OnCreate();

	GraphicsEngine::GetInstance()->Init();
	m_SwapChain = GraphicsEngine::GetInstance()->CreateSwapChain();

	RECT rc = GetClientWindowRect();
	m_SwapChain->Init(m_Hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,	0, 0, 0,	0, 1, 0,},
		{-0.5f, 0.5f, 0.0f,		-0.11f, 0.78f, 0.0f,	1, 1, 0,	0, 1, 1,},
		{0.5f, -0.5f, 0.0f,		0.75f, -0.73f, 0.0f,	0, 0, 1,	1, 0, 0,},
		{0.5f, 0.5f, 0.0f,		0.88f, 0.77f, 0.0f,		1, 1, 1,	0, 0, 1 },
	};

	m_VertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	UINT sizeList = ARRAYSIZE(list);

	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	GraphicsEngine::GetInstance()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	m_VertexShader = GraphicsEngine::GetInstance()->CreateVertexShader(shaderByteCode, shaderSize);
	m_VertexBuffer->Load(list, sizeof(vertex), sizeList, shaderByteCode, shaderSize);

	GraphicsEngine::GetInstance()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	m_PixelShader = GraphicsEngine::GetInstance()->CreatePixelShader(shaderByteCode, shaderSize);

	GraphicsEngine::GetInstance()->ReleaseCompiledShader();

	constant cc;
	cc.m_Time = 0;

	m_ConstantBuffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	m_ConstantBuffer->Load(&cc, sizeof(constant));
}

void AppWindow::OnUpdate()
{
	//Window::OnUpdate();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTarget(m_SwapChain, 0, 0, 0, 1.0);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cc;
	cc.m_Time = ::GetTickCount();
	m_ConstantBuffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_VertexShader, m_ConstantBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_PixelShader, m_ConstantBuffer);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(m_VertexShader);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetPixelShader(m_PixelShader);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(m_VertexBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(m_VertexBuffer->GetVertexSize(), 0);
	m_SwapChain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_VertexBuffer->Release();
	m_SwapChain->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	GraphicsEngine::GetInstance()->Release();
}
