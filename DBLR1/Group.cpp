#include "Group.h"

using namespace::std;

Group::Group(): id(-1), groupName("") {}

Group::Group(string gr): id(-1), groupName(gr) {}

Group::Group(const Group& gr): id(gr.id), groupName(gr.groupName){}

void Group::setId(int id) { this->id = id; }

void Group::setGroupName(string group) { this->groupName = group; }

int Group::getId() { return this->id; }

string Group::getGroupName() { return this->groupName; }

bool operator==(const Group& gr1, const Group& gr2)
{
	return (gr1.id == gr1.id) && (gr1.groupName == gr2.groupName);
}