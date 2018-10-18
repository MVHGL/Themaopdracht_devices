#pragma once
#include "hwlib.hpp"
#include "KeyPadListener.hpp"
#include <array>

/* Boundary object to communicate with the hardware */
class KeyPad {
private:
	KeyPadListener& keyPadListener;
	std::array<hwlib::pin_out*, 4> columns;
	std::array<hwlib::pin_in*, 4> rows;
	char keys[4][4] = {
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'} 
	};
	
public:
	KeyPad(KeyPadListener& keyPadListener, const std::array<hwlib::pin_in*, 4>& rows, 
	const std::array<hwlib::pin_out*, 4>& columns);
	
	void buttonPressed();
};
