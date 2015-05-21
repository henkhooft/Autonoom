#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

class ConnectionHandler
{
public:
	~ConnectionHandler();
	static ConnectionHandler& getInstance();
	void init();
	int readData(char* buffer);
	bool writeData(char* buffer);
private:
	ConnectionHandler(ConnectionHandler const&) = delete;
	void operator=(ConnectionHandler const& ) = delete;
};

#endif