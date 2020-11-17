#include "Ball.h"
#include "Bindable_list.h"
#include "Sphere.h"


Ball::Ball(Renderer& renderer, int lati, int longi)
{
	namespace dx = DirectX;

	if (!checkStatics())
	{
		auto pvs = std::make_unique<VertexShader>(renderer, L"ColourIndexVS.cso");
		auto pvsbc = pvs->GetBytecode();
		addStaticBind(std::move(pvs));

		addStaticBind(std::make_unique<PixelShader>(renderer, L"ColourIndexPS.cso"));

		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		addStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(renderer, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		addStaticBind(std::make_unique<InputLayout>(renderer, ied, pvsbc));

		addStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	struct Vertex
	{
		dx::XMFLOAT3 pos;
	};
	auto model = Sphere::MakeTesselated<Vertex>(lati, longi);
	// deform vertices of model by linear transformation
	model.Transform(dx::XMMatrixScaling(1.0f, 1.0f, 1.0f));

	addBind(std::make_unique<VertexBuffer>(renderer, model.vertices));

	addIndexBuffer(std::make_unique<IndexBuffer>(renderer, model.indices));

	addBind(std::make_unique<TransformBuffer>(renderer, *this));
}