#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
	Sensor(int _address) {address = _address; }
	virtual ~Sensor() { } 
	virtual int getLastMeasurement() { return 0; } 
	inline int getAddress() { return address; }
protected:
	int address;
};

#endif