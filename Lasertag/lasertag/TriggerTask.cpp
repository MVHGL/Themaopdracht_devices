#include "TriggerTask.hpp"

TriggerTask::TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame):
	task("Triggertask"),
	trigger(trigger),
	mainGame(mainGame),
	fireRateTimer(this, "Fire rate timer"),
	fireRateFlag(this, "Fire rate flag"),
	fireRatePool("Fire rate pool"),
	clock(this, 500'000, "Triggertask clock") {}

void TriggerTask::weaponSet() {
	fireRateFlag.set();
}

void TriggerTask::main() {
	state_t state = IDLE;
	while (true) {
		switch (state) {
			case IDLE: {
				wait(fireRateFlag);
				fireRate = fireRatePool.read() * 1'000;
				state = CHECKING;
				break;
			}
			case CHECKING: {
				wait(clock);
				if (trigger.get()) {
					mainGame.triggered();
					fireRateTimer.set(fireRate);
				}
				break;
			}
		}
	}
}