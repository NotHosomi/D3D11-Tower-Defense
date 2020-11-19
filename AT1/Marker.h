#pragma once
#include "GameObject.h"
class Marker : public GameObject
{
public:
    Marker(Renderer& renderer, Vector3 pos);
    void update(GameData* _GD) override {}
};

