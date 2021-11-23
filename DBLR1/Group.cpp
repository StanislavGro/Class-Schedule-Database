#include "Group.h"

using namespace::std;

Group::Group(): id(-1), groupName(NULL) {}

Group::Group(int ID, string* gr) : id(ID), groupName(new string(*gr)) {}

Group::Group(string* gr): id(-1), groupName(new string(*gr)) {}

Group::Group(const Group& gr): id(gr.id), groupName(new string(*(gr.groupName))){}

Group::~Group()
{
	groupName->clear();
}

void Group::setId(int id) { this->id = id; }

void Group::setGroupName(string* group) { this->groupName = group; }

int Group::getId() { return this->id; }

string* Group::getGroupName() { return this->groupName; }

bool operator==(const Group& gr1, const Group& gr2)
{
	return (*gr1.groupName == *gr2.groupName);
}

ostream& operator<<(ostream& os, Group& group)
{
	os << "   Название группы: " << *(group.groupName) << endl;
	return os;
}

istream& operator>>(istream& is, Group& group)
{
	is >> *(group.groupName);

	return is;
}
