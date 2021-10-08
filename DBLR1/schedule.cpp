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
	os << "����� ���������: " << shed.classroomNumber << endl;
	os << "����� ������: "	  << shed.weekNumber	  << endl;
	os << "���� ������: "	  << shed.dayOfWeek		  << endl;
	os << "�������� ������: " << shed.groupName		  << endl;
	os << "�����: "			  << shed.timePeriod	  << endl;

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
	cout << "����� ���������: " << this->classroomNumber <<endl;
	cout << "����� ������: "	<< this->weekNumber		 <<endl;
	cout << "���� ������: "		<< this->dayOfWeek		 <<endl;
	cout << "�������� ������: " << this->groupName		 <<endl;
	cout << "�����: "			<< this->timePeriod		 <<endl;

	cout << endl;
}

