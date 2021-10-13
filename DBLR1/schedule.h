#pragma once
#include<iostream>

using namespace::std;

class schedule {

private:

	int id;
	int classroomNumber; //����� ���������
	int weekNumber; //����� ������

	string groupName; //�������� ������
	string timePeriod; //��������� ����������
	string dayOfWeek; //���� ������


public:

	schedule();
	schedule(int, int, int, string, string, string);
	schedule(int, int, string, string, string);
	schedule(const schedule &);

	void setID(int);
	void setClassroomNumber(int);
	void setWeekNumber(int);
	void setGroupName(string);
	void setTimePeriod(string);
	void setDayOfWeek(string);

	int getID();
	int getClassroomNumber();
	int getWeekNumber();
	string getGroupName();
	string getTimePeriod();
	string getDayOfWeek();

	bool operator==(const schedule&);
	friend ostream& operator<<(ostream& os, schedule &);
	friend istream& operator>>(istream& is, schedule &);

	void print();

};