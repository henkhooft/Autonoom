#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
	Options();
	~Options();
	void reset();

	inline int getMaxSpeed() { return speed_limit;}
	inline int getMaxRange() { return sonar_limit;}
	inline bool getIsDriving() { return isDriving;}
private:
	int speed_limit;
	int sonar_limit;
	bool isDriving;

	/* Current sensor data */
	
};

#endif