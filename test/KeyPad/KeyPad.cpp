#include "KeyPad.hpp"

KeyPad::KeyPad(KeyPadListener& keyPadListener) :
	keyPad(keyPadListener) /*hwlib::pins initialize*/ { }