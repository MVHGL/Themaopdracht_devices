#include "ir_transmitter.hpp"
ir_transmitter::ir_transmitter(hwlib::pin_out & transmitter):
	transmitter(transmitter)
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
	}
	else {		// Send 0
		transmitter.set(1);
		hwlib::wait_us(800);
		transmitter.set(0);
		hwlib::wait_us(1600);
	}
}

void ir_transmitter::send(const uint16_t& player_id, const uint16_t& data) {
	// Check if player_id or data isn't larger then 31
	if (!(player_id > 31 || data > 31)) {
		uint16_t message = 0x8000 | get_checksum(player_id, data);
		message |= (data << 5) | player_id;
		
		transmitter.set(1); // Prevent receiver from getting garbage
		hwlib::wait_us(3'500);
		transmitter.set(0);
		hwlib::wait_us(1'000);
		
		// Send data twice
		for (uint16_t i = 15; i >= 0 && i < 16; i--) {
			send_bit(((message >> i) & 1));
		}
		hwlib::wait_ms(3);
		for (uint16_t i = 15; i >= 0 && i < 16; i--) {
			send_bit(((message >> i) & 1));
		}
		
		for (uint16_t i = 15; i >= 0 && i < 16; i--) {
			hwlib::cout << ((message >> i) & 1);
		}
		hwlib::cout << '\n';
		hwlib::cout << message << '\n';
	}else {
		hwlib::cout << "{ERROR} player_id or data size too large!" << '\n';
	}
}




