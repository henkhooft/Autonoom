#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <stdio.h>		// Standard input/output
#include <iostream>
#include <stdlib.h>		
#include <string.h>		// String functions
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
	~ConnectionHandler();
	static ConnectionHandler& getInstance()
	{
		static ConnectionHandler instance;
		return instance;
	}
	void init();
	void parseData(std::string s);
	bool writeString(std::string s);
	void start();
	inline void addSensors(std::vector<Sensor*>& _sensors) {sensors = _sensors;}
private:
	ConnectionHandler();
	void *run();
	static void *run_helper(void *context)
	{
		return ((ConnectionHandler*)context)->run();
	}
	int USB;
	std::vector<Sensor*> sensors;
};

#endif