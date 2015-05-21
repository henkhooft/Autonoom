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
	bool writeData(unsigned char buffer[]);
private:
	ConnectionHandler();
	int USB;
};

#endif