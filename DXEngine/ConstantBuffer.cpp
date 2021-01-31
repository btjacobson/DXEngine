#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{

}

ConstantBuffer::~ConstantBuffer()
{

}

bool ConstantBuffer::Load(void* buffer, UINT bufferSize)
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = bufferSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	if (FAILED(GraphicsEngine::GetInstance()->m_D3dDevice->CreateBuffer(&bufferDesc, &initData, &m_Buffer)))
	{
		return false;
	}

	return true;
}

void ConstantBuffer::Update(DeviceContext* deviceContext, void* buffer)
{
	deviceContext->m_DeviceContext->UpdateSubresource(m_Buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::Release()
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}
	delete this;

	return true;
}
