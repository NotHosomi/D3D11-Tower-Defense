#include "Pyramid.h"
#include "Bindable_list.h"
#include "Cone.h"
#include <array>


Pyramid::Pyramid(Renderer& renderer, std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_int_distribution<int>& tdist)
	:
	TestObject(renderer, rng, adist, ddist, odist, rdist)
{
	namespace dx = DirectX;

	if (!checkStatics())
	{
		auto pvs = std::make_unique<VertexShader>(renderer, L"BlendedPhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"BlendedPhongPS.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, ied, pvsbc));

		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		struct PSMaterialConstant
		{
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
			float padding[2];
		} colorConst;
		addStaticBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(renderer, colorConst, 1u));
	}

	// Generate geometry per-instance, non-static
	struct Vertex
	{
		dx::XMFLOAT3 pos;
		dx::XMFLOAT3 n;
		std::array<char, 4> color;
		char padding;
	};
	const auto tesselation = tdist(rng);
	auto model = Cone::MakeTesselatedIndependentFaces<Vertex>(tesselation);
	// set vertex colors for mesh (tip red blending to blue base)
	for (auto& v : model.vertices)
	{
		v.color = { (char)255,(char)255,(char)10 };
	}
	for (int i = 0; i < tesselation; i++)
	{
		model.vertices[i * 3].color = { (char)255,(char)10,(char)10 };
	}
	model.SetNormalsIndependentFlat();

	addBind(std::make_unique<VertexBuffer>(renderer, model.vertices));
	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));


	addBind(std::make_unique<TransformBuffer>(renderer, *this));
}
