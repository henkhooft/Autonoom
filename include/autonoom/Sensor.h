#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
	virtual Sensor();
	virtual ~Sensor();
	virtual int getLastMeasurement(); };
	inline int getAddress() { return address; }
protected:
	int address;
};

#endif