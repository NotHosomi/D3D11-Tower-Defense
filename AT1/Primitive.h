#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"

template<class T>
class Primitive : public Drawable
{
protected:
	static bool checkStatics() noexcept
	{
		return !static_binds.empty();
	}
	static void addStaticBind(std::unique_ptr<Bindable> bind) noexcept
	{
		assert("Use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
		static_binds.push_back(std::move(bind));
	}
	void addStaticIndexBuffer(std::unique_ptr<IndexBuffer> buffer) noexcept
	{
		index_buffer = buffer.get();
		static_binds.push_back(std::move(buffer));
	}
	void fetchStaticIndices() noexcept
	{
		assert("Index buffer already set" && index_buffer == nullptr);
		for (const auto& iter : static_binds)
		{
			if (const auto ib = dynamic_cast<IndexBuffer*>(iter.get()))
			{
				index_buffer = ib;
				return;
			}
		}
		assert("No index buffer found in static binds" && index_buffer != nullptr);
	}
	const std::vector<std::unique_ptr<Bindable>>& getStaticBinds() const noexcept
	{
		return static_binds;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> static_binds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> Primitive<T>::static_binds;