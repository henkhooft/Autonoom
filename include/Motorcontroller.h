#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "ConnectionHandler.h"
#include "Movement.h"
#include <string>
#include <unistd.h>

class Motorcontroller
{
public:
	Motorcontroller(ConnectionHandler& _con);
	~Motorcontroller();
	void steer(Movement move);
	bool drive(Movement move);
	void stop();
	static bool TURBO;
private:
	ConnectionHandler& con;
	
};

#endif
