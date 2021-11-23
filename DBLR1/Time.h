#pragma once

#include<iostream>
#include<vector>

using namespace::std;

class Time
{
private:

	int id;
	string* timeStart;
	string* timeEnd;

public:

	Time();
	Time(string*, string*);
	Time(int, string*, string*);
	Time(const Time&);
	~Time();

	void setId(int);
	void setTimeStart(string*);
	void setTimeEnd(string*);

	int getId();
	string* getTimeStart();
	string* getTimeEnd();

	friend bool operator==(const Time&, const Time&);
	friend ostream& operator<<(ostream& os, Time&);
	friend istream& operator>>(istream& is, Time&);
};