#include "ir_receiver.hpp"

ir_receiver::ir_receiver(hwlib::pin_in & receiver, mainGameControlTask& mainGame):
	task("IR receiver task"),
	receiver(receiver),
	decoder(mainGame),
	pause_count(0),
	clock(this, 100, "IR Received clock"),
	pauses(this, "IR Receiver channel pauses"),
	counter(0)
	{}
	
void ir_receiver::get() {
	if (!receiver.get()) {
		pauses.write(pause_count);
		state = SIGNAL;
		counter++;
	}
	else {
		pause_count += 100;
		if (pause_count >= 3'000) {
			pause_count = 0;
		}
	}
}

void ir_receiver::putMessage() {
	mutex.wait();
	int pause = 0, msg1 = 0, msg2 = 0;
	for (int i = 0; i < 17; i++) {
		pause = pauses.read();
		if (pause > 200 && pause < 2'000) {
			msg1 |= (pause < 1'000) ? 1 : 0;
			if (i != 16) 
				msg1 <<= 1;
		}
	}
	for (int i = 0; i < 16; i++) {
		pause = pauses.read();
		if (pause > 200 && pause < 2'000) {
			msg2 |= (pause < 1'000) ? 1 : 0;
			if (i != 15) 
				msg2 <<= 1;
		}
	}
	decoder.write_message(msg1, msg2);
	mutex.signal();
}

void ir_receiver::main() {
	while (true) {
		switch (state) {
			case IDLE:
				if (counter == 33) {
					state = MESSAGE;
					counter = 0;
				}
				wait(clock);
				get();
				break;
			case SIGNAL:
				wait(clock);
				if (receiver.get()) {
					pause_count = 0;
					state = IDLE;
				}
				break;
			case MESSAGE:
				putMessage();
				state = IDLE;
				break;
		}
	}
}
