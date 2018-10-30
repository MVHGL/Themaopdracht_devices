#pragma once
class Time {
private:
	int sec;
	int min;
public:
	Time();
	Time(const int& sec, const int& min);
	Time getTime() const;
	int getSec() const;
	int getMin() const;
	void updateTime();
};