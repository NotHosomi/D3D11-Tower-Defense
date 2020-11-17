#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class Renderer
{
	friend class Bindable;
public:
	explicit Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void present();
	void wipe(float r, float g, float b) noexcept;

	void drawTri(float angle, float x, float y);

	void drawIndexed(UINT count) noexcept;
	void setProjection(DirectX::FXMMATRIX _projection) noexcept;
	DirectX::XMMATRIX getProjection() const noexcept;

	DirectX::XMMATRIX getCamera() const noexcept;
	void setCamera(DirectX::FXMMATRIX cam) noexcept;

private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera_pos;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_view;
};

