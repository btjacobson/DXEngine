#include "AppWindow.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_World;
	Matrix4x4 m_View;
	Matrix4x4 m_Projection;
	unsigned int m_Time;
};

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}

void AppWindow::UpdateQuadPosition()
{
	constant cc;
	cc.m_Time = ::GetTickCount();

	m_DeltaPosition += m_DeltaTime / 4.0f;
	
	if (m_DeltaPosition > 1.0f)
	{
		m_DeltaPosition = 0;
	}
	
	Matrix4x4 temp;

	m_DeltaScale += m_DeltaTime / 0.15f;

	cc.m_World.SetScale(Vector3D::Lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_DeltaScale) + 1.0f) / 2.0f));
	temp.SetTranslation(Vector3D::Lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_DeltaPosition));

	cc.m_World *= temp;

	cc.m_View.SetIdentity();
	cc.m_Projection.SetOrthoLH
	(
		(GetClientWindowRect().right - GetClientWindowRect().left) / 400.0f,
		(GetClientWindowRect().bottom - GetClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);

	m_ConstantBuffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cc);
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
		{ Vector3D(-0.5f, -0.5f, 0.0f),	Vector3D(-0.32f, -0.11f, 0.0f),	Vector3D(0, 0, 0),	Vector3D(0, 1, 0) },
		{ Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D(-0.11f, 0.78f, 0.0f),	Vector3D(1, 1, 0),	Vector3D(0, 1, 1) },
		{ Vector3D(0.5f, -0.5f, 0.0f),	Vector3D(0.75f, -0.73f, 0.0f),	Vector3D(0, 0, 1),	Vector3D(1, 0, 0) },
		{ Vector3D(0.5f, 0.5f, 0.0f),	Vector3D(0.88f, 0.77f, 0.0f),	Vector3D(1, 1, 1),	Vector3D(0, 0, 1) }
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

	UpdateQuadPosition();

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_VertexShader, m_ConstantBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_PixelShader, m_ConstantBuffer);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(m_VertexShader);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetPixelShader(m_PixelShader);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(m_VertexBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(m_VertexBuffer->GetVertexSize(), 0);
	m_SwapChain->Present(true);

	m_OldDelta = m_NewDelta;
	m_NewDelta = ::GetTickCount();
	m_DeltaTime = (m_OldDelta) ? ((m_NewDelta - m_OldDelta) / 1000.0f) : 0;
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
