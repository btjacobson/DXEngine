#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	void UpdateQuadPosition();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;

private:
	SwapChain* m_SwapChain;
	VertexBuffer* m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;
	ConstantBuffer* m_ConstantBuffer;

	float m_OldDelta;
	float m_NewDelta;
	float m_DeltaTime;
	float m_DeltaPosition;
	float m_DeltaScale;
};
