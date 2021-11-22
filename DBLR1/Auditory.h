#pragma once

#include<iostream>
#include<vector>

using namespace::std;

class Auditory
{
private:

	int id;
	string auditoryName;

public:

	Auditory();
	Auditory(string);
	Auditory(const Auditory&);

	void setId(int);
	void setAuditoryName(string);

	int getId();
	string getAuditoryName();

	friend bool operator==(const Auditory&, const Auditory&);

};

