#pragma once
#include "Keypad.hpp"
/* Control object for KeyPad */

class KeypadController : public rtos::task<> {
private:
	rtos::timer timer;
	Keypad keypad;
public:
	KeypadController(const std::array<hwlib::pin_in*, 4>& rows, 
		const std::array<hwlib::pin_out*, 4>& columns);
		
	void main() override;
};