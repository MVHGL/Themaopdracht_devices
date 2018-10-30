#include "KeyPadController.hpp"
#include "hwlib.hpp"

KeypadController::KeypadController(const std::array<hwlib::pin_in*, 4>& rows, 
		const std::array<hwlib::pin_out*, 4>& columns):
	clock(this, 100'000, "KeypadController clock"),
	keypad(rows, columns)
	{ }

void KeypadController::main() {
	while (true) {
		wait(clock);
		if (keypad.getChar() != 0) {
			/* logica */
			hwlib::cout << keypad.getChar();
		}
	}
}