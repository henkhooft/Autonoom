#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement
{
public:
	Movement(int angle, int distance);
	~Movement();
	void setDone(bool value);
private:
	bool done;
	int wheel_angle;
	int distance_move_cm;
};

#endif