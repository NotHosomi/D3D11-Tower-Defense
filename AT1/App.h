#pragma once
#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include "PointLight.h"
#include <vector>
#include "GameData.h"
#include "Tile.h"
#include "Grid.h"

class App
{
public:
	App();
	~App();

	int run();
	
private:
	void tick();

	Timer timer;

	Window wnd;

	Camera cam;
	// Just the one light will suffice for now 
	PointLight light;

	// outdated
	std::vector<std::unique_ptr<class Drawable>> drawables;
	// TODO: Switch with a list?
	std::vector<class GameObject*> game_objects;
	Grid* world;
	//class SkinnedCube* debug_boi;
	class Ball* debug_boi_2;
	GameData _GD;
};