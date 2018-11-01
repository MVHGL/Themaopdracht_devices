#ifndef _TRIGGERTASK_HPP
#define _TRIGGERTASK_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "mainGameControlTask.hpp"

class TriggerTask : public rtos::task<> {
private:
	hwlib::pin_in& trigger;
	mainGameControlTask& mainGame;
	rtos::clock clock;
public:
	TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame);
	void main() override;
};
#endif
