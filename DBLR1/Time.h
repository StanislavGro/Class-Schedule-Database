#pragma once

#include<iostream>
#include<vector>

using namespace::std;

class Time
{
private:

	string timeStart;
	string timeEnd;

public:

	Time();
	Time(string&, string&);
	Time(const Time&);

	void setTimeStart(string&);
	void setTimeEnd(string&);

	string getTimeStart();
	string getTimeEnd();

	friend bool operator==(const Time&, const Time&);
	friend ostream& operator<<(ostream& os, Time&);
	friend istream& operator>>(istream& is, Time&);
};