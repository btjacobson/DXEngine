#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>

#include <iostream>

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

bool GraphicsEngine::CompileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &m_Blob, &errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << (char*)errorBlob->GetBufferPointer();
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob->GetBufferPointer();
	*byteCodeSize = m_Blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &m_Blob, &errorBlob)))
	{
		if (errorBlob)
		{
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob->GetBufferPointer();
	*byteCodeSize = m_Blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (m_Blob)
	{
		m_Blob->Release();
	}
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

IndexBuffer* GraphicsEngine::CreateIndexBuffer()
{
	return new IndexBuffer();
}

 ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shaderByteCode, size_t byteCodeSize)
{
	VertexShader* vertexShader = new VertexShader();
	
	if (!vertexShader->Init(shaderByteCode, byteCodeSize))
	{
		vertexShader->Release();
		return nullptr;
	}

	return vertexShader;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shaderByteCode, size_t byteCodeSize)
{
	PixelShader* pixelShader = new PixelShader();

	if (!pixelShader->Init(shaderByteCode, byteCodeSize))
	{
		pixelShader->Release();
		return nullptr;
	}

	return pixelShader;
}
