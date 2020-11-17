#include "Sheet.h"


class Grid
{
public:
	Grid(Renderer& renderer);
	Grid(const Grid&) = delete;
	Grid& operator= (const Grid&) = delete;

	void draw(Renderer& renderer);

private:
	static const int GRID_WIDTH = 20;
	static const int GRID_HEIGHT = 15;
	std::vector<std::vector<Sheet>> tiles;
};

