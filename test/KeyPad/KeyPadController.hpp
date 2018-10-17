#pragma once
#include "KeyPadListener.hpp"
/* Control object for KeyPad */

class KeyPadController : public KeyPadListener {
private:
	/* Some variables maybe */
public:
	void buttonAPressed() override;
	void buttonBPressed() override;
	void button1Pressed() override;
	void button2Pressed() override;
	void button3Pressed() override;
	void button4Pressed() override;
	void button5Pressed() override;
	void button6Pressed() override;
	void button7Pressed() override;
	void button8Pressed() override;
	void button9Pressed() override;
};