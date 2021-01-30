#pragma once

#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool Load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader);
	UINT GetVertexSize();
	bool Release();

private:
	friend class DeviceContext;

	UINT m_SizeVertex;
	UINT m_SizeList;
	ID3D11Buffer* m_Buffer;
	ID3D11InputLayout* m_Layout;
};
