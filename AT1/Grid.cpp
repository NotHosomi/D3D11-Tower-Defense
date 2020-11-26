#include "Grid.h"
#include "Tile.h"
#include "EnemySpawner.h"
#include "GameObject.h"

Grid::Grid(Renderer& renderer)
{
	int layout[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	tiles.reserve(GRID_WIDTH);
	for (int x = 0; x < GRID_WIDTH; ++x)
	{
		tiles.emplace_back();
		tiles.back().reserve(GRID_HEIGHT);
		for (int y = 0; y < GRID_HEIGHT; ++y)
		{
			bool path = layout[x + y * GRID_WIDTH];
			tiles.back().emplace_back(renderer, path ? "Path" : "Grass");
			Vector3 pos;
			pos.x = x;
			pos.y = y;
			tiles.back().back().setPos(pos);
		}
	}

	waypoints.reserve(13); // VERY IMPORTANT
	waypoints.emplace_back(Vector3(18, 7, 0), nullptr);
	waypoints.emplace_back(Vector3(16, 7, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(16, 11, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(13, 11, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(13, 3, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(17, 3, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(17, 1, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(2, 1, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(2, 5, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(9, 5, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(9, 13, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(3, 13, 0), &waypoints.back());
	waypoints.emplace_back(Vector3(3, 8, 0), &waypoints.back());

	EnemySpawner* e = new EnemySpawner(&waypoints.back());
	GameObject::create(e);
	e = new EnemySpawner(&(*(waypoints.rbegin() + 4)));
	GameObject::create(e);
}

void Grid::draw(Renderer& renderer)
{
	for (auto& column : tiles)
	{
		for (auto& tile : column)
		{
			tile.draw(renderer);
		}
	}
}

PathCorner* Grid::getFirstStopTarget()
{
	return &waypoints.back();
}

Tile* Grid::getTile(Vector3 coords)
{
	return getTile(static_cast<int>(coords.x), static_cast<int>(coords.y));
}

Tile* Grid::getTile(int x, int y)
{
	if (x < 0 || y < 0 ||
		x >= GRID_WIDTH || y >= GRID_HEIGHT)
	{
		return nullptr;
	}
	return &tiles[x][y];
}
