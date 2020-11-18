#pragma once
#include "Primitive.h"
#include <random>
#include <string>

class Tile : public Primitive<Tile>
{
public:
	Tile(Renderer& renderer, std::string texture);
	void update(float dt) noexcept override {};
private:
	static constexpr float TILE_DIMS = 1;

	// Tower* occupier = null;
};