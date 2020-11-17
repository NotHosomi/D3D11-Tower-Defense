#pragma once
#include "Primitive.h"
#include "Vector3.h"
#include <string>

class SkinnedCube : public Primitive<SkinnedCube>
{
public:
	SkinnedCube(Renderer& renderer, std::string texture);
private:
};