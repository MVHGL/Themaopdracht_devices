#include "time.hpp"

Time::Time(const int& min, const int& sec) :
	min(min), sec(sec)
	{
		if (sec > 60) this->sec = 59;
		if (min > 60) this->min = 59;
		if (min < 0) this->min = 0;
		if (sec < 0) this->sec = 0;
	}
	
Time::Time():
	min(0), sec(0) {}

int Time::getMin() const { return min; }

int Time::getSec() const { return sec; }
		
Time Time::getTime() const { return *this; }

void Time::updateTime() { 
	if (sec == 0 && min > 0) {
		min--;
		sec = 59;
	}
	else if (sec > 0) {
		sec--;
	}
}
