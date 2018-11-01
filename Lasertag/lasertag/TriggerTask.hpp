#ifndef _TRIGGERTASK_HPP
#define _TRIGGERTASK_HPP
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
	uint16_t fireRate;
public:
	TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame);
	void weaponSet(const uint16_t& fireRate);
	void getTriggerState();
	void main() override;
};
#endif
