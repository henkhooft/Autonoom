#include "ConnectionHandler.h"

// Constructor
ConnectionHandler::ConnectionHandler()
{
	init();
}

// Destructor
ConnectionHandler::~ConnectionHandler()
{
	if (USB != 0){
		close(USB);
	}
}

/**
 * @brief Initializes a serial connection for transfering data.
 * @details [long description]
 */
void ConnectionHandler::init()
{
	bool errorOccured = false;
	std::string device = "/dev/ttyAMA0";
	ROS_INFO("Starting serial connection on %s", device.c_str());

	/* Open File Descriptor */
	USB = open(device.c_str(), O_RDWR | O_NOCTTY);

	if (USB < 0) {
		ROS_FATAL("No valid filedescriptor for device");
		exit(-1);
	}

		/* Configure port */
	struct termios tty;
	struct termios tty_old;
	struct sigaction saio;
	memset (&tty, 0, sizeof tty);

	/* Error handling */
	if (tcgetattr (USB, &tty ) != 0) {
		ROS_ERROR_STREAM("Error " << errno << "  from tcgetattr: " << strerror(errno));
		errorOccured = true;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set signal handler */
	saio.sa_handler = &ConnectionHandler::signal_handler_IO;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction(SIGIO, &saio, NULL);

	fcntl(USB, F_SETFL, FASYNC);
	fcntl(USB, F_SETOWN, getpid());


	/* Set Baud rate */
	cfsetospeed(&tty, (speed_t)B9600);
	cfsetispeed(&tty, (speed_t)B9600);

	/* More port settings */
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
	   ROS_ERROR_STREAM("Error " << errno << " from tcsetattr");
	   errorOccured = true;
	}

	if (!errorOccured) {
		ROS_INFO("Serial port configured....");

		/* Send setup message */
		sleep(1);	// Wait a sec...
		writeString("HELLO WORLD\r");
	}
}

/**
 * @brief Reads data into a buffer.
 * @details [long description]
 * 
 * @param buffer Buffer to read into.
 * @return [description]
 */
int ConnectionHandler::readData(char buffer[])
{
	if (USB != 0) {
		ROS_INFO("Starting reading data");
		int n = 0, spot = 0;
		char buf = '\0';
		// memset(buffer, '\0', sizeof (buffer));

		// do {
		n = read( USB, &buf, 1);
		// sprintf( &buffer[spot], "%c", buf );
		// spot += n;
		// } while (buf != '\r' && n > 0);

		if (n < 0) {
			std::cout << "Error reading: " << strerror(errno) << " with error: " << n << std::endl;
		}
		else if (n == 0) {
			std::cout << "Read nothing!" << std::endl;
		}
		else {
			std::cout << "Response: " << buffer << std::endl;
			return n;
		}
	}
	return 0;
}

bool ConnectionHandler::writeString(std::string s)
{
	if (USB != 0) {
		if (write(USB, s.c_str(), s.size()) > 0) {
			return true;
		}
	}

	return false;
}

void ConnectionHandler::parseData(std::string s)
{
	std::stringstream stream;
	stream.str(s);

	std::string segment;
	std::vector<std::string> seglist;

	while(std::getline(stream, segment, '|')) {
		seglist.push_back(segment);
		std::cout << "Segment: " << segment << std::endl;
	}

	if (seglist.size() > 0) {
		
		/* String comparisons */
		segment = seglist.front();

		if (segment.compare("101") == 0) {
			// PingAck
		}
		else if (segment.compare("201") == 0) {
			// SonarAck

		}
	}
	else {
		ROS_WARN("Message could not be parsed");
	}
}

void ConnectionHandler::signal_handler_IO(int status)
{
	if (USB != 0) {
		ROS_INFO("Starting reading data");
		int n = 0, spot = 0;
		char buf = '\0';
		// memset(buffer, '\0', sizeof (buffer));

		// do {
		n = read( USB, &buf, 1);
		// sprintf( &buffer[spot], "%c", buf );
		// spot += n;
		// } while (buf != '\r' && n > 0);

		if (n < 0) {
			std::cout << "Error reading: " << strerror(errno) << " with error: " << n << std::endl;
		}
		else if (n == 0) {
			std::cout << "Read nothing!" << std::endl;
		}
		else {
			std::cout << "Response: " << buffer << std::endl;
			return n;
	}
	
}