#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "ConnectionHandler.h"
#include "Movement.h"

class Motorcontroller
{
public:
	Motorcontroller();
	~Motorcontroller();
	bool drive(Movement move);
	void stop();
private:
	ConnectionHandler* apCon;
};

#endif