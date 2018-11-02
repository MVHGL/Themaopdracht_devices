#include "keypadTask.hpp"

keypadTask::keypadTask(initGame & initGameTask):
	task("KeypadTask"),
	initGameTask(initGameTask)
	{}


void keypadTask::main(){
	while(1){
		switch(state){
			case IDLE:
			{
				if (keypad.getc()){
					hwlib::cout << "button pressed.\n";
					state = BUTTON_PRESSED;
					break;
				}
			}
			case BUTTON_PRESSED:
			{
				initGameTask.buttonPressed(keypad.getc());
				state = IDLE;
				break;
			}
		}
	}
};