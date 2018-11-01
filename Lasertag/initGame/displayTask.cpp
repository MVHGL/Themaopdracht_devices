#include "displayTask.hpp"

displayTask::displayTask(){

}

displayTask::main(){
	enum state_t = {IDLE, DISPLAY };
	state state_t;
	switch(state){
		case IDLE:
			wait(displayChannel);
			state = DISPLAY;
		
		case DISPLAY:
			char a = displayChannel.read();
			show(a);
	}
	 
}

displayTask::show(char c){
	display << "\f" << "\t0502" << c << hwlib::flush;
}

displayTask::showState(const int state){
	
}

displayTask::setState(const in state){
	
}