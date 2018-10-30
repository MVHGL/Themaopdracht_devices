#pragma once
#include "rtos.hpp"

struct Time {
	static int min;
	int sec;
};

class gameTimeControl : public rtos::task<> {
private:
	rtos::clock gameTime;
	
public:
	gameTimeControl();

};

