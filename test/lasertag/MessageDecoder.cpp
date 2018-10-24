#include "MessageDecoder.hpp"

MessageDecoder::MessageDecoder():
	task("Message decoder"),
	pauses(this, "Pause channel"),
	state(IDLE)
	{ }

void MessageDecoder::check() {
	for (int i = 31; i >= 0 && i < 32; i--) {
		hwlib::cout << ((message >> i) & 1);
	}
	hwlib::cout << '\n';
}

void MessageDecoder::pauseDetected(const int& pause) {
	pauses.write(pause);
}

void MessageDecoder::main() {
	while (true) {
		switch (state) {
			case IDLE:
				wait(pauses);
				pause = pauses.read();
				
				if (pause > 4'000 && pause < 5'000){
					message = 0; amount = 0;
					state = MESSAGE;
				}
				break;
			case MESSAGE:
				wait(pauses);
				pause = pauses.read();
				if (pause > 200 && pause < 2'000) {
					amount++;
					message <<= 1;
					message |= ((pause > 1'000) ? 1 : 0);
					if (amount == 32) {
						check();
						amount = 0; message = 0; pause = 0;
						state = IDLE;
					}
				}
				break;
		}
	}
}

