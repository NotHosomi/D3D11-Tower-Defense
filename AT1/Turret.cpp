#include "Turret.h"

void Turret::update(GameData* _GD)
{
	shoot_timer += _GD->dt;
	if (!validateTarget(_GD))
		return;

	updateRot();

	if (shoot_timer > attack_time)
	{
		attack(_GD);
		shoot_timer = 0;
	}
}

void Turret::draw(Renderer* renderer)
{
	//turret_base.draw(*renderer);
	if (model != nullptr)
	{
		model->draw(*renderer);
	}
}

Turret::Turret(Renderer& renderer, Vector3 pos) :
	turret_base(renderer)
{
	turret_base.setPos(pos);
}

bool Turret::validateTarget(GameData* _GD)
{
	if (target == nullptr)
	{
		pickTarget(_GD);
		return target != nullptr;
	}
	Vector3 dist = target->getPos() - getPos();
	if (dist.magnitude() > range)
	{
		pickTarget(_GD);
	}
	return target != nullptr;
}

void Turret::updateRot()
{
	if (target == nullptr)
		return;

	// calculate new rotation
	Vector3 dir = target->getPos() - getPos();
	dir.normalise();
	float yaw = atan2(dir.y, dir.x);
	setRot(Vector3(yaw, 0, 0));
}
