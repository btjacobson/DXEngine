#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : m_Buffer(0)
{

}

IndexBuffer::~IndexBuffer()
{

}

bool IndexBuffer::Load(void* listIndices, UINT sizeList)
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * sizeList;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listIndices;

	m_SizeList = sizeList;

	if (FAILED(GraphicsEngine::GetInstance()->m_D3dDevice->CreateBuffer(&bufferDesc, &initData, &m_Buffer)))
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::GetIndexSize()
{
	return m_SizeList;
}

bool IndexBuffer::Release()
{
	m_Buffer->Release();
	delete this;

	return true;
}