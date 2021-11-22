#include "Time.h"

Time::Time(): id(-1), timeStart(""), timeEnd("") {}

Time::Time(string tStart, string tEnd): id(-1), timeStart(tStart), timeEnd(tEnd) {}

Time::Time(const Time& time): id(time.id), timeStart(time.timeStart), timeEnd(time.timeEnd) {}

void Time::setId(int id) { this->id = id; }

void Time::setTimeStart(string timeStart) { this->timeStart = timeStart; }

void Time::setTimeEnd(string timeEnd) { this->timeEnd = timeEnd; }

int Time::getId() { return this->id; }

string Time::getTimeStart() { return timeStart; }

string Time::getTimeEnd() { return timeEnd; }

bool operator==(const Time& time1, const Time& time2)
{
	return (time1.id == time2.id)
		&& (time1.timeStart == time2.timeStart)
		&& (time1.timeEnd == time2.timeEnd);
}
