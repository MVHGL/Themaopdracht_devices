#include "TriggerTask.hpp"

TriggerTask::TriggerTask(hwlib::pin_in& trigger, mainGameControlTask& mainGame):
	task("Triggertask"),
	trigger(trigger),
	mainGame(mainGame),
	clock(this, 250'000, "Triggertask clock")
{}

void TriggerTask::main() {
	while (true) {
		wait(clock);
		if (trigger.get()) {
			mainGame.triggered();
		}
	}
}