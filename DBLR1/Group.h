#pragma once

#include <iostream>
#include <vector>

using namespace::std;

class Group
{
private:

	int id;
	string group;

public:

	void setId(int);
	void setGroup(string);

	int getId();
	string getGroup();

};

