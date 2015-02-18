cbuffer PerFrameBuffer : register(b0)
{
	float4x4 viewProjection;
};

cbuffer PerMeshBuffer : register(b1)
{
	float4x4 world;
	float4x4 worldView;
	float4x4 worldViewInverseTranspose;
}

struct VertexIn
{
	float3 position : POSITION;
	float3 colour : COLOR;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct PixelIn
{
	float4 viewPosition : SV_POSITION;
	float3 worldPosition : POSITION;
	float3 viewNormal : NORMAL;
	float3 colour : COLOR;
	float2 texcoord : TEXCOORD0;
};

PixelIn main(VertexIn input)
{
	PixelIn output;
	output.worldPosition = input.position;
	output.viewPosition = mul(world, float4(input.position, 1.0));
	output.viewPosition = mul(viewProjection, output.viewPosition);
	output.viewNormal = normalize(mul(input.normal, worldViewInverseTranspose));
	output.colour = input.colour;
	output.texcoord = input.texcoord;
	return output;
}