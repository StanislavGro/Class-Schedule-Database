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

	void setId(int);
	void setTimeStart(string);
	void setTimeEnd(string);

	int getId();
	string getTimeStart();
	string getTimeEnd();

};