#pragma once
#include "Turret.h"

class TurretGun : public Turret
{
public:
	TurretGun(Renderer& renderer, Vector3 pos);
private:
	void attack(GameData* _GD) override;
	void pickTarget(GameData* _GD) override;
};

