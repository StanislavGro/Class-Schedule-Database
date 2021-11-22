#pragma once

#include <iostream>
#include <vector>

using namespace::std;

class Group
{
private:

	int id;
	string groupName;

public:

	Group();
	Group(string);
	Group(const Group&);

	void setId(int);
	void setGroupName(string);

	int getId();
	string getGroupName();

	friend bool operator==(const Group&, const Group&);

};

