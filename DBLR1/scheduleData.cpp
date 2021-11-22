#include "scheduleData.h"
#include<iostream>
#include<vector>

using namespace::std;

bool scheduleData::insertSchedule(schedule sch) 
{ 

    if (!isScheduleExist(sch)) {
        this->scheduleVector.push_back(sch);
        return true;
    }

    return false; 
}

bool scheduleData::insertAuditory(string audit) { 
    
    if (!isAuditoryExist(audit)) {
        this->auditoryVector.push_back(*(new Auditory(audit)));
        return true;
    }

    return false;
}

bool scheduleData::insertGroup(string gr) {	
    if (!isAuditoryExist(gr)) {
        this->groupVector.push_back(*(new Group(gr)));
        return true;
    }

    return false;
}

bool scheduleData::isScheduleExist(schedule sc) 
{
    for (schedule sched : scheduleVector)
        if (sched == sc)
            return true;

    return false;
}

bool scheduleData::isAuditoryExist(string audit)
{
    for (Auditory au : auditoryVector)
        if (au.getAuditoryName() == audit)
            return true;

    return false;
}

bool scheduleData::isGroupExist(string gr)
{
    for (Group gr : groupVector)
        if (gr.getGroupName() == gr)
            return true;

    return false;
}

bool scheduleData::removeInSchedule(int index)
{
    scheduleVector.erase(scheduleVector.begin()+index);

    return true;
}

bool scheduleData::removeInGroup(string group)
{

    bool removed = false;

    auto it = groupVector.begin();
    auto it2 = scheduleVector.begin();

    for (int i = 0; i < groupVector.size(); i++) {
        if (groupVector[i].getGroupName() == group) {
            groupVector.erase(it+i);
            removed = true;
        }
    }

    if (removed) {
        for (int i = 0; i < scheduleVector.size(); i++) {
            if (scheduleVector[i].getGroup().getGroupName() == group) {
                scheduleVector.erase(it2 + i);

            }
        }
        return true;
    }

    return false;
}

bool scheduleData::removeInAuditory(string auditory)
{
    bool removed = false;

    auto it = auditoryVector.begin();
    auto it2 = scheduleVector.begin();

    for (int i = 0; i < auditoryVector.size(); i++) {
        if (auditoryVector[i].getAuditoryName() == auditory) {
            auditoryVector.erase(it + i);
            removed = true;
        }
    }

    if (removed) {
        for (int i = 0; i < scheduleVector.size(); i++) {
            if (scheduleVector[i].getAuditory().getAuditoryName() == auditory) {
                scheduleVector.erase(it2 + i);

            }
        }
        return true;
    }

    return false;

}

bool scheduleData::editAllSchedule(int index, schedule sc)
{

    if (removeInSchedule(index)) {
        scheduleVector[index].setID(sc.getID());
        scheduleVector[index].setAuditory(sc.getAuditory());
        scheduleVector[index].setDayOfWeek(sc.getDayOfWeek());
        scheduleVector[index].setGroup(sc.getGroup().getGroupName());
        scheduleVector[index].setTimeStart(sc.getTimeStart());
        scheduleVector[index].setTimeEnd(sc.getTimeEnd());
        scheduleVector[index].setWeekNumber(sc.getWeekNumber());
        return true;
    }
      
    return false;
}

bool scheduleData::editByDayInSchedule(int index, string day)
{
    scheduleVector[index].setDayOfWeek(day);

    return true;
}

bool scheduleData::editByTimeInSchedule(int index, string tStart, string tEnd)
{
    scheduleVector[index].setTimeStart(tStart);
    scheduleVector[index].setTimeEnd(tEnd);

    return true;
}

bool scheduleData::editByGroupInSchedule(int index, string group)
{
    scheduleVector[index].setGroup(group);

    return true;
}

bool scheduleData::editByAuditoryInSchedule(int index, string auditory)
{
    scheduleVector[index].setAuditory(auditory);

    return true;
}

bool scheduleData::editAuditory(string oldA, string newA)
{
    bool changed = false;

    if (auditoryVector.size() == 0) {
        cout << "  Таблица Аудиторий пуста!!" << endl;
        return changed;
    }


    for (int i = 0; i < auditoryVector.size(); i++) {
        if (auditoryVector[i].getAuditoryName() == oldA) {
            changed = true;
            auditoryVector[i].setAuditoryName(newA);
            break;
        }
    }

    return true;
}

bool scheduleData::editGroup(string oldG, string newG)
{
    bool changed = false;

    if (groupVector.size() == 0) {
        cout << "Таблица групп полностью пуста" << endl;
        return changed;
    }

    for (int i = 0; i < groupVector.size(); i++) {
        if (groupVector[i].getGroupName() == oldG) {
            changed = true;
            groupVector[i].setGroupName(newG);
            break;
        }
    }

    return changed;
}

void scheduleData::setScheduleVector(vector<schedule> scVector) { scheduleVector = scVector; }

void scheduleData::setAuditoryVector(vector<Auditory> auVector) { auditoryVector = auVector; }

void scheduleData::setGroupVector(vector<Group> grVector) { groupVector = grVector; }

void scheduleData::showScheduleVector()
{

    for (int i = 0; i < this->scheduleVector.size(); i++)
    {

        cout << endl;

        cout << "  " << i + 1 << "." << endl;
        cout << "    Номер недели: " << this->scheduleVector[i].getWeekNumber() << endl;

        cout << "    День недели: " << this->scheduleVector[i].getDayOfWeek() << endl;

        cout << "    Время начала: " << this->scheduleVector[i].getTimeStart() << endl;

        cout << "    Время окончания: " << this->scheduleVector[i].getTimeEnd() << endl;

        cout << "    Название группы: " << this->scheduleVector[i].getGroup().getGroupName() << endl;

        cout << "    Номер аудитории: " << this->scheduleVector[i].getAuditory().getAuditoryName() << endl;

    }

    if (this->scheduleVector.size()) {
        cout << "\n!- Таблица расписания пуста!\n";
    }

    cout << endl;

}

void scheduleData::showAuditoryVector()
{

    for (int i = 0; i < this->auditoryVector.size(); i++)
    {

        cout << endl;

        cout << "  " << i + 1 << "." << this->auditoryVector[i].getAuditoryName() << endl;

    }

    if (this->auditoryVector.size()) {
        cout << "\n!- Таблица групп пуста!\n";
    }

    cout << endl;

}

void scheduleData::showGroupVector()
{

    for (int i = 0; i < this->groupVector.size(); i++)
    {

        cout << endl;

        cout << "  " << i + 1 << "." << this->groupVector[i].getGroupName() << endl;

    }

    if (this->groupVector.size()) {
        cout << "\n!- Таблица аудиторий пуста!\n";
    }

    cout << endl;

}
