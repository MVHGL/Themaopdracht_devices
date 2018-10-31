#ifndef _GAMETIMECONTROL_HPP
#define _GAMETIMECONTROL_HPP
#include "time.hpp"
#include "rtos.hpp"
#include "mainGameControlTask.hpp"
#include "displayTask.hpp"

class gameTimeControl : public rtos::task<> {
private:
	Time time;
	rtos::clock clock;
	rtos::flag timeStart;
	mainGameControlTask mainGame;
	displayTask& display;
	enum state_t { IDLE, KEEP_TIME };
	state_t state = IDLE;
	
	void checkTime();
	bool gameTimeOver();
public:
	gameTimeControl(const Time& time, mainGameControlTask* mainGame, displayTask& display);
	void startGameTimer();
	void main() override;
};
#endif
