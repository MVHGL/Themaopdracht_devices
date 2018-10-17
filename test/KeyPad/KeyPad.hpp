#pragma once
#include "hwlib.hpp"
#include "KeyPadListener.hpp"

/* Boundary object to communicate with the hardware */
class KeyPad {
private
	KeyPadListener& keyPad;
	/* hwlib::pins */
public:
	KeyPad(KeyPadListener& keyPadListener); // add hwlib::pins in constructor
};