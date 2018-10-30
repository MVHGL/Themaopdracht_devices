#include "time.hpp"

Time::Time(const int& sec, const int& min) :
	sec(sec), min(min)
	{
		if (sec > 60) this->sec = 60;
		if (min > 60) this->min = 60;
		if (min < 0) this->min = 0;
		if (sec < 0) this->sec = 0;
	}

int Time::getMin() const { return min; }

int Time::getSec() const { return sec; }
		
Time Time::getTime() const { return *this; }

void Time::updateTime() { 
	if (sec == 0 && min > 0) {
		min--;
		sec = 60;
	}
	else if (sec > 0) {
		sec--;
	}
}
