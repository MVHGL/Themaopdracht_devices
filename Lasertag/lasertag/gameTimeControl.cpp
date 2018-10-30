#include "gameTimeControl.hpp"

gameTimeControl::gameTimeControl(const Time& time, mainGameControlTask& mainGame):
	time(time),
	clock(this, 1'000'000, "Game Time control clock"),
	mainGame(mainGame)
{
}

bool gameTimeControl::gameTimeOver() {
	return (time.getMin() == 0 && time.getSec() == 0);
}

void gameTimeControl::main() {
	while (true) {
		switch (state) {
			case IDLE:
				wait(clock);
				break;
			case KEEP_TIME:
				time.updateTime();  // clock waited one second, so edit the time
				if (!gameTimeOver()) // if time has NOT ended
					state = KEEP_TIME;
				else // game time has ended, end the game
					// mainGame.gameTimeOver();
				state = IDLE;
				break;
		}
	}
}


