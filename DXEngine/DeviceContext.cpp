#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
	m_DeviceContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
{

}

void DeviceContext::ClearRenderTarget(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r, g, b, a };
	m_DeviceContext->ClearRenderTargetView(swapChain->m_RenderTargetView, clearColor);
	m_DeviceContext->OMSetRenderTargets(1, &swapChain->m_RenderTargetView, NULL);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_SizeVertex;
	UINT offset = 0;

	m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_Buffer, &stride, &offset);
	m_DeviceContext->IASetInputLayout(vertexBuffer->m_Layout);
}

void DeviceContext::DrawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_DeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_DeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{ 
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_DeviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::SetVertexShader(VertexShader* vertexShader)
{
	m_DeviceContext->VSSetShader(vertexShader->m_VertexShader, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixelShader)
{
	m_DeviceContext->PSSetShader(pixelShader->m_PixelShader, nullptr, 0);
}

bool DeviceContext::Release()
{
	m_DeviceContext->Release();
	delete this;	
	return true;
}
