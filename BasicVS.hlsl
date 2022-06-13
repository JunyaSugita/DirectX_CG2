#include "Basic.hlsli"

VSOutput main( float4 pos : POSITION, float2 uv : TEXCOORD )
{
	VSOutput output;
	//output.svpos = pos;
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}