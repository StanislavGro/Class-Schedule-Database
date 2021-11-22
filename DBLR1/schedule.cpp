#include "schedule.h"
#include <iostream>

using namespace::std;


schedule::schedule(): 
	id(-1), weekNumber(-1), dayOfWeek(""), timeStart(""), timeEnd(""), group(""), auditory()  {}


schedule::schedule(int ID, int weekNum, string dayOW, string timeStart, string timeEnd, string grName, string clNum) :
	id(ID), weekNumber(weekNum), dayOfWeek(dayOW), timeStart(""), timeEnd(""), group(grName), auditory(clNum) {}


schedule::schedule(int weekNum, string dayOW, string timeStart, string timeEnd, string grName, string clNum) :
	schedule::schedule(-1, weekNum, dayOW, timeStart, timeEnd, grName, clNum) {}


schedule::schedule(const schedule& sc) :
	id(sc.id), weekNumber(sc.weekNumber), dayOfWeek(sc.dayOfWeek), timeStart(sc.timeStart), timeEnd(sc.timeEnd),
	group(sc.group), auditory(sc.auditory) {}


void schedule::setID(int ID) { this->id = ID; }


void schedule::setAuditory(Auditory clNum) { this->auditory = clNum; }


void schedule::setWeekNumber(int weekNum) { this->weekNumber = weekNum; }


void schedule::setGroup(string grName) { this->group = grName; }


void schedule::setTimeStart(string timePStart) { this->timeStart = timeStart; }


void schedule::setTimeEnd(string timeEnd) { this->timeStart = timeEnd; }


void schedule::setDayOfWeek(string dayOW) { this->dayOfWeek = dayOW; }


int schedule::getID() { return this->id; }


Auditory schedule::getAuditory() { return this->auditory; }


int schedule::getWeekNumber() {	return this->weekNumber; }


Group schedule::getGroup() { return this->group; }


string schedule::getTimeStart() { return this->timeStart; }


string schedule::getTimeEnd() { return this->timeEnd; }


string schedule::getDayOfWeek() { return this->dayOfWeek; }


bool schedule::operator==(const schedule& sched)
{
	return this->auditory == sched.auditory && this->weekNumber == sched.weekNumber
		&& this->dayOfWeek == sched.dayOfWeek && this->group == sched.group
		&& this->timeStart == sched.timeStart && this->timeEnd == sched.timeEnd;
}


ostream& operator<<(ostream& os, schedule& shed)
{
	os << "   ����� ������: "	   << shed.weekNumber			   << endl;
	os << "   ���� ������: "	   << shed.dayOfWeek			   << endl;
	os << "   ����� ������: "	   << shed.timeStart			   << endl;
	os << "   ����� �����: "	   << shed.timeEnd				   << endl;
	os << "   �������� ������: "   << shed.group.getGroupName()		  << endl;
	os << "   ����� ���������: "   << shed.auditory.getAuditoryName() << endl;

	os << endl;

	return os;
}


istream& operator>>(istream& is, schedule& shed) 
{

	string auditory;
	string group;

	//is >> shed.id;
	is >> shed.weekNumber;
	is >> shed.dayOfWeek;
	is >> shed.timeStart;
	is >> shed.timeEnd;
	is >> group;
	is >> auditory;

	shed.group.setGroupName(group);
	shed.auditory.setAuditoryName(auditory);

	return is;
}


void schedule::print()
{
	cout << this->id << "." << endl;

	cout << "����� ������: "	<< this->weekNumber					 <<endl;
	cout << "���� ������: "		<< this->dayOfWeek					 <<endl;
	cout << "����� ������: "	<< this->timeStart					 <<endl;
	cout << "����� �����: "		<< this->timeEnd					 <<endl;
	cout << "�������� ������: " << this->group.getGroupName()		 <<endl;
	cout << "����� ���������: " << this->auditory.getAuditoryName()	 <<endl;

	cout << endl;
}