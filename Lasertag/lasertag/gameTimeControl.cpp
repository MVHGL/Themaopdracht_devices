#include "gameTimeControl.hpp"

gameTimeControl::gameTimeControl(displayTask& display):
	task("Game time control task"),
	clock(this, 1'000'000, "Game Time control clock"),
	timeStart(this, "Time flag"),
	display(display)
{
}

void gameTimeControl::setTime(const Time& time) {
	this->time = time;
}

void gameTimeControl::startGameTimer() {	 
	timeStart.set();
}
bool gameTimeControl::isGameTimeOver() {
	return (time.getMin() == 0 && time.getSec() == 0);
}

void gameTimeControl::main() {
	while (true) {
		switch (state) {
			case IDLE:
				wait(timeStart);
				state = KEEP_TIME;
				break;
			case KEEP_TIME:
				wait(clock);
				time.updateTime();  	// clock waited one second, so edit the time
				if (isGameTimeOver()) {	// if time has ended
					display.showString("GAME OVER");
					state = IDLE;
				} else {
					display.showGameTime(time);
				} 	
				break;
		}
	}
}


