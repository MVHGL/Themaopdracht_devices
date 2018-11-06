/// @file time.hpp
#ifndef _TIME_HPP
#define _TIME_HPP
/// \brief
/// Time class
/// \details
/// This Time class can hold two integers. Minutes and seconds.
class Time {
private:
	int min;
	int sec;
public:
	/// \brief
	/// Default constructor.
	Time();
	/// \brief
	/// Constructor with two params.
	/// \details
	/// Time constructor which requires x number of minutes and y number of seconds.
	Time(const int& min, const int& sec);
	/// \brief
	/// Get Time object.
	/// \details
	/// Returns (const) the current Time left. 
	Time getTime() const;
	/// \brief
	/// Get seconds.
	/// \details
	/// Returns the current seconds left.
	int getSec() const;
	/// \brief
	/// Gets minutes.
	/// \details
	/// Gets (const) the current minutes left. 
	int getMin() const;
	/// \brief
	/// Updates the time.
	/// \details
	/// update the time. Each time this function is called, seconds will be reduced with one. Keep in mind that a timer or clock (lasting 1 second) will be necessairy, before updating the time again. 
	void updateTime();
};
#endif