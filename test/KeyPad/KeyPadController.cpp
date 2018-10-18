#include "KeyPadController.hpp"
#include "hwlib.hpp"

KeypadController::KeypadController(const std::array<hwlib::pin_in*, 4>& rows, 
		const std::array<hwlib::pin_out*, 4>& columns):
	timer(this, "KeypadController Timer"),
	keypad(rows, columns)
	{ }

void KeypadController::main() {
	while (true) {
		if (keypad.getChar() != 0) {
			/* logica */
			timer.set(500'000);
			wait(timer);
		}
	}
}