#pragma once
#include "KeyPadListener.hpp"
/* Control object for KeyPad */

class KeyPadController : public KeyPadListener {
private:
	/* Some variables maybe */
public:
	void buttonPressed(const char& button) override;
};