#include "displayTask.hpp"

displayTask::displayTask(hwlib::istream & oled_display){
	oled_display(oled_display),
	Task("display task")
}

displayTask::main(){
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

displayTask::show(char c){
	display << "\f" << "\t0502" << c << hwlib::flush;
}

displayTask::showState(const int state){
	
}

displayTask::setState(const in state){
	
}