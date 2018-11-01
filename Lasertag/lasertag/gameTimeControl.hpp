#ifndef _GAMETIMECONTROL_HPP
#define _GAMETIMECONTROL_HPP

#include <functional>
#include "time.hpp"
#include "rtos.hpp"
#include "displayTask.hpp"

class gameTimeControl : public rtos::task<> {
private:
	Time time;
	rtos::clock clock;
	rtos::flag timeStart;
	displayTask& display;
	enum state_t { IDLE, KEEP_TIME };
	state_t state = IDLE;
	
	void checkTime();
public:
	gameTimeControl(displayTask& display);
	
	void setTime(const Time& time);
	bool isGameTimeOver();
	void startGameTimer();
	void main() override;
};
#endif
