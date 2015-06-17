#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement
{
public:
	Movement(int angle, int distance);
	~Movement();
	void setDone(bool value);

	// Get set
	inline int getWheelAngle() { return wheel_angle;}
	inline int getDistance() { return distance_move_cm;}
private:
	bool done;
	int wheel_angle;
	int distance_move_cm;
};

#endif