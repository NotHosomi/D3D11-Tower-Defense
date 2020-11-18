#include "Tile.h"
#include "Bindable_list.h"
#include "Plane.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"


Tile::Tile(Renderer& renderer, std::string texture)
{
	namespace dx = DirectX;

	if (!checkStatics())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 n;
			DirectX::XMFLOAT2 tc;
		};
		auto model = Plane::Make<Vertex>();
		model.vertices[0].tc = { 0.0f,0.0f };
		model.vertices[1].tc = { 1.0f,0.0f };
		model.vertices[2].tc = { 0.0f,1.0f };
		model.vertices[3].tc = { 1.0f,1.0f };


		addStaticBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

		addStaticBind(std::make_unique<Sampler>(renderer));

		auto pvs = std::make_unique<VertexShader>(renderer, L"TextureVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"TexturePS.cso"));

		addStaticIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, ied, pvsbc));

		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		fetchStaticIndices();
	}

	addBind(std::make_unique<Texture>(renderer, Surface::FromFile("Images\\" + texture + ".png")));
	addBind(std::make_unique<TransformBuffer>(renderer, *this));
}