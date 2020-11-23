#pragma once
#include "Turret.h"

class TurretLaser :
    public Turret
{
public:
	TurretLaser(Renderer& renderer, Vector3 pos);
private:
	void attack(GameData* _GD) override;
	void pickTarget(GameData* _GD) override;
};

