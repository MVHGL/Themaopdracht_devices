#include "gameTimeControl.hpp"

gameTimeControl::gameTimeControl(const Time& time, mainGameControlTask& mainGame):
	task("Game time control task"),
	time(time),
	clock(this, 1'000'000, "Game Time control clock"),
	timeStart(this, "Time flag"),
	mainGame(mainGame)
{
}

void gameTimeControl::startGameTimer() {
	timeStart.set();
}

bool gameTimeControl::gameTimeOver() {
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
				time.updateTime();  // clock waited one second, so edit the time
				if (gameTimeOver()) {// if time has ended
					mainGame.gameOver();
					display.gameOver();
					state = IDLE;
				} else {
					display.showGameTime(time);
				} 	
				break;
		}
	}
}


