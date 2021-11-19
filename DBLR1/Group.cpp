#include "Group.h"

using namespace::std;

void Group::setId(int id) { this->id = id; }

void Group::setGroup(string group) { this->group = group; }

int Group::getId() { return this->id; }

string Group::getGroup() { return this->group; }