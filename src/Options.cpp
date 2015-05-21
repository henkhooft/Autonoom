#include "Options.h"

#define SONAR_LIMIT_DEFAULT 10
#define SPEED_LIMIT_DEFAULT 20

// Constructor
Options::Options()
{
	reset();
}

// Destructor
Options::~Options()
{

}

void Options::reset()
{
	speed_limit = SPEED_LIMIT_DEFAULT;
	sonar_limit = SONAR_LIMIT_DEFAULT;
}