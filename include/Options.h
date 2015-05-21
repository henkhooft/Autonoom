#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
	Options();
	~Options();
	void reset();
private:
	int speed_limit;
	int sonar_limit;
};

#endif