class registerGameControl : public rtos::task<> {
private:
	rtos::timer registerTimer;
	rtos::channel<char, 10> keypadChannel;
	enum state_t {IDLE, GET_PLAYER_ID, GET_WEAPON};
public:
//	void buttonPressed(char button) override; // override a button (from the keypad)

	void write(button b);
	void main();
};
