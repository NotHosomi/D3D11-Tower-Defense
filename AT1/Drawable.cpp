#include "Drawable.h"
#include "IndexBuffer.h"
#include "Bindable.h"
#include <cassert>
#include <typeinfo>

void Drawable::draw(Renderer& renderer) const noexcept
{
	for (auto& it : binds)
	{
		it->bind(renderer);
	}
	for (auto& it : getStaticBinds())
	{
		it->bind(renderer);
	}
	renderer.drawIndexed(index_buffer->count());
}

void Drawable::addBind(std::unique_ptr<Bindable> bind) noexcept
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
	binds.push_back(std::move(bind));
}

void Drawable::addIndexBuffer(std::unique_ptr<class IndexBuffer> buffer) noexcept
{
	assert("Attempting to add index buffer a second time" && index_buffer == nullptr);
	index_buffer = buffer.get();
	binds.push_back(std::move(buffer));
}
