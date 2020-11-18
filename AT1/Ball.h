#pragma once
#include "Primitive.h"
#include <random>
#include "Vector3.h"

class Ball : public Primitive<Ball>
{
public:
	Ball(Renderer& renderer, int lati, int longi);
private:
};