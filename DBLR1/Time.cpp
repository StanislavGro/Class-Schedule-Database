#include "Time.h"

void Time::setId(int id) { this->id = id; }

void Time::setTimeStart(string timeStart) { this->timeStart = timeStart; }

void Time::setTimeEnd(string timeEnd) { this->timeEnd = timeEnd; }

int Time::getId() { return this->id; }

string Time::getTimeStart() { return timeStart; }

string Time::getTimeEnd() { return timeEnd; }
