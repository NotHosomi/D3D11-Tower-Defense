cbuffer CBuf
{
	float4 face_colours[6];
};

float4 main( uint tri_id : SV_PrimitiveID ) : SV_Target
{
	return face_colours[(tri_id / 2) % 8];
}