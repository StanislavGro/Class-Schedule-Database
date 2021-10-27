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
	os << "����� ������: "	  << shed.weekNumber	  << endl;
	os << "���� ������: "	  << shed.dayOfWeek		  << endl;
	os << "����� ������: "	  << shed.timeStart	      << endl;
	os << "����� �����: "	  << shed.timeEnd		  << endl;
	os << "�������� ������: " << shed.groupName		  << endl;
	os << "����� ���������: " << shed.classroomNumber << endl;

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
	cout << "����� ������: "	<< this->weekNumber		 <<endl;
	cout << "���� ������: "		<< this->dayOfWeek		 <<endl;
	cout << "����� ������: "	<< this->timeStart		 <<endl;
	cout << "����� �����: "		<< this->timeEnd		 <<endl;
	cout << "�������� ������: " << this->groupName		 <<endl;
	cout << "����� ���������: " << this->classroomNumber <<endl;

	cout << endl;
}

