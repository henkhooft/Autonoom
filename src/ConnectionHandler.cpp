#include "ConnectionHandler.h"


// Constructor
ConnectionHandler::ConnectionHandler(std::vector<Sensor*>& _sensors)
	: sensors(_sensors)
{
	init();

	// run();
}

// Destructor
ConnectionHandler::~ConnectionHandler()
{
	if (USB != 0){

		// TODO restore old port settings
		close(USB);
	}
}

/**
 * @brief Initializes a serial connection on the UART interface for transfering data.
 * @details [long description]
 */
void ConnectionHandler::init()
{
	bool errorOccured = false;
	std::string device = "/dev/ttyACM0";
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
	memset (&tty, 0, sizeof tty);

	/* Error handling */
	if (tcgetattr (USB, &tty ) != 0) {
		ROS_ERROR_STREAM("Error " << errno << "  from tcgetattr: " << strerror(errno));
		errorOccured = true;
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
	tty.c_cc[VMIN]   =  5;                  // read doesn't block
	tty.c_cc[VTIME]  =  0;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Extra */
	tty.c_iflag = IGNPAR;
	tty.c_lflag = 0;
	tty.c_oflag = 0;

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applY attributes */
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
	   ROS_ERROR_STREAM("Error " << errno << " from tcsetattr");
	   errorOccured = true;
	}

	if (!errorOccured) {
		ROS_INFO("Serial port configured...");
	}
}

/**
 * @brief Threadable method for reading in data on the serial device
 * @details [long description]
 * @return Pointer to method
 */
void* ConnectionHandler::run()
{
	volatile int STOP = false;
	int result = 0;

	sleep(2);				// Wait a sec...
	writeString("100|");	// Send ping

	bool stringComplete = false;
	std::string inputString = "";

	if (USB != 0) {
		while(STOP == false) {

			char inChar[1];
			result = read(USB, inChar, 1);
			inputString += inChar;

			if (inChar[0] == '\n')
			{
				inputString.erase(inputString.size() - 1); // Remove carriage return
				inputString.erase( std::remove(inputString.begin(), inputString.end(), '\r'), inputString.end() );

				ROS_INFO("Got input: %s", inputString.c_str());
				parseData(inputString);
				inputString = "";
			}
		}
	}
	else {
		ROS_ERROR("Thread did not find a valid file descriptor");
	}
}

/**
 * @brief Write a string to the UART interface
 * @details [long description]
 * 
 * @param s String to write
 * @return If write was succesfull
 */
bool ConnectionHandler::writeString(std::string s)
{
	std::string copy(s);
	s += '\n';
	if (USB != 0) {
		if (write(USB, s.c_str(), s.size()) > 0) {
			ROS_INFO("Written: %s", copy.c_str());
			return true;
		}
	}

	return false;
}

/**
 * @brief Handles the commands in a string
 * @details Parses the string according to the '|' character and calls the corresponding handler
 * 
 * @param s String to parse
 */
void ConnectionHandler::parseData(std::string s)
{
	std::stringstream stream;
	stream.str(s);

	std::string segment;
	std::vector<std::string> seglist;

	while(std::getline(stream, segment, '|')) {
		seglist.push_back(segment);
		// std::cout << "Segment: " << segment << std::endl;
	}

	if (seglist.size() > 0) {
		
		/* String comparisons */
		segment = seglist.front();

		if (segment.compare("101") == 0) {			// Ping ack
			ROS_INFO("ATmega is found to be online!");
		}
		else if (segment.compare("201") == 0) {		// Sonar ack
			int counter = 1;

			for(std::vector<Sensor*>::iterator it = sensors.begin(); it != sensors.end(); ++it) {

    			Sonar* son = dynamic_cast<Sonar*>(*it);
    			ROS_INFO_STREAM("Sonar " << counter << " reports " << seglist[counter] << " cm");
				
				int s_value = 0;
				std::istringstream(seglist[counter]) >> s_value;

				son->setMeasurement(s_value);
				counter++;
			}
		}
	}
	else {
		ROS_WARN("Message could not be parsed");
	}
}

/**
 * @brief Start the threaded listener
 * @details [long description]
 */
void ConnectionHandler::start()
{
	pthread_t thread1;
	int iret1;

	iret1 = pthread_create(&thread1, NULL, &ConnectionHandler::run_helper, this);
	ROS_INFO("Serial thread started");
}
