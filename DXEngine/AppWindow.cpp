#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
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
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
	};

	m_VertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	UINT sizeList = ARRAYSIZE(list);

	GraphicsEngine::GetInstance()->CreateShaders();

	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	GraphicsEngine::GetInstance()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	m_VertexShader = GraphicsEngine::GetInstance()->CreateVertexShader(shaderByteCode, shaderSize);

	m_VertexBuffer->Load(list, sizeof(vertex), sizeList, shaderByteCode, shaderSize);

	GraphicsEngine::GetInstance()->ReleaseCompiledShader();
}

void AppWindow::OnUpdate()
{
	//Window::OnUpdate();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTarget(m_SwapChain, 0, 0, 0, 1.0);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::GetInstance()->SetShaders();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(m_VertexShader);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(m_VertexBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(m_VertexBuffer->GetVertexSize(), 0);
	m_SwapChain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_VertexBuffer->Release();
	m_SwapChain->Release();
	GraphicsEngine::GetInstance()->Release();
}
