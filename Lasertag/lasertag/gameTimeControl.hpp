#pragma once
#include "time.hpp"
#include "rtos.hpp"
#include "mainGameControlTask.hpp"
class gameTimeControl : public rtos::task<> {
private:
	Time time;
	rtos::clock clock;
	mainGameControlTask& mainGame;
	enum state_t { IDLE, KEEP_TIME };
	state_t state = IDLE;
	
	void checkTime();
	bool gameTimeOver();
public:
	gameTimeControl(const Time& time, mainGameControlTask& mainGame);
	void main() override;
};

