#include "ir_receiver.hpp"

ir_receiver::ir_receiver(hwlib::pin_in & receiver):
	task("IR receiver task"),
	receiver(receiver),
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
		if (pause_count >= 3'000)
			pause_count = 0;
	}
}

void ir_receiver::print() {
	int pause = 0, msg1 = 0, msg2 = 0;
	pause = pauses.read();
	for (int i = 0; i < 16; i++) {
		pause = pauses.read();
		//hwlib::cout << "msg1 " << pause << '\t';
		if (pause > 200 && pause < 2'000) {
			msg1 <<= 1;
			msg1 |= (pause < 1'000) ? 1 : 0;
		}
	}
	pause = pauses.read();
	hwlib::cout << '\n';
	for (int i = 0; i < 16; i++) {
		pause = pauses.read();
		//hwlib::cout << "msg2 "<< pause << '\t';
		if (pause > 200 && pause < 2'000) {
			msg2 <<= 1;
			msg2 |= (pause < 1'000) ? 1 : 0;
		}
	}
	hwlib::cout << '\n';
	for (int i = 0; i < 16; i++) {
		hwlib::cout << (msg1 & 1);
		msg1 >>= 1;
	}
	hwlib::cout << '\n';
	for (int i = 0; i < 16; i++) {
		hwlib::cout << (msg2 & 1);
		msg2 >>= 1;
	}
}

void ir_receiver::main() {
	while (true) {
		switch (state) {
			case IDLE:
				if (counter == 34) {
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
				print();
				state = IDLE;
				break;
		}
	}
}
