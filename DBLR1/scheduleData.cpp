#include "scheduleData.h"
#include<iostream>
#include<vector>
#include <sstream>

using namespace::std;

bool scheduleData::insertSchedule(schedule* sch) 
{ 

    if (!isScheduleExist(sch)) {
        this->scheduleVector.push_back(*(new schedule(*sch)));
        return insertAuditory(sch->getAuditory()) && insertGroup(sch->getGroup());
    }

    return false; 
}


bool scheduleData::isScheduleExist(schedule* sch) 
{
    for(int i = 0; i < scheduleVector.size(); i++)
        if (scheduleVector[i] == *sch)
            return true;

    /*for (schedule sched : scheduleVector)
        if (sched == *sch)
            return true;*/

    return false;
}


bool scheduleData::insertAuditory(Auditory* auditory) {

    if (!isAuditoryExist(auditory)) {
        this->auditoryVector.push_back(*(new Auditory(*auditory)));
        return true;
    }

    return false;

}


bool scheduleData::isAuditoryExist(Auditory* auditory)
{
    for (int i = 0; i < auditoryVector.size(); i++)
        if (auditoryVector[i] == *auditory)
            return true;

    /*for (Auditory au : auditoryVector)
        if (au == *auditory)
            return true;*/

    return false;
}


bool scheduleData::insertGroup(Group* group) {	
    
    if (!isGroupExist(group)) {
        this->groupVector.push_back(*(new Group(*group)));
        return true;
    }

    return false;
}


bool scheduleData::isGroupExist(Group* group)
{

    for (int i = 0; i < groupVector.size(); i++)
        if (groupVector[i] == *group)
            return true;

    /*for (Group gr : groupVector)
        if (gr == *group)
            return true;*/

    return false;
}


bool scheduleData::removeInSchedule(int index)
{

    auto scheduleIt = scheduleVector.begin();

    for (int i = 0; i < scheduleVector.size(); i++, scheduleIt++) {
        if (scheduleVector[i].getID() == index) {
            scheduleVector.erase(scheduleIt);
            break;
        }
    }


    return true;
}


bool scheduleData::removeAllInGroup(Group* group)
{

    bool removed = false;
    auto itSchedule = scheduleVector.begin();
    auto itGroup = groupVector.begin();

    /*auto it = std::find(groupVector.begin(), groupVector.end(), group->getGroupName());
    if (it != groupVector.end())
        groupVector.erase(it);*/

    for (int i = 0; i < groupVector.size(); i++, itGroup++)
        if (groupVector[i] == *group) {
            groupVector.erase(itGroup);
            removed = true;
            break;
        }

    if (removed) {
        for (int i = 0; i < scheduleVector.size(); i++) {
            if (*(scheduleVector[i].getGroup()) == *group) {
                scheduleVector.erase(itSchedule + i);
                itSchedule = scheduleVector.begin();
                i--;
            }
        }
        return true;
    }

    return false;

}


bool scheduleData::removeAllInAuditory(Auditory* auditory)
{
    bool removed = false;

    auto itAuditory = auditoryVector.begin();
    auto itSchedule = scheduleVector.begin();

    for (int i = 0; i < auditoryVector.size(); i++, itAuditory++)
        if (auditoryVector[i] == *auditory) {
            auditoryVector.erase(itAuditory);
            removed = true;
            break;
        }

    if (removed) {
        for (int i = 0; i < scheduleVector.size(); i++)
            if (*(scheduleVector[i].getAuditory()) == *auditory) {
                scheduleVector.erase(itSchedule + i);
                itSchedule = scheduleVector.begin();
                i--;
            }

        return true;
    }

    return false;
}


bool scheduleData::removeOneInGroup(Group* group) 
{
    bool removed = false;

    auto itGroup = groupVector.begin();
    auto itSchedule = scheduleVector.begin();

    for (int i = 0; i < groupVector.size(); i++)
        if (groupVector[i] == *group) {
            groupVector.erase(itGroup + i);
            return true;
        }

    return false;
}


