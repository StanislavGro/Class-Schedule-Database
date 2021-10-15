#include "schedule.h"
#include <iostream>

using namespace::std;

schedule::schedule(): 
	id(-1), weekNumber(-1), dayOfWeek(""), timePeriod(""), groupName(""), classroomNumber(-1)  {}

schedule::schedule(int ID, int weekNum, string dayOW, string timePer, string grName, int clNum) :
	id(ID), weekNumber(weekNum), dayOfWeek(dayOW), timePeriod(timePer), groupName(grName), classroomNumber(clNum) {}

schedule::schedule(int weekNum, string dayOW, string timePer, string grName, int clNum) :
	schedule::schedule(-1, weekNum, dayOW, timePer, grName, clNum) {}


schedule::schedule(const schedule& sc) :
	id(sc.id), weekNumber(sc.weekNumber), dayOfWeek(sc.dayOfWeek), timePeriod(sc.timePeriod),   
	groupName(sc.groupName), classroomNumber(sc.classroomNumber) {}

void schedule::setID(int ID) { this->id = ID; }

void schedule::setClassroomNumber(int clNum) { this->classroomNumber = clNum; }

void schedule::setWeekNumber(int weekNum) { this->weekNumber = weekNum; }

void schedule::setGroupName(string grName) { this->groupName = grName; }

void schedule::setTimePeriod(string timePer) { this->timePeriod = timePer; }

void schedule::setDayOfWeek(string dayOW) { this->dayOfWeek = dayOW; }

int schedule::getID() { return this->id; }

int schedule::getClassroomNumber() { return this->classroomNumber; }

int schedule::getWeekNumber() {	return this->weekNumber; }

string schedule::getGroupName() { return this->groupName; }

string schedule::getTimePeriod() { return this->timePeriod; }

string schedule::getDayOfWeek() { return this->dayOfWeek; }

bool schedule::operator==(const schedule& sched)
{
	return this->classroomNumber == sched.classroomNumber && this->weekNumber == sched.weekNumber
		&& this->dayOfWeek == sched.dayOfWeek && this->groupName == sched.groupName && this->timePeriod == sched.timePeriod;
}

ostream& operator<<(ostream& os, schedule& shed)
{
	os << "Номер недели: "	  << shed.weekNumber	  << endl;
	os << "День недели: "	  << shed.dayOfWeek		  << endl;
	os << "Время: "			  << shed.timePeriod	  << endl;
	os << "Название группы: " << shed.groupName		  << endl;
	os << "Номер аудитории: " << shed.classroomNumber << endl;

	os << endl;

	return os;
}

istream& operator>>(istream& is, schedule& shed) 
{

	is >> shed.id;
	is >> shed.weekNumber;
	is >> shed.dayOfWeek;
	is >> shed.timePeriod;
	is >> shed.groupName;
	is >> shed.classroomNumber;

	return is;
}

void schedule::print()
{
	cout << "Номер недели: "	<< this->weekNumber		 <<endl;
	cout << "День недели: "		<< this->dayOfWeek		 <<endl;
	cout << "Время: "			<< this->timePeriod		 <<endl;
	cout << "Название группы: " << this->groupName		 <<endl;
	cout << "Номер аудитории: " << this->classroomNumber <<endl;

	cout << endl;
}

