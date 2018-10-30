#pragma once
#include "hwlib.hpp"
#include <array>
#include "rtos.hpp"

/* Boundary object to communicate with the hardware */
class Keypad {
private:
	std::array<hwlib::pin_out*, 4> columns;
	std::array<hwlib::pin_in*, 4> rows;
	char keys[4][4] = {
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'} 
	};
	
public:
	Keypad(const std::array<hwlib::pin_in*, 4>& rows, 
		const std::array<hwlib::pin_out*, 4>& columns);
	
	char getChar();
};
