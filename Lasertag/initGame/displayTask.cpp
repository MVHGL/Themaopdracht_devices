#include "displayTask.hpp"

displayTask::displayTask(hwlib::window_ostream & oled_display):
	task("displayTask"),
	stateFlag(this, "stateFlag"),
	statePool("statePool"),
	displayChannel(this, "displayChannel"),
	oled_display(oled_display)
	{}

void displayTask::main(){
	while(true){
		switch(state_display){
			case IDLE:
			{
				wait(displayChannel);
				state_display = DISPLAY;
				break;
			}

			case DISPLAY:
			{
				char a = displayChannel.read();
				show(a);
				state_display = IDLE;
				break;
			}
		}
	}
};

void displayTask::show(char c){
	oled_display << "\f" << "\t0502" << c << hwlib::flush;
};

void displayTask::showState(const int state){
	
};

void displayTask::setState(const int state){
	
};