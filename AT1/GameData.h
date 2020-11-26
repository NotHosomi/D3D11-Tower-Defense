#pragma once

struct GameData
{
	float dt;
	std::vector<class GameObject*>* game_objects;
	class Grid* world;
	class Renderer* renderer;
	class Keyboard* keys;
};