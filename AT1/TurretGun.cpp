#include "TurretGun.h"

TurretGun::TurretGun(Renderer& renderer, Vector3 pos) :
	Turret(renderer, pos)
{
	model = new SkinnedCube(renderer, "blank");
	setPos(pos);
	pos.z += 1;
	model->setPos(pos);
	model->setScale(Vector3(0.5f, 0.5f, 0.5f));

	damage = 4;
	attack_time = 0.2;
	range = 4.5;
}

void TurretGun::attack(GameData* _GD)
{
	// simple attack for the simplest turret
	target->damage(damage);
	pickTarget(_GD);
}

// This turret attacks the closest enemy
void TurretGun::pickTarget(GameData* _GD)
{
	float shortest_dist = range;

	// FIXME: This is bad. Needs optimizing.
	// Using seperate vectors of Enemies and other GameObjects would remove need for Dynamic cast, but may slow down the GameObject instatiation in App.cpp
	for (GameObject* go : *_GD->game_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(go);
		if (enemy == nullptr)
		{
			continue;
		}

		Vector3 diff = enemy->getPos() - getPos();
		float dist = diff.magnitude();
		if (dist < shortest_dist)
		{
			shortest_dist = dist;
			target = enemy;
		}
	}
	if (shortest_dist == 0)
	{
		// no target
		target = nullptr;
		return;
	}
	updateRot();
}
