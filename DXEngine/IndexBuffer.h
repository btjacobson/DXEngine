#pragma once

#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	bool Load(void* listIndices, UINT sizeList);
	UINT GetIndexSize();
	bool Release();

private:
	friend class DeviceContext;

	UINT m_SizeList;
	ID3D11Buffer* m_Buffer;
};
