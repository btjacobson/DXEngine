#pragma once

#include <d3d11.h>

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool Load(void* buffer, UINT bufferSize);
	void Update(DeviceContext* deviceContext, void* buffer);
	bool Release();

private:
	friend class DeviceContext;

	ID3D11Buffer* m_Buffer;
};
