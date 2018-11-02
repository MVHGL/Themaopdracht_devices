#include "keypadTask.hpp"

keypadTask::keypadTask(initGame & initGameTask):
	Task("KeypadTask"),
	out0(out0),
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