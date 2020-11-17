#pragma once

struct GameData
{
	float dt;
	std::vector<class GameObject*>* game_objects;
	Renderer* renderer;
};