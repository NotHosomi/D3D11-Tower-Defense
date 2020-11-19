#pragma once
#include "GameObject.h"
#include "PathCorner.h"
//#include <random>

class EnemySpawner : public GameObject
{
public:
	EnemySpawner(PathCorner* first_stop_target);

	void update(GameData* _GD) override;
private:
	const float MAX_TIMER = 1;
	const float MIN_TIMER = 0.1f;
	float spawn_timer;

	void spawn(GameData* _GD);
	void setTimer();

	PathCorner* first_target = nullptr;
	Vector3 spawn_pos;
};