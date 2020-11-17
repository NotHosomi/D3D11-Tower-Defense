#include "PathCorner.h"
#include "Ball.h"


PathCorner::PathCorner(Vector3 pos, PathCorner* next_stop) :
	pos(pos), next_destination(next_stop)
{}

Vector3 PathCorner::getPos()
{
	return pos;
}

PathCorner* PathCorner::getNextStopTarget()
{
	return next_destination;
}
