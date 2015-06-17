#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "ConnectionHandler.h"
#include "Movement.h"
#include <string>
#include <unistd.h>

class Motorcontroller
{
public:
	Motorcontroller();
	~Motorcontroller();
	bool drive(Movement move);
	void stop();
private:
	ConnectionHandler& con;
};

#endif