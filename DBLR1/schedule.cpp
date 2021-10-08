#include "schedule.h"
#include <iostream>

using namespace::std;

schedule::schedule(int ID, int clNum, int weekNum, string grName, string timePer, string dayOW) :
	id(ID), classroomNumber(clNum), weekNumber(weekNum), groupName(grName), timePeriod(timePer), dayOfWeek(dayOW) {}

schedule::schedule(const schedule& sc) :
	id(sc.id), classroomNumber(sc.classroomNumber), weekNumber(sc.weekNumber), 
	groupName(sc.groupName), timePeriod(sc.timePeriod), dayOfWeek(sc.dayOfWeek) {}

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
	os << "Номер аудитории: " << shed.classroomNumber << endl;
	os << "Номер недели: "	  << shed.weekNumber	  << endl;
	os << "День недели: "	  << shed.dayOfWeek		  << endl;
	os << "Название группы: " << shed.groupName		  << endl;
	os << "Время: "			  << shed.timePeriod	  << endl;

	os << endl;

	return os;
}

istream& operator>>(istream& is, schedule& shed) 
{

	is >> shed.id;
	is >> shed.classroomNumber;
	is >> shed.weekNumber;
	is >> shed.groupName;
	is >> shed.timePeriod;
	is >> shed.dayOfWeek;

	return is;
}

void schedule::print()
{
	cout << "Номер аудитории: " << this->classroomNumber <<endl;
	cout << "Номер недели: "	<< this->weekNumber		 <<endl;
	cout << "День недели: "		<< this->dayOfWeek		 <<endl;
	cout << "Название группы: " << this->groupName		 <<endl;
	cout << "Время: "			<< this->timePeriod		 <<endl;

	cout << endl;
}

