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

#include "ros/ros.h"

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
	int readData(char buffer[]);
	void parseData(std::string s);
	bool writeString(std::string s);
private:
	ConnectionHandler();
	static void signal_handler_IO(int status);
	int USB;
};

#endif