#pragma once

#include<iostream>
#include<vector>
#include"schedule.h"
#include"Auditory.h"
#include"Group.h"
#include"Time.h"

class scheduleData
{
private:

	vector<schedule> scheduleVector;
	vector<Auditory> auditoryVector;
	vector<Group> groupVector;

public:

	~scheduleData();

	bool insertSchedule(schedule*);
	bool insertAuditory(Auditory*);
	bool insertGroup(Group*);
	
	bool isScheduleExist(schedule*);
	bool isAuditoryExist(Auditory*);
	bool isGroupExist(Group*);

	bool removeInSchedule(int);
	bool removeOneInAuditory(Auditory*);
	bool removeOneInGroup(Group*);
	bool removeAllInGroup(Group*);
	bool removeAllInAuditory(Auditory*);

	bool editAllSchedule(int, schedule*);
	bool editByDayInSchedule(int, string*);
	bool editByTimeInSchedule(int, Time*);
	bool editByGroupInSchedule(int, Group*);
	bool editByAuditoryInSchedule(int, Auditory*);
	bool editAuditory(Auditory*, Auditory*);
	bool editGroup(Group*, Group*);

	void find(string*);
	void find(int*, int*);

	void showScheduleVector();
	void showAuditoryVector();
	void showGroupVector();

	vector<schedule> getScheduleVector();
	vector<Auditory> getAuditoryVector();
	vector<Group> getGroupVector();

};

