struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant : register(b0)
{
	row_major float4x4 m_World;
	row_major float4x4 m_View;
	row_major float4x4 m_Projection;
	unsigned int m_Time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(lerp(input.color, input.color1, (sin(m_Time / 500.0f) + 1.0f) / 2.0f), 1.0f);
}