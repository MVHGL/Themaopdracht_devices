#pragma once

/* Interface base class */
class KeyPadListener {
public:
	virtual void buttonHashTagPressed() = 0;
	virtual void buttonStarPressed() = 0;
	virtual void buttonAPressed() = 0;
	virtual void buttonBPressed() = 0;
	virtual void buttonCPressed() = 0;
	virtual void button1Pressed() = 0;
	virtual void button2Pressed() = 0;
	virtual void button3Pressed() = 0;
	virtual void button4Pressed() = 0;
	virtual void button5Pressed() = 0;
	virtual void button6Pressed() = 0;
	virtual void button7Pressed() = 0;
	virtual void button8Pressed() = 0;
	virtual void button9Pressed() = 0;
};