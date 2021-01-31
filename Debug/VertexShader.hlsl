struct VS_INPUT
{
	float4 position: POSITION;
	float3 position1: POSITION1;
	float3 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant : register(b0)
{
	unsigned int m_Time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = lerp(input.position, input.position1, (sin(m_Time / 1000.0f) + 1.0f) / 2.0f);
	output.color = input.color;

	return output;
}