#ifndef _TIME_HPP
#define _TIME_HPP
class Time {
private:
	int min;
	int sec;
public:
	Time();
	Time(const int& min, const int& sec);
	Time getTime() const;
	int getSec() const;
	int getMin() const;
	void updateTime();
};
#endif