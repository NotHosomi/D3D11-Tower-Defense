#include "TurretLaser.h"

TurretLaser::TurretLaser(Renderer& renderer, Vector3 pos) :
	Turret(renderer, pos)
{
	model = new SkinnedCube(renderer, "blank");
	setPos(pos);
	pos.z += 2;
	model->setPos(pos);
	model->setScale(Vector3(0.5f, 0.5f, 2));

	damage = 50;
	attack_time = 1;
	range = 6;
}

void TurretLaser::attack(GameData* _GD)
{
	// Todo: shooting fx
	target->damage(damage);
}


// This turret attacks the closest enemy
void TurretLaser::pickTarget(GameData* _GD)
{
	int highest_max = 0;

	// FIXME: This is bad. Needs optimizing.
	// Using seperate vectors of Enemies and other GameObjects would remove need for Dynamic cast, but may slow down the GameObject instatiation in App.cpp
	for (GameObject* go : *_GD->game_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(go);
		if (enemy == nullptr)
		{
			continue;
		}

		int hp = enemy->getMaxHp();
		if (hp > highest_max)
		{
			highest_max = hp;
			target = enemy;
		}
	}
	if (highest_max == 0)
	{
		// no target
		target = nullptr;
		return;
	}
	updateRot();
}