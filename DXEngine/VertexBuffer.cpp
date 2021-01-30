#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer() : m_Layout(0), m_Buffer(0)
{

}

VertexBuffer::~VertexBuffer()
{

}

bool VertexBuffer::Load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader)
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}

	if (m_Layout)
	{
		m_Layout->Release();
	}

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeVertex * sizeList;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listVertices;

	m_SizeVertex = sizeVertex;
	m_SizeList = sizeList;

	if (FAILED(GraphicsEngine::GetInstance()->m_D3dDevice->CreateBuffer(&bufferDesc, &initData, &m_Buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	UINT sizeLayout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::GetInstance()->m_D3dDevice->CreateInputLayout(layout, sizeLayout,
		shaderByteCode, sizeByteShader, &m_Layout)))
	{
		return false;
	}

	return true;
}

UINT VertexBuffer::GetVertexSize()
{
	return m_SizeList;
}

bool VertexBuffer::Release()
{
	m_Layout->Release();
	m_Buffer->Release();
	delete this;

	return true;
}
