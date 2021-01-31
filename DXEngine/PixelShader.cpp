#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
{

}

PixelShader::~PixelShader()
{

}

void PixelShader::Release()
{
	if (m_PixelShader)
	{
		m_PixelShader->Release();
	}
	delete this;
}

bool PixelShader::Init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::GetInstance()->m_D3dDevice->CreatePixelShader(
		shaderByteCode, byteCodeSize, nullptr, &m_PixelShader)))
	{
		return false;
	}

	return true;
}
