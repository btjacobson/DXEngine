#include "VertexShader.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader()
{

}

VertexShader::~VertexShader()
{

}

void VertexShader::Release()
{
	if (m_VertexShader)
	{
		m_VertexShader->Release();
	}
	delete this;
}

bool VertexShader::Init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::GetInstance()->m_D3dDevice->CreateVertexShader(
		shaderByteCode, byteCodeSize, nullptr, &m_VertexShader)))
	{
		return false;
	}

	return true;
}