bool scheduleData::removeOneInAuditory(Auditory* auditory) 
{
    auto itAuditory = auditoryVector.begin();
    auto itSchedule = scheduleVector.begin();

    for (int i = 0; i < auditoryVector.size(); i++)
        if (auditoryVector[i] == *auditory) {
            auditoryVector.erase(itAuditory + i);
            return true;
        }

    return false;
}


bool scheduleData::editAllSchedule(int index, schedule* sc)
{

    if (removeInSchedule(index)) {
        scheduleVector.push_back((*(new schedule(*sc))));
        return true;
    }
      
    return false;
}


bool scheduleData::editByDayInSchedule(int index, string* day)
{
    scheduleVector[index].setDayOfWeek(day);

    return true;
}


bool scheduleData::editByTimeInSchedule(int index, Time* time)
{
    scheduleVector[index].setTime(time);

    return true;
}


bool scheduleData::editByGroupInSchedule(int index, Group* group)
{
    scheduleVector[index].setGroup(group);

    return true;
}


bool scheduleData::editByAuditoryInSchedule(int index, Auditory* auditory)
{
    scheduleVector[index].setAuditory(auditory);

    return true;
}


bool scheduleData::editAuditory(Auditory* oldAuditory, Auditory* newAuditory)
{

    if (auditoryVector.size() == 0) {
        cout << "  Таблица Аудиторий пуста!!" << endl;
        return false;
    }


    for (int i = 0; i < auditoryVector.size(); i++) {
        if (auditoryVector[i] == *oldAuditory) {
            auditoryVector[i].setAuditoryName(newAuditory->getAuditoryName());
            return true;
        }
    }

    return false;
}


bool scheduleData::editGroup(Group* oldGroup, Group* newGroup)
{
    if (groupVector.size() == 0) {
        cout << "Таблица групп полностью пуста" << endl;
        return false;
    }

    for (int i = 0; i < groupVector.size(); i++)
        if (groupVector[i] == *oldGroup) {
            groupVector[i].setGroupName(newGroup->getGroupName());
            return true;
        }

    return false;
}


void scheduleData::showScheduleVector()
{

    if (!this->scheduleVector.size())
        cout << "\n!- Таблица РАСПИСАНИЯ пуста!\n";
    else {
        for (int i = 0; i < this->scheduleVector.size(); i++)
        {

            cout << endl;
            cout << "  " << i + 1 << "." << endl;
            cout << "    Номер недели: " << this->scheduleVector[i].getWeekNumber() << endl;
            cout << "    День недели: " << this->scheduleVector[i].getDayOfWeek() << endl;
            cout << this->scheduleVector[i].getTime() << endl;
            cout << this->scheduleVector[i].getGroup() << endl;
            cout << this->scheduleVector[i].getAuditory() << endl;

        }
    }

    cout << endl;

}


void scheduleData::showAuditoryVector()
{
    if (!this->auditoryVector.size())
        cout << "\n!- Таблица АУДИТОРИЙ пуста!\n";
    else {
        for (int i = 0; i < this->auditoryVector.size(); i++)
        {
            cout << endl;

            cout << "  " << i + 1 << "." << this->auditoryVector[i].getAuditoryName() << endl;

        }
    }
    cout << endl;
}


void scheduleData::showGroupVector()
{
    if (!this->groupVector.size())
        cout << "\n!- Таблица ГРУПП пуста!\n";
    else {
        for (int i = 0; i < this->groupVector.size(); i++)
        {
            cout << endl;
            cout << "  " << i + 1 << "." << this->groupVector[i].getGroupName() << endl;
        }
    }   
    cout << endl;
}


vector<schedule> scheduleData::getScheduleVector() { return scheduleVector; }


vector<Auditory> scheduleData::getAuditoryVector() { return auditoryVector; }


vector<Group> scheduleData::getGroupVector() { return groupVector; }


scheduleData::~scheduleData()
{
    this->scheduleVector.clear();
    this->scheduleVector.shrink_to_fit();

    this->auditoryVector.clear();
    this->auditoryVector.shrink_to_fit();

    this->groupVector.clear();
    this->groupVector.shrink_to_fit();
}