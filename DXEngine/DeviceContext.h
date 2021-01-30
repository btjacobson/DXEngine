#pragma once

#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	void ClearRenderTarget(SwapChain* swapChain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void DrawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void SetViewportSize(UINT width, UINT height);
	bool Release();

private:
	ID3D11DeviceContext* m_DeviceContext;
};
