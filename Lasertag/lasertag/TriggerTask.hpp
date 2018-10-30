#pragma once
#include "rtos.hpp"
#include "hwlib.hpp"
#include "mainGameControlTask.hpp"

class TriggerTask : public rtos::task<> {
private:
	hwlib::pin_in& trigger;
	mainGameControlTask& mainGame;
	rtos::timer fireRateTimer;
	rtos::flag fireRateFlag;
	rtos::pool<uint16_t> fireRatePool;
	rtos::clock clock;
	
	enum state_t { IDLE, CHECKING };
public:
	TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame);
	void weaponSet();
	void main() override;
};

