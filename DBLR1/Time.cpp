#include "Time.h"

Time::Time(): id(-1), timeStart(NULL), timeEnd(NULL) {}

Time::Time(string* tStart, string* tEnd): id(-1), timeStart(new string(*tStart)), timeEnd(new string(*tEnd)) {}

Time::Time(int ID, string* tStart, string* tEnd): id(ID), timeStart(new string(*tStart)), timeEnd(new string(*tEnd)) {}

Time::Time(const Time& time): id(time.id), timeStart(new string(*(time.timeStart))), timeEnd(new string(*(time.timeEnd))) {}

void Time::setId(int id) { this->id = id; }

void Time::setTimeStart(string* timeStart) { this->timeStart = timeStart; }

void Time::setTimeEnd(string* timeEnd) { this->timeEnd = timeEnd; }

int Time::getId() { return this->id; }

string* Time::getTimeStart() { return timeStart; }

string* Time::getTimeEnd() { return timeEnd; }

bool operator==(const Time& time1, const Time& time2)
{
	return (time1.id == time2.id)
		&& (time1.timeStart == time2.timeStart)
		&& (time1.timeEnd == time2.timeEnd);
}

ostream& operator<<(ostream& os, Time& time)
{
	os << "   Время начала: " << *(time.timeStart) << endl;
	os << "   Время окончания: " << *(time.timeEnd) << endl;

	return os;
}

istream& operator>>(istream& is, Time& time)
{
	is >> *(time.timeStart);
	is >> *(time.timeEnd);

	return is;
}

Time::~Time()
{
}