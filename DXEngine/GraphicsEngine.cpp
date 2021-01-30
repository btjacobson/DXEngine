#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}

bool GraphicsEngine::Init()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT res = 0;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes;)
	{
		res = D3D11CreateDevice(NULL, driverTypes[driverTypeIndex], NULL, NULL, featureLevels, 
			numFeatureLevels, D3D11_SDK_VERSION, &m_D3dDevice, &m_FeatureLevel, &m_ImmContext);

		if (SUCCEEDED(res))
		{
			break;
		}

		++driverTypeIndex;
	}

	if (FAILED(res))
	{
		return false;
	}

	m_ImmDeviceContext = new DeviceContext(m_ImmContext);


	m_D3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DxgiDevice);
	m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_DxgiAdapter);
	m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DxgiFactory);

	return true;
}

bool GraphicsEngine::Release()
{
	if (m_VertexShader)
	{
		m_VertexShader->Release();
	}

	if (m_PixelShader)
	{
		m_PixelShader->Release();
	}

	if (m_VertexShaderBlob)
	{
		m_VertexShaderBlob->Release();
	}

	if (m_PixelShaderBlob)
	{
		m_PixelShaderBlob->Release();
	}

	m_DxgiDevice->Release();
	m_DxgiAdapter->Release();
	m_DxgiFactory->Release();
	m_ImmDeviceContext->Release();
	m_D3dDevice->Release();
	
	return true;
}

bool GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"../shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_VertexShaderBlob, &errblob);
	D3DCompileFromFile(L"../shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_PixelShaderBlob, &errblob);
	
	m_D3dDevice->CreateVertexShader(m_VertexShaderBlob->GetBufferPointer(), m_VertexShaderBlob->GetBufferSize(), nullptr, &m_VertexShader);
	m_D3dDevice->CreatePixelShader(m_PixelShaderBlob->GetBufferPointer(), m_PixelShaderBlob->GetBufferSize(), nullptr, &m_PixelShader);

	return true;
}

bool GraphicsEngine::SetShaders()
{	
	m_ImmContext->VSSetShader(m_VertexShader, nullptr, 0);
	m_ImmContext->PSSetShader(m_PixelShader, nullptr, 0);

	return true;
}

void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_VertexShaderBlob->GetBufferPointer();
	*size = (UINT)this->m_VertexShaderBlob->GetBufferSize();
}

GraphicsEngine* GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;
	
	return &engine;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return m_ImmDeviceContext;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}
