#include "ir_transmitter.hpp"
ir_transmitter::ir_transmitter(hwlib::pin_out & transmitter):
	task(1, "transmitterTask"),
	transmitter(transmitter),
	playerIDPool("Player ID pool"),
	dataPool("Data pool"),
	transmitFlag(this, "Transmit flag"),
	transmitMutex("Transmit mutex")
	{}

uint16_t ir_transmitter::get_checksum(const uint16_t& player_id, const uint16_t& data) {
	uint16_t checkbits = 0x0;
	for (uint16_t i = 1; i <= 16; i *= 2) {
		checkbits |= ((data & i) ^ ((player_id & i)));
	}
	checkbits <<= 10;
	return checkbits;
}

void ir_transmitter::send_bit(const bool& value) {
	if (value) { // Send 1
		transmitter.set(1);
		hwlib::wait_us(1600);
		transmitter.set(0);
		hwlib::wait_us(800);
	} else {		// Send 0
		transmitter.set(1);
		hwlib::wait_us(800);
		transmitter.set(0);
		hwlib::wait_us(1600);
	}
}

void ir_transmitter::send(const uint16_t& player_id, const uint16_t& data) {
	playerIDPool.write(player_id);
	dataPool.write(data);
	transmitFlag.set();
}

void ir_transmitter::writeIRMessage() {
	uint16_t player_id = playerIDPool.read();
	uint16_t data = dataPool.read();
	// Reserve mutex
	transmitMutex.wait();
	// Check if player_id or data isn't larger then 31
	if (!(player_id > 31 || data > 31)) {
		// Calculate checksum
		uint16_t message = 0x8000 | get_checksum(player_id, data);
		message |= (data << 5) | player_id;
		
		// Send data
		for (uint16_t i = 15; i >= 0 && i < 16; i--) {
			send_bit(((message >> i) & 1));
		}
		// Wait 3 ms before sending message again
		hwlib::wait_ms(3);

		// Send data again
		for (uint16_t i = 15; i >= 0 && i < 16; i--) {
			send_bit(((message >> i) & 1));
		}
		// Send last pulse to mark the end of transmission
		transmitter.set(1);
		hwlib::wait_us(400);
		transmitter.set(0);
	}
	// Release mutex
	transmitMutex.signal();
}

void ir_transmitter::main(){
	state = IDLE;
	while(true){
		switch(state){
			case IDLE:
				wait(transmitFlag);
				state = SEND;
				break;
			case SEND:
				writeIRMessage();
				state = IDLE;
				break;
		}
	}
}




