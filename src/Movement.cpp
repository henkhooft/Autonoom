#include "Movement.h"

// Constructor
Movement::Movement(int angle, int distance)
	: wheel_angle(angle), distance_move_cm(distance)
{

}

// Destructor
Movement::~Movement()
{

}

void Movement::setDone(bool value)
{
	done = value;
}