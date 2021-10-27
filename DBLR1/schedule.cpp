#include "schedule.h"
#include <iostream>

using namespace::std;

schedule::schedule(): 
	id(-1), weekNumber(-1), dayOfWeek(""), timeStart(""), timeEnd(""), groupName(""), classroomNumber("")  {}

schedule::schedule(int ID, int weekNum, string dayOW, string timeStart, string timeEnd, string grName, string clNum) :
	id(ID), weekNumber(weekNum), dayOfWeek(dayOW), timeStart(""), timeEnd(""), groupName(grName), classroomNumber(clNum) {}

schedule::schedule(int weekNum, string dayOW, string timeStart, string timeEnd, string grName, string clNum) :
	schedule::schedule(-1, weekNum, dayOW, timeStart, timeEnd, grName, clNum) {}


schedule::schedule(const schedule& sc) :
	id(sc.id), weekNumber(sc.weekNumber), dayOfWeek(sc.dayOfWeek), timeStart(sc.timeStart), timeEnd(sc.timeEnd),
	groupName(sc.groupName), classroomNumber(sc.classroomNumber) {}

void schedule::setID(int ID) { this->id = ID; }

void schedule::setClassroomNumber(int clNum) { this->classroomNumber = clNum; }

void schedule::setWeekNumber(int weekNum) { this->weekNumber = weekNum; }

void schedule::setGroupName(string grName) { this->groupName = grName; }

void schedule::setTimeStart(string timePStart) { this->timeStart = timeStart; }

void schedule::setTimeEnd(string timeEnd) { this->timeStart = timeEnd; }

void schedule::setDayOfWeek(string dayOW) { this->dayOfWeek = dayOW; }

int schedule::getID() { return this->id; }

string schedule::getClassroomNumber() { return this->classroomNumber; }

int schedule::getWeekNumber() {	return this->weekNumber; }

string schedule::getGroupName() { return this->groupName; }

string schedule::getTimeStart() { return this->timeStart; }

string schedule::getTimeEnd() { return this->timeEnd; }

string schedule::getDayOfWeek() { return this->dayOfWeek; }

bool schedule::operator==(const schedule& sched)
{
	return this->classroomNumber == sched.classroomNumber && this->weekNumber == sched.weekNumber
		&& this->dayOfWeek == sched.dayOfWeek && this->groupName == sched.groupName 
		&& this->timeStart == sched.timeStart && this->timeEnd == sched.timeEnd;
}

ostream& operator<<(ostream& os, schedule& shed)
{
	os << "Номер недели: "	  << shed.weekNumber	  << endl;
	os << "День недели: "	  << shed.dayOfWeek		  << endl;
	os << "Время начала: "	  << shed.timeStart	      << endl;
	os << "Время конца: "	  << shed.timeEnd		  << endl;
	os << "Название группы: " << shed.groupName		  << endl;
	os << "Номер аудитории: " << shed.classroomNumber << endl;

	os << endl;

	return os;
}

istream& operator>>(istream& is, schedule& shed) 
{

	//is >> shed.id;
	is >> shed.weekNumber;
	is >> shed.dayOfWeek;
	is >> shed.timeStart;
	is >> shed.timeEnd;
	is >> shed.groupName;
	is >> shed.classroomNumber;

	return is;
}

void schedule::print()
{
	cout << this->id << "." << endl;
	cout << "Номер недели: "	<< this->weekNumber		 <<endl;
	cout << "День недели: "		<< this->dayOfWeek		 <<endl;
	cout << "Время начала: "	<< this->timeStart		 <<endl;
	cout << "Время конца: "		<< this->timeEnd		 <<endl;
	cout << "Название группы: " << this->groupName		 <<endl;
	cout << "Номер аудитории: " << this->classroomNumber <<endl;

	cout << endl;
}

