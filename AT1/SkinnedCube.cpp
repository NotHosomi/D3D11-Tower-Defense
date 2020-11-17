#include "SkinnedCube.h"
#include "Bindable_list.h"
#include "CubeBase.h"
#include "Surface.h"
#include "Texture.h"
#include "Sampler.h"



SkinnedCube::SkinnedCube(Renderer& renderer, Vector3 pos, Vector3 rot, Vector3 scale, std::string texture) :
	local_transform(DirectX::XMMatrixScaling(scale.x, scale.x, scale.x)*
		DirectX::XMMatrixRotationRollPitchYaw(rot.y, rot.x, rot.z)*
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z))
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

DirectX::XMMATRIX SkinnedCube::getXMTransform() const noexcept
{
	// replace with FromVector versions
	return local_transform *
		DirectX::XMMatrixScaling(x_scale, y_scale, z_scale) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(x, y, z);
}

void SkinnedCube::setPos(Vector3 new_pos)
{
	x = new_pos.x;
	y = new_pos.y;
	z = new_pos.z;
}

void SkinnedCube::setRos(Vector3 new_rot)
{
	roll = new_rot.x;
	pitch = new_rot.y;
	yaw = new_rot.z;
}

void SkinnedCube::setScale(Vector3 new_scale)
{
	x_scale = new_scale.x;
	y_scale = new_scale.y;
	z_scale = new_scale.z;
}
