#pragma once

#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class DeviceContext;
class VertexShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Init();
	bool Release();
	bool CompileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void ReleaseCompiledShader();
	bool CreateShaders();
	bool SetShaders();

	static GraphicsEngine* GetInstance();

	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();
	VertexShader* CreateVertexShader(const void* shaderByteCode, size_t byteCodeSize);

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;

	DeviceContext* m_ImmDeviceContext;
	ID3D11Device* m_D3dDevice;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	IDXGIDevice* m_DxgiDevice;
	IDXGIAdapter* m_DxgiAdapter;
	IDXGIFactory* m_DxgiFactory;
	ID3D11DeviceContext* m_ImmContext;

	ID3DBlob* m_Blob = nullptr;
	ID3DBlob* m_VertexShaderBlob = nullptr;
	ID3DBlob* m_PixelShaderBlob = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
};
