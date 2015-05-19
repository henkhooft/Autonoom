#ifndef CONNECTIONHANDLER
#define CONNECTIONHANDLER

class ConnectionHandler
{
public:
	~ConnectionHandler();
	static ConnectionHandler getInstance();
	void init();
	int readData(char* buffer);
	bool writeData(char* buffer);
private:
	ConnectionHandler();
	ConnectionHandler instance;
};

#endif