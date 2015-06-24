#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <stdio.h>		// Standard input/output
#include <iostream>
#include <stdlib.h>		
#include <string>		// String functions
#include <sstream>
#include <unistd.h>		// UNIX standard functions
#include <fcntl.h>		// File control
#include <errno.h>		// Error definitions
#include <termios.h>	// POSIX terminal control
#include <sys/signal.h> // Signal handling
#include <pthread.h>	// Threading

#include "ros/ros.h"
#include "Sensor.h"
#include "Sonar.h"

class ConnectionHandler
{
public:	
	ConnectionHandler(std::vector<Sensor*>& _sensors);
	~ConnectionHandler();

	void parseData(std::string s);
	bool writeString(std::string s);
	void start();
private:
	void *run();
	void init();
	std::vector<Sensor*>& sensors;
	static void *run_helper(void *context)
	{
		return ((ConnectionHandler*)context)->run();
	}
	int USB;
};

#endif
