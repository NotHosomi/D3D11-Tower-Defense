#include "Renderer.h"
#include <sstream> // For std::size(), could use <array> instead
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swap_desc = {};
	swap_desc.BufferDesc.Width = 0; // use window size
	swap_desc.BufferDesc.Height = 0;
	swap_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_desc.BufferDesc.RefreshRate.Numerator = 0; // use existing refresh rate
	swap_desc.BufferDesc.RefreshRate.Denominator = 0;
	swap_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // no scaling
	swap_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // not interlaced
	swap_desc.SampleDesc.Count = 1; // no AA
	swap_desc.SampleDesc.Quality = 0;
	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Buffer is used for the RT
	swap_desc.BufferCount = 1; // 1 back buffer
	swap_desc.OutputWindow = hWnd;
	swap_desc.Windowed = TRUE;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_desc.Flags = 0;

	// init members
	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &swap_desc,
		&swapchain, &device, nullptr, &context
	);
	// fetch back
	// todo: add debug diagnostics
	Microsoft::WRL::ComPtr<ID3D11Resource> back;
	swapchain->GetBuffer(0, __uuidof(ID3D11Resource), &back);
	device->CreateRenderTargetView(back.Get(), nullptr, &render_target);

	/// Depth Buffer
	// Depth state
	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_state;
	device->CreateDepthStencilState(&dsd, &depth_state);
	context->OMSetDepthStencilState(depth_state.Get(), 1);
	// Depth texture
	D3D11_TEXTURE2D_DESC dtd = {};
	dtd.Width = 800;
	dtd.Height = 600;
	dtd.MipLevels = 1;
	dtd.ArraySize = 1;
	dtd.Format = DXGI_FORMAT_D32_FLOAT;
	dtd.SampleDesc.Count = 1;
	dtd.SampleDesc.Quality = 0;
	dtd.Usage = D3D11_USAGE_DEFAULT;
	dtd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depth;
	device->CreateTexture2D(&dtd, nullptr, &depth);
	// Depth view
	D3D11_DEPTH_STENCIL_VIEW_DESC dvd = {};
	dvd.Format = DXGI_FORMAT_D32_FLOAT;
	dvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dvd.Texture2D.MipSlice = 0;
	device->CreateDepthStencilView(depth.Get(), &dvd, &depth_view);
	context->OMSetRenderTargets(1, render_target.GetAddressOf(), depth_view.Get());


	// Viewport
	D3D11_VIEWPORT vp;
	vp.Height = 600;
	vp.Width = 800;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);
}

void Renderer::present()
{
	swapchain->Present(1, 0);
}

void Renderer::wipe(float r, float g, float b) noexcept
{
	const float colour[] = { r, g, b, 1 };
	context->ClearRenderTargetView(render_target.Get(), colour);
	context->ClearDepthStencilView(depth_view.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Renderer::drawTri(float angle, float x, float y)
{
	namespace wrl = Microsoft::WRL;
	namespace DX = DirectX;


	// Vertex Buffer setup
	struct Vertex
	{
		float x;
		float y;
		float z;
	};
	const Vertex vertices[] =
	{
		{ -1.0f,-1.0f,-1.0f	 },
		{ 1.0f,-1.0f,-1.0f	 },
		{ -1.0f,1.0f,-1.0f	 },
		{ 1.0f,1.0f,-1.0f	  },
		{ -1.0f,-1.0f,1.0f	 },
		{ 1.0f,-1.0f,1.0f	  },
		{ -1.0f,1.0f,1.0f	 },
		{ 1.0f,1.0f,1.0f	 },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;

	// Bind Buffer
	wrl::ComPtr<ID3D11Buffer> vertex_buffer;
	device->CreateBuffer(&bd, &sd, &vertex_buffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	context->IASetVertexBuffers(0, 1, vertex_buffer.GetAddressOf(), &stride, &offset);


	// Index Buffer setup
	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.ByteWidth = sizeof(vertices);
	ibd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;

	// Bind Buffer
	wrl::ComPtr<ID3D11Buffer> index_buffer;
	device->CreateBuffer(&ibd, &isd, &index_buffer);
	context->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, 0);


	// Transformation setup
	struct VrtConstantBuffer
	{
		DX::XMMATRIX transform;
	};
	const VrtConstantBuffer vcb =
	{
		{
			DX::XMMatrixTranspose(
				DX::XMMatrixRotationX(angle)*
				DX::XMMatrixRotationZ(angle)*
				DX::XMMatrixTranslation(x, y, 4) *
				DX::XMMatrixPerspectiveLH(1, 3.0f/4.0f, 0.5f, 10) )
		}
	};
	D3D11_BUFFER_DESC vcbd = {};
	vcbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vcbd.Usage = D3D11_USAGE_DYNAMIC;
	vcbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vcbd.MiscFlags = 0;
	vcbd.ByteWidth = sizeof(vcb);
	vcbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vcsd = {};
	vcsd.pSysMem = &vcb;

	// Bind buffer
	wrl::ComPtr<ID3D11Buffer> vertex_constant_buffer;
	device->CreateBuffer(&vcbd, &vcsd, &vertex_constant_buffer);
	context->VSSetConstantBuffers(0, 1, vertex_constant_buffer.GetAddressOf());

	// Pixel ConstBuffer
	struct PxlConstBuffer
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const PxlConstBuffer pcb =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};
	D3D11_BUFFER_DESC pcbd = {};
	pcbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pcbd.Usage = D3D11_USAGE_DEFAULT;
	pcbd.CPUAccessFlags = 0;
	pcbd.MiscFlags = 0;
	pcbd.ByteWidth = sizeof(pcb);
	pcbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA pcsd = {};
	pcsd.pSysMem = &pcb;

	wrl::ComPtr<ID3D11Buffer> pixel_constant_buffer;
	device->CreateBuffer(&pcbd, &pcsd, &pixel_constant_buffer);
	context->PSSetConstantBuffers(0, 1, pixel_constant_buffer.GetAddressOf());

	// reusable blob
	wrl::ComPtr<ID3DBlob> blob;

	// Pixel Shader
	wrl::ComPtr<ID3D11PixelShader> pixel_shader;
	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixel_shader);
	context->PSSetShader(pixel_shader.Get(), nullptr, 0);

	// Vertex Shader
	wrl::ComPtr<ID3D11VertexShader> vertex_shader;
	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertex_shader);
	context->VSSetShader(vertex_shader.Get(), nullptr, 0);

	// Vertex layout
	wrl::ComPtr<ID3D11InputLayout> input_layout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(
		ied, (UINT)std::size(ied),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&input_layout);
	context->IASetInputLayout(input_layout.Get());

	// Pick vertex topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	context->DrawIndexed((UINT)std::size(indices), 0, 0);
}

void Renderer::drawIndexed(UINT n) noexcept
{
	context->DrawIndexed(n, 0u, 0u);
}

void Renderer::setProjection(DirectX::FXMMATRIX _projection) noexcept
{
	projection = _projection;
}

DirectX::XMMATRIX Renderer::getProjection() const noexcept
{
	return projection;
}

DirectX::XMMATRIX Renderer::getCamera() const noexcept
{
	return camera_pos;
}

void Renderer::setCamera(DirectX::FXMMATRIX cam) noexcept
{
	camera_pos = cam;
}
