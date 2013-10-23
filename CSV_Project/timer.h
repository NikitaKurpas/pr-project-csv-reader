#pragma once

#include <time.h>

// A simple timer class
class timer
{
private:
	clock_t start;
	clock_t finish;

public:
	double GetDuration() { return (double)(finish - start); }
	void Start() { start = clock(); }
	void Stop()  { finish = clock(); }

};

