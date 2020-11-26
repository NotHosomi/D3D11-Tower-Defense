#pragma once
#include "GameObject.h"

class Picker :
    public GameObject
{
public:
    Picker(Renderer& renderer);
    void update(GameData* _GD) override;

private:
};

