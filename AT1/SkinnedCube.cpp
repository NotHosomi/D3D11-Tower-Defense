#include "SkinnedCube.h"
#include "Bindable_list.h"
#include "CubeBase.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"



SkinnedCube::SkinnedCube(Renderer& renderer, std::string texture)
{
	if (!checkStatics())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 n;
			DirectX::XMFLOAT2 tc;
		};
		auto model = CubeBase::MakeIndependentTextured<Vertex>();
		model.SetNormalsIndependentFlat();

		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		addStaticBind(std::make_unique<Texture>(renderer, Surface::FromFile("Images\\" + texture + ".png")));

		addStaticBind(std::make_unique<Sampler>(renderer));

		auto pvs = std::make_unique<VertexShader>(renderer, L"TexturedPhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"TexturedPhongPS.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
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
	else
	{
		fetchStaticIndices();
	}

	addBind(std::make_unique<TransformBuffer>(renderer, *this));
}
