#pragma once
#include "GameObject.h"

class Trace : public GameObject
{
public:
	Trace(Renderer& renderer, Vector3 start, Vector3 end, Vector3 colour);
	void update(GameData* _GD) override;
private:

};

