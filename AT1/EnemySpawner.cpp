#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(PathCorner* first_stop_target)
{
	first_target = first_stop_target;

	Vector3 pos = first_stop_target->getPos();
	pos.x = -1;
	spawn_pos = pos;

	// intentional constant seed, for testing purposes
	srand(0);
	spawn_timer = 1;
}

void EnemySpawner::update(GameData* _GD)
{
	spawn_timer -= _GD->dt;
	if (spawn_timer <= 0)
	{
		spawn(_GD);
		setTimer();
	}
}

void EnemySpawner::spawn(GameData* _GD)
{
	Enemy::EnemyType type = static_cast<Enemy::EnemyType>(rand() % 5);
	Enemy* new_enemy = new Enemy(*_GD->renderer, first_target, spawn_pos, type);
	GameObject::create(new_enemy);
}

void EnemySpawner::setTimer()
{
	spawn_timer = rand() / (float)RAND_MAX;
	spawn_timer = spawn_timer * (MAX_TIMER - MIN_TIMER) + MIN_TIMER;
}