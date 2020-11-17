Texture2D tex;

SamplerState ss;

float4 main(float2 tc : TexCoord) : SV_Target
{
	return tex.Sample(ss,tc);
}