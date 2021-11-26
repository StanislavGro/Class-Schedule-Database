#include "Auditory.h"

using namespace::std;

Auditory::Auditory(): id(-1), auditoryName(NULL) {}

Auditory::Auditory(int ID, string* audit) : id(ID), auditoryName(new string(*audit)) {}

Auditory::Auditory(string* audit): id(-1), auditoryName(new string(*audit)) {}

Auditory::Auditory(const Auditory &audit): id(audit.id), auditoryName(new string(*(audit.auditoryName))) {}

void Auditory::setId(int id) { this->id = id; }

void Auditory::setAuditoryName(string* auditory) { this->auditoryName = auditory; }

int Auditory::getId() { return this->id; }

string* Auditory::getAuditoryName() { return this->auditoryName; }

bool operator==(const Auditory& au1, const Auditory& au2) 
{	
	return (*(au1.auditoryName) == *(au2.auditoryName)); 
}

ostream& operator<<(ostream& os, Auditory& auditory)
{
	os << "   Номер аудитории: " << *(auditory.auditoryName) << endl;

	return os;
}

istream& operator>>(istream& is, Auditory& auditory)
{

	is >> *(auditory.auditoryName);

	return is;
}

Auditory::~Auditory() {}
