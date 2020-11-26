#pragma once
#include "Tile.h"
#include "PathCorner.h"


class Grid
{
public:
	Grid(Renderer& renderer);
	Grid(const Grid&) = delete;
	Grid& operator= (const Grid&) = delete;


	void draw(Renderer& renderer);
	PathCorner* getFirstStopTarget();

	Tile* getTile(Vector3 coords);
	Tile* getTile(int x, int y);

	static const int GRID_WIDTH = 20;
	static const int GRID_HEIGHT = 15;
private:
	std::vector<std::vector<Tile>> tiles; // TODO: make single dimension
	std::vector<PathCorner> waypoints;
};

