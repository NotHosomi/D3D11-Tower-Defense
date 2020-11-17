#include "Cube.h"
#include "Bindable_list.h"
#include "CubeBase.h"

Cube::Cube(Renderer& renderer,
	std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	std::uniform_real_distribution<float>& bdist,
	DirectX::XMFLOAT3 material) :
	TestObject(renderer, rng, adist, ddist, odist, rdist)
{
	namespace dx = DirectX;

	if (!checkStatics())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			dx::XMFLOAT3 n;
		};
		auto model = CubeBase::MakeIndependent<Vertex>();
		model.SetNormalsIndependentFlat();

		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		auto pvs = std::make_unique<VertexShader>(renderer, L"PhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"PhongPS.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		//struct PixelShaderConstants
		//{
		//	struct
		//	{
		//		float r;
		//		float g;
		//		float b;
		//		float a;
		//	} face_colors[8];
		//};
		//const PixelShaderConstants cb2 =
		//{
		//	{
		//		{ 1.0f,1.0f,1.0f },
		//		{ 1.0f,0.0f,0.0f },
		//		{ 0.0f,1.0f,0.0f },
		//		{ 1.0f,1.0f,0.0f },
		//		{ 0.0f,0.0f,1.0f },
		//		{ 1.0f,0.0f,1.0f },
		//		{ 0.0f,1.0f,1.0f },
		//		{ 0.0f,0.0f,0.0f },
		//	}
		//};
		//addStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(renderer, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, ied, pvsbc));

		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		fetchStaticIndices();
	}

	addBind(std::make_unique<TransformBuffer>(renderer, *this));

	struct PSMaterialConstant
	{
		dx::XMFLOAT3 color;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[3];
	} colorConst;
	colorConst.color = material;
	addBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(renderer, colorConst, 1u));

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&transform,
		dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng))
	);
}

DirectX::XMMATRIX Cube::getXMTransform() const noexcept
{
	return DirectX::XMLoadFloat3x3(&transform) * TestObject::getXMTransform();
}