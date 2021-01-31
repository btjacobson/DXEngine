#pragma once

#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	void Release();

private:
	friend class GraphicsEngine;
	friend class DeviceContext;

	bool Init(const void* shaderByteCode, size_t byteCodeSize);

	ID3D11VertexShader* m_VertexShader;
};
