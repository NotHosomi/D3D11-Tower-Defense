#include "Cylinder.h"
#include "Prism.h"
#include "Bindable_list.h"

Cylinder::Cylinder(Renderer& renderer, std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist,
	std::uniform_int_distribution<int>& tdist)
	:
	TestObject(renderer, rng, adist, ddist, odist, rdist)
{
	if (!checkStatics())
	{
		auto pvs = std::make_unique<VertexShader>(renderer, L"PhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));
		addStaticBind(std::make_unique<PixelShader>(renderer, L"IndexedPhongPS.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, ied, pvsbc));

		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		struct PSMaterialConstant
		{
			DirectX::XMFLOAT3A colors[6] = {
				{1.0f,0.0f,0.0f},
				{0.0f,1.0f,0.0f},
				{0.0f,0.0f,1.0f},
				{1.0f,1.0f,0.0f},
				{1.0f,0.0f,1.0f},
				{0.0f,1.0f,1.0f},
			};
			float specularIntensity = 0.6f;
			float specularPower = 30.0f;
		} matConst;
		addStaticBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(renderer, matConst, 1u));
	}

	// Generate geometry per-instance, non-static
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 n;
	};
	const auto model = Prism::MakeTesselatedIndependentCapNormals<Vertex>(tdist(rng));
	addBind(std::make_unique<VertexBuffer>(renderer, model.vertices));
	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

	addBind(std::make_unique<TransformBuffer>(renderer, *this));
}
