#include "Enemy.h"
#include <random>

Enemy::Enemy(Renderer& renderer, PathCorner* first_stop_target, Vector3 spawn_pos) :
	offset(Vector3(0.5 * rand() / (float)RAND_MAX - 0.25, 0.5 * rand() / (float)RAND_MAX - 0.25, 0))
{
	model = new SkinnedCube(renderer, "Hi");
	model->setScale(Vector3(0.5f, 0.5f, 0.5f));

	setPos(spawn_pos + offset);
	destination = first_stop_target;
	current_health = max_health;
}

void Enemy::update(GameData* _GD)
{
	move(_GD->dt);
}

void Enemy::damage(float amount)
{
	// To do, fetch SE_DMG_AMP stacks
	// stacks *= 0.005
	// amount *= 1 + stacks
	current_health -= static_cast<int>(amount);


	if (current_health <= 0)
	{
		// kill self
		//GameObject::destroy(this);
	}
}

void Enemy::move(float dt)
{
	Vector3 dist = (destination->getPos() + offset) - getPos();
	Vector3 dir = dist;
	dir.normalise();
	dir = dir * (SPEED * dt);

	if (dir.magnitude() >= dist.magnitude())
	{
		dir = dist;
		destination = destination->getNextStopTarget();

		if (destination == nullptr)
		{
			GameObject::destroy(this);
		}
	}
	setPos(getPos() + dir);
}
