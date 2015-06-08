#include "ConnectionHandler.h"

// Constructor
ConnectionHandler::ConnectionHandler()
	: USB(0)
{
	init();
}

// Destructor
ConnectionHandler::~ConnectionHandler()
{

}

/**
 * @brief Initializes a serial connection for transfering data.
 * @details [long description]
 */
void ConnectionHandler::init()
{

	/* Open File Descriptor */
	USB = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY );

		/* Configure port */
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	/* Error handling */
	if (tcgetattr (USB, &tty ) != 0) {
		std::cout << "Error " << errno << "  from tcgetattr: " << strerror(errno) << std::endl;
	}

	/* Save old tty parameters */
	tty_old = tty;

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
	   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
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
		int n = 0, spot = 0;
		char buf = '\0';
		memset(buffer, '\0', sizeof (buffer));

		do {
			n = read( USB, &buf, 1);
			sprintf( &buffer[spot], "%c", buf );
			spot += n;
		} while (buf != '\r' && n > 0);

		if (n < 0) {
			std::cout << "Error reading: " << strerror(errno) << std::endl;
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

/**
 * @brief Writes data from a buffer into a serial connection.
 * @details [long description]
 * 
 * @param buffer Buffer to write from.
 * @return Returns true if write was successful.
 */
bool ConnectionHandler::writeData(unsigned char buffer[])
{
	// if (USB != 0) {
	// 	int n_written = 0;
	// 	int spot = 0;

	// 	do {
	// 		n_written = write( USB, &buffer[spot], 1);
	// 		spot += n_written;
	// 	} while (buffer[spot-1] != '\r' && n_written > 0);

	// 	if (n_written == (sizeof(buffer)/sizeof(*buffer))) {
	// 		return true;
	// 	}
	// }
	return false;
}

bool ConnectionHandler::writeString(std::string s)
{
	// unsigned char m_write[s.size()];
	// strcpy( (char*)m_write, s.c_str());

	// writeData(m_write);

	if (USB != 0) {
		if (write(USB, s.c_str(), s.size()) > 0) {
			return true;
		}
	}

	return false;
}

void ConnectionHandler::parseData(std::string s)
{

}