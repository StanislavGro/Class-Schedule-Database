#include "Time.h"

Time::Time(): timeStart(""), timeEnd("") {}

Time::Time(string& tStart, string& tEnd): timeStart(tStart), timeEnd(tEnd) {}

Time::Time(const Time& time): timeStart(time.timeStart), timeEnd(time.timeEnd) {}

void Time::setTimeStart(string& timeStart) { this->timeStart = timeStart; }

void Time::setTimeEnd(string& timeEnd) { this->timeEnd = timeEnd; }

string Time::getTimeStart() { return timeStart; }

string Time::getTimeEnd() { return timeEnd; }

bool operator==(const Time& time1, const Time& time2)
{
	return (time1.timeStart == time2.timeStart)
		&& (time1.timeEnd == time2.timeEnd);
}

ostream& operator<<(ostream& os, Time& time)
{
	os << "    Время начала: " << time.timeStart << endl;
	os << "    Время окончания: " << time.timeEnd << endl;

	return os;
}

istream& operator>>(istream& is, Time& time)
{
	is >> time.timeStart;
	is >> time.timeEnd;

	return is;
}