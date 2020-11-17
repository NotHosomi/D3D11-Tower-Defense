#include "TransformBuffer.h"
#include "Drawable.h"

std::unique_ptr<VertexConstantBuffer<TransformBuffer::Transforms>> TransformBuffer::vertex_constant_buffer;

TransformBuffer::TransformBuffer(Renderer& renderer, const Drawable& parent, UINT slot) :
	parent(parent)
{
	if (!vertex_constant_buffer)
	{
		vertex_constant_buffer = std::make_unique<VertexConstantBuffer<Transforms>>(renderer, slot);
	}
}

void TransformBuffer::bind(Renderer& renderer) noexcept
{
	const auto modelView = parent.getXMTransform() * renderer.getCamera();
	const Transforms transforms =
	{
		DirectX::XMMatrixTranspose(modelView),
		DirectX::XMMatrixTranspose(
			modelView *
			renderer.getProjection()
		)
	};
	vertex_constant_buffer->Update(renderer, transforms);
	vertex_constant_buffer->bind(renderer);
}