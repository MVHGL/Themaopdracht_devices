#include "displayTask.hpp"

displayTask::displayTask(hwlib::window_ostream & oled_display)
	displayF
	oled_display(oled_display),
	Task("display task")
	{}

displayTask::main(){
	while(true){
		switch(state_display){
			case IDLE:
				wait(displayChannel);
				state_display = DISPLAY;
				break;

			case DISPLAY:
				char a = displayChannel.read();
				show(a);
				state_display = IDLE;
				break;
		}
	}
}

displayTask::show(char c){
	display << "\f" << "\t0502" << c << hwlib::flush;
}

displayTask::showState(const int state){
	
}

displayTask::setState(const in state){
	
}