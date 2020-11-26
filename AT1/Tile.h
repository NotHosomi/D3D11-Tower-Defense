#pragma once
#include "Primitive.h"
#include <random>
#include <string>

class Turret;

class Tile : public Primitive<Tile>
{
public:
	Tile(Renderer& renderer, std::string texture);
	void update(float dt) noexcept override {};

	Turret* fetchOccupier();
	void setOccupier(Turret* new_tower);
private:
	static constexpr float TILE_DIMS = 1;

	Turret* occupier = nullptr;
};