#pragma once

#include<iostream>
#include<vector>
#include"schedule.h"
#include"Auditory.h"
#include"Group.h"
#include"DataMapper.h"


using namespace::std;

class scheduleData
{
private:

	DataMapper dMapper;

	vector<schedule*> scheduleVector;
	vector<Auditory*> auditoryVector;
	vector<Group*> groupVector;

public:

	~scheduleData();

	void fillAllTablesFromDB();

	bool insertSchedule(schedule&);
	bool insertAuditory(Auditory&);
	bool insertAuditoryAndDB(Auditory&);
	bool insertGroup(Group&);
	bool insertGroupAndDB(Group&);
	
	bool isScheduleExist(schedule&);
	bool isAuditoryExist(Auditory&);
	bool isGroupExist(Group&);

	int findIdInAuditVector(Auditory&);
	int findIdInGroupVector(Group&);
	int findIdInScheduleVector(schedule&);
	
	bool removeInSchedule(int&);
	bool removeOneInAuditory(Auditory&);
	bool removeOneInGroup(Group&);
	//bool removeAllInAuditory(Auditory&);
	//bool removeAllInGroup(Group&);

	bool freeSchedule();
	void updateIdVectors(schedule*);

	bool ScheduleVectorCheck(schedule &);

	bool editAllSchedule(int&, schedule&);
	bool editByDayInSchedule(int&, string&);
	bool editByTimeInSchedule(int&, Time&);
	bool editByGroupInSchedule(int&, Group&);
	bool editByAuditoryInSchedule(int&, Auditory&);
	bool editAuditory(int&, Auditory&);
	bool editAuditory(Auditory&, Auditory&);
	bool editGroup(int&, Group&);
	bool editGroup(Group&, Group&);
	
	void find(const string&);
	void find(const int&, const int&);

	void showScheduleVector();
	void showAuditoryVector();
	void showGroupVector();

	void printDBShedule();
	void printDBAuditory();
	void printDBGroup();

	vector<schedule*> getScheduleVector();
	vector<Auditory*> getAuditoryVector();
	vector<Group*> getGroupVector();

};

