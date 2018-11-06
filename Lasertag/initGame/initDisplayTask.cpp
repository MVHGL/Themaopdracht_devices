#include "initDisplayTask.hpp"

initDisplayTask::initDisplayTask(hwlib::window_ostream & oled_display):
	task("displayTask"),
	timeFlag(this, "timeFlag"),
	timePool("timePool"),
	commandFlag(this, "commandFlag"),
	commandPool("commandPool"),
	stateFlag(this, "stateFlag"),
	statePool("statePool"),
	oled_display(oled_display)
	{}

void initDisplayTask::main(){
	oled_display << '\f' << hwlib::flush;
	while(true){
		switch(state_display){
			case IDLE:
			{
				auto event = wait(timeFlag + commandFlag + stateFlag);
				if(event == timeFlag){
					time = timePool.read();
					state_display = DISPLAY;
					break;
				}
				if(event == commandFlag){
					c = commandPool.read();
				}
				if(event == stateFlag){
					state = statePool.read();
				}
				state_display = DISPLAY;
				break;
			}

			case DISPLAY:
			{
				if(state == 1){
					oled_display 
					<<"\f" << "\t0000" << "time set: " << time
					<< "\t0002" << "command: "<< c 
					<< "\t0003" << "setting time..."
					<< "\t0005" << "press C" <<
					hwlib::flush;
					state_display = IDLE;
					break;
				}
				if(state == 2){
					oled_display 
					<<"\f" << "\t0000" << "time set: " << time
					<< "\t0002" << "command: "<< c 
					<< "\t0003" << "send the time "
					<< "\t0004" << "to player."
					<< "\t0005" << "press #" <<
					hwlib::flush;
					state_display = IDLE;
					break;
				if(state == 3){
					oled_display 
					<<"\f" << "\t0000" << "time set: " << time
					<< "\t0002" << "command: "<< c 
					<< "\t0003" << "start the game "
					<< "\t0005" << "press *" <<
					hwlib::flush;
					state_display = IDLE;
					break;					
				}
				if(state == 9){
					oled_display <<"\f" <<"invalid keypress!"
					<< hwlib::flush;
				}
					
				}
			}
		}
	}
};

void initDisplayTask::showTime(const int & t){
	timePool.write(t);
	timeFlag.set();
};

void initDisplayTask::showCommand(const char & c){
	commandPool.write(c);
	commandFlag.set();
};

void initDisplayTask::showState(const int & s){
	statePool.write(s);
	stateFlag.set();
}