#include "ir_decoder.hpp"

ir_decoder::ir_decoder(mainGameControlTask& mainGame):
	task("IR decoder"),
	messages(this, "IR decoder messages channel"),
	mainGame(mainGame)
	{ }

void ir_decoder::write_message(const int& message1, const int& message2) {
	messages.write(message1);
	messages.write(message2);
}

void ir_decoder::check_message() {
	int garbage;
	int message = messages.read();
	uint16_t new_checksum = extract(message);
	
	if (checksum == new_checksum) {
		garbage = messages.read();
		mainGame.IRMessageReceived(player_id, data);
		//hwlib::cout << "Received 1st time containing: " << data << ' ' << player_id << '\n';
	} else {
		message = messages.read();
		new_checksum = extract(message);
		if (checksum == new_checksum) {
			mainGame.IRMessageReceived(player_id, data);
			//hwlib::cout << "Received 2nd time containing: " << data << ' ' << player_id << '\n';

		} else {
			hwlib::cout << "{ERROR}\n";
		}
	}	
}

uint16_t ir_decoder::get_checksum(const uint16_t& player_id, const uint16_t& data) {
	uint16_t checkbits = 0x0;
	for (uint16_t i = 1; i <= 16; i *= 2) {
		checkbits |= ((data & i) ^ ((player_id & i)));
	}
	return checkbits;
}

uint16_t ir_decoder::extract(const int& message) {
	player_id = message & 0b11111;
	data = (message >> 5) & 0b11111;
	checksum = (message >> 10) & 0b11111;
	return get_checksum(player_id, data);
}

void ir_decoder::main() {
	state_t state = IDLE;
	while (true) {
		switch (state) {
			case IDLE:
				wait(messages);
				state = DECODING;
				break;
			case DECODING:
				check_message();
				state = IDLE;
				break;
		}
	}
}
