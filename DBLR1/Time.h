#pragma once

#include<iostream>
#include<vector>

using namespace::std;

class Time
{
private:

	int id;
	string timeStart;
	string timeEnd;

public:

	Time();
	Time(string, string);
	Time(const Time&);

	void setId(int);
	void setTimeStart(string);
	void setTimeEnd(string);

	int getId();
	string getTimeStart();
	string getTimeEnd();

	friend bool operator==(const Time&, const Time&);
};