#include "Auditory.h"

using namespace::std;

Auditory::Auditory(): id(-1), auditoryName("") {}

Auditory::Auditory(string audit): id(-1), auditoryName(audit) {}

Auditory::Auditory(const Auditory &audit): id(audit.id), auditoryName(audit.auditoryName) {}

void Auditory::setId(int id) { this->id = id; }

void Auditory::setAuditoryName(string auditory) { this->auditoryName = auditory; }

int Auditory::getId() { return this->id; }

string Auditory::getAuditoryName() { return this->auditoryName; }

bool operator==(const Auditory& au1, const Auditory& au2) 
{	
	return (au1.id == au2.id) && (au1.auditoryName == au2.auditoryName); 
}