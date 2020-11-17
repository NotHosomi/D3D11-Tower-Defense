#include "Enemy.h"
#include <random>

Enemy::Enemy(Renderer& renderer, PathCorner* first_stop_target, Vector3 spawn_pos)
	//offset((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0)
{
	model = new SkinnedCube(renderer, "Hi");
	setPos(spawn_pos);

	destination = first_stop_target;
	current_health = max_health;
}

void Enemy::update(float dt)
{
	move(dt);
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
	dir * speed * dt;

	if (dir.magnitude() >= dist.magnitude())
	{
		dir = dist;
		destination = destination->getNextStopTarget();

		if (destination == nullptr)
		{
			// Damage objective
			// Kill self
		}
	}
}
