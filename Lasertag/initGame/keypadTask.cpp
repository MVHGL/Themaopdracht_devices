#include "keypadTask.hpp"

keypadTask::keypadTask(initGame & initGameTask):
	Task("KeypadTask"),
	initGameTask(initGameTask)
	{}


void keypadTask::main(){
	while(1){
		switch(state){
			case IDLE:
				if keypad.getc(){
					state = BUTTON_PRESSED;
					break;
				}
			case BUTTON_PRESSED:
				initGameTask.buttonPressed();
				state = IDLE;
				break;
		}
	}
}