#pragma once
#include "Turret.h"
class TurretMage : public Turret
{
public:
	TurretMage(Renderer& renderer, Vector3 pos);
private:
	void attack(GameData* _GD) override;
	void pickTarget(GameData* _GD) override;
};

