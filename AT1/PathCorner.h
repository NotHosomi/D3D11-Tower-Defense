#pragma once
#include "Vector3.h"

class PathCorner
{
public:
	PathCorner(Vector3 pos, PathCorner* next_stop = nullptr);

	Vector3 getPos();
	PathCorner* getNextStopTarget();

private:
	Vector3 pos;
	// Todo implement multiple destinations
	PathCorner* next_destination = nullptr;
};

