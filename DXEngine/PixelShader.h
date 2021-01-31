#pragma once

#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	void Release();

private:
	friend class GraphicsEngine;
	friend class DeviceContext;

	bool Init(const void* shaderByteCode, size_t byteCodeSize);

	ID3D11PixelShader* m_PixelShader;
};
