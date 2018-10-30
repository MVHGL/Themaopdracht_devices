#include "KeyPad.hpp"

Keypad::Keypad(const std::array<hwlib::pin_in*, 4>& rows, 
	const std::array<hwlib::pin_out*, 4>& columns):
			   
	columns{columns},
	rows{rows}
	{
		for (int i = 0; i < 4; i++) 
			columns[i]->set(1);	
	}

char Keypad::getChar() {
	char pressedChar = 0;
	for (int i = 0; i < 4; ++i) {
		columns[i]->set(0);	
		for (int j = 0; j < 4; ++j)
			if (!rows[j]->get()) {
				pressedChar = keys[j][i];
			}
		
		columns[i]->set(1);
	}
	return pressedChar;
}