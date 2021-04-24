cbuffer LightCBuf
{
	float3 lightPos;
	float3 ambient;
	float3 diffuseColor;
	float diffuseIntensity;
	float attConst;
	float attLin;
	float attQuad;
};

cbuffer ObjectCBuf
{
	float3 materialColor;
	float specularIntensity;
	float specularPower;
};

float4 main(float3 worldPos : Position, float3 n : Normal) : SV_Target
{
	// fragment to light vector data
	const float3 incidence = lightPos - worldPos;
	const float incidence_norm = length(incidence);
	const float3 incidence_normalized = incidence / incidence_norm;
	// attenuation
	const float att = 1.0f / (attConst + attLin * incidence_norm + attQuad * (incidence_norm * incidence_norm));
	// diffuse intensity
	const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f,dot(incidence_normalized,n));
	// reflected light vector
	const float3 w = n * dot(incidence,n);
	const float3 r = w * 2.0f - incidence;
	// calculate specular intensity based on angle between viewing vector and reflection vector, narrow with power function
	const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f,dot(normalize(-r),normalize(worldPos))),specularPower);
	// final color
	return float4(saturate((diffuse + ambient + specular) * materialColor), 1.0f);
}