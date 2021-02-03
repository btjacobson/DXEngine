struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

struct VS_OUTPUT
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

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.position = lerp(input.position, input.position1, (sin(m_Time / 1000.0f) + 1.0f) / 2.0f);
	
	// World Space
	output.position = mul(input.position, m_World);
	
	// View Space
	output.position = mul(output.position, m_View);

	// Screen Space
	output.position = mul(output.position, m_Projection);
	
	output.color = input.color;
	output.color1 = input.color1;

	return output;
}