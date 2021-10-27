#pragma once
#include<iostream>

using namespace::std;

class schedule {

private:

	int id;
	int weekNumber; //����� ������
	string dayOfWeek; //���� ������
	string timeStart; //����� ������
	string timeEnd; //����� �����
	string groupName; //�������� ������
	string classroomNumber; //����� ���������


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
	void setGroupName(string);
	void setClassroomNumber(int);

	int getID();
	int getWeekNumber();
	string getDayOfWeek();
	string getTimeStart();
	string getTimeEnd();
	string getGroupName();
	string getClassroomNumber();

	bool operator==(const schedule&);
	friend ostream& operator<<(ostream& os, schedule &);
	friend istream& operator>>(istream& is, schedule &);

	void print();

};