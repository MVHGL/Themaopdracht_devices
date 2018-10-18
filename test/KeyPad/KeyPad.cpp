#include "KeyPad.hpp"

KeyPad::KeyPad(KeyPadListener& keyPadListener, const std::array<hwlib::pin_in*, 4>& rows, 
	const std::array<hwlib::pin_out*, 4>& columns):
			   
	keyPadListener(keyPadListener),
	columns{columns},
	rows{rows}
	{
		for (int i = 0; i < 4; i++) 
			columns[i]->set(1);	
	}

void KeyPad::buttonPressed() {
	for (int i = 0; i < 4; i++) {
		columns[i]->set(0);	
		for (int j = 0; j < 4; j++) {
			if (!rows[j]->get()) {
				keyPadListener.buttonPressed(keys[j][i]);
				hwlib::wait_ms(100);
			}
		}
		columns[i]->set(1);
	}
}