#pragma once
#include<iostream>
#include"Auditory.h"
#include"Group.h"
#include"Time.h"

using namespace::std;

class schedule {

private:

	int	id;				//����� ������
	int	*weekNumber;	//����� ������
	string *dayOfWeek;	//���� ������
	Time *time;			//����� ������ � ���������
	Group *group;		//�������� ������
	Auditory *auditory;	//����� ���������


public:

	schedule();
	schedule(int, int*, string*, Time*, Group*, Auditory*);
	schedule(int*, string*, Time*, Group*, Auditory*);
	schedule(const schedule &);
	~schedule();

	void setID(int);
	void setWeekNumber(int*);
	void setDayOfWeek(string*);
	void setTime(Time*);
	void setGroup(Group*);
	void setAuditory(Auditory*);

	int getID();
	int* getWeekNumber();
	string* getDayOfWeek();
	Time* getTime();
	Group* getGroup();
	Auditory* getAuditory();

	friend bool operator==(const schedule&, const schedule&);
	friend ostream& operator<<(ostream& os, schedule &);
	friend istream& operator>>(istream& is, schedule &);

	void print();

};