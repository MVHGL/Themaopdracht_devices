#include "KeyPadController.hpp"
#include "hwlib.hpp"

void KeyPadController::buttonPressed(const char& button) {
	hwlib::cout << button;
}