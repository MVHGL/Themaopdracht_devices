#pragma once

/* Interface base class */
class KeyPadListener {
public:
	virtual void buttonPressed(const char& button) = 0;
};