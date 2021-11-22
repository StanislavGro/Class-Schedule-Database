#pragma once
#include<iostream>
#include"Auditory.h"
#include"Group.h"
#include"Time.h"

using namespace::std;

class schedule {

private:

	int id;
	int weekNumber;			//номер недели
	string dayOfWeek;		//день недели
	string timeStart;		//время начала
	string timeEnd;			//время конца
	Group group;			//название группы
	Auditory auditory;		//номер аудитории


public:

	schedule();
	schedule(int, int, string, string, string, string, string);
	schedule(int, string, string, string, string, string);
	schedule(const schedule &);

	void setID(int);
	void setWeekNumber(int);
	void setDayOfWeek(string);
	void setTimeStart(string);
	void setTimeEnd(string);
	void setGroup(string);
	void setAuditory(Auditory );

	int getID();
	int getWeekNumber();
	string getDayOfWeek();
	string getTimeStart();
	string getTimeEnd();
	Group getGroup();
	Auditory getAuditory();

	bool operator==(const schedule&);
	friend ostream& operator<<(ostream& os, schedule &);
	friend istream& operator>>(istream& is, schedule &);

	void print();

};