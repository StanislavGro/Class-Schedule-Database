#include "schedule.h"
#include <iostream>

using namespace::std;


schedule::schedule(): 
	id(-1), weekNumber((int)0), dayOfWeek(""), time(NULL), group(NULL), auditory(NULL)  {}


schedule::schedule(int ID, int& weekNum, string& dayOW, Time* time, Group* grName, Auditory* clNum) :
	id(ID), weekNumber(weekNum), dayOfWeek(dayOW), time(time), group(grName), auditory(clNum) {}


schedule::schedule(int& weekNum, string& dayOW, Time* time, Group* grName, Auditory* clNum) :
	schedule::schedule(-1, weekNum, dayOW, time, grName, clNum) {}


schedule::schedule(const schedule& sc) :
	id(sc.id), weekNumber(sc.weekNumber), dayOfWeek(sc.dayOfWeek), time(new Time(*sc.time)), 
	group(new Group(*sc.group)), auditory(new Auditory(*sc.auditory)) {}


void schedule::setID(int ID) { this->id = ID; }


void schedule::setAuditory(Auditory* clNum) { this->auditory = clNum; }


void schedule::setWeekNumber(int& weekNum) { this->weekNumber = weekNum; }


void schedule::setGroup(Group* grName) { this->group = grName; }


void schedule::setTime(Time* time) { this->time = time; }


void schedule::setDayOfWeek(string& dayOW) { this->dayOfWeek = dayOW; }


int schedule::getID() { return this->id; }


Auditory* schedule::getAuditory() { return this->auditory; }


int schedule::getWeekNumber() { return this->weekNumber; }


Group* schedule::getGroup() { return this->group; }


Time* schedule::getTime() { return this->time; }


string schedule::getDayOfWeek() { return this->dayOfWeek; }


bool operator==(const schedule& sched1, const schedule& sched2)
{
	return *(sched1.auditory) == *(sched2.auditory) && sched1.weekNumber == sched2.weekNumber
		&& sched1.dayOfWeek == sched2.dayOfWeek && *(sched1.group) == *(sched2.group)
		&& *(sched1.time) == *(sched2.time);
}


ostream& operator<<(ostream& os, schedule& shed)
{
	os << "   Номер недели: "	<< shed.weekNumber	<< endl;
	os << "   День недели: "	<< shed.dayOfWeek	<< endl;
	os << *(shed.time);
	os << *(shed.group);
	os << *(shed.auditory);

	os << endl;

	return os;
}


istream& operator>>(istream& is, schedule& sched) 
{
	string timeStart;
	string timeEnd;
	string auditory;
	string group;

	//is >> shed.id;
	is >> sched.weekNumber;
	is >> sched.dayOfWeek;
	is >> timeStart;
	is >> timeEnd;
	is >> group;
	is >> auditory;



	sched.setTime(new Time(timeStart, timeEnd));
	sched.setGroup(new Group(group));
	sched.setAuditory(new Auditory(auditory));

	return is;
}


void schedule::print()
{
	cout << this->id << "." << endl;

	cout << "Номер недели: "	<< this->weekNumber		<<endl;
	cout << "День недели: "		<< this->dayOfWeek		<<endl;
	cout << *(this->time)		<<endl;
	cout << *(this->group)		<<endl;
	cout << *(this->auditory)	<<endl;

	cout << endl;
}