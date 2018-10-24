#include "ir_receiver.hpp"

ir_receiver::ir_receiver(PauseListener& pauseListener, hwlib::pin_in & receiver):
	task(1, "IR receiver task"),
	receiver(receiver),
	pauseListener(pauseListener),
	clock(this, 100, "IR Received clock")
	{}
	



void ir_receiver::main() {
	pauseCounter = 0;
	while (true) {
		switch (state) {
			case IDLE:
				wait(clock);
				if (!receiver.get()) {
					hwlib::cout << "pauseDetected\n";
					pauseListener.pauseDetected(pauseCounter);
					state = SIGNAL;
				}
				else {
					hwlib::cout << pauseCounter << '\n';
					pauseCounter += 100;
					if (pauseCounter >= 9'000)
						pauseCounter = 0;
				}
				break;
			case SIGNAL:
				wait(clock);
				if (receiver.get()) {
					pauseCounter = 0;
					state = IDLE;
				}
				break;
		}
	}
}
