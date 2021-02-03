#pragma once

#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	void ClearRenderTarget(SwapChain* swapChain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);
	void DrawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void DrawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);
	void DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void SetViewportSize(UINT width, UINT height);
	void SetVertexShader(VertexShader* vertexShader);
	void SetPixelShader(PixelShader* pixelShader);
	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* constantBuffer);
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* constantBuffer);
	bool Release();

private:
	friend class ConstantBuffer;

	ID3D11DeviceContext* m_DeviceContext;
};
