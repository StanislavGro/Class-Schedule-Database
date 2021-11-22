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

	bool insertSchedule(schedule);
	bool insertAuditory(string);
	bool insertGroup(string);

	bool isScheduleExist(schedule);
	bool isAuditoryExist(string);
	bool isGroupExist(string);

	bool removeInSchedule(int);
	bool removeInGroup(string);
	bool removeInAuditory(string);

	bool editAllSchedule(int, schedule);
	bool editByDayInSchedule(int, string);
	bool editByTimeInSchedule(int, string, string);
	bool editByGroupInSchedule(int, string);
	bool editByAuditoryInSchedule(int, string);
	bool editAuditory(string, string);
	bool editGroup(string, string);

	void find(string);
	void find(int, int);

	void setScheduleVector(vector<schedule>);
	void setAuditoryVector(vector<Auditory>);
	void setGroupVector(vector<Group>);

	void showScheduleVector();
	void showAuditoryVector();
	void showGroupVector();

};

