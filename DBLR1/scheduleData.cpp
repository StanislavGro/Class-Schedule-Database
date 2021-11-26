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
    scheduleVector[index-1].setDayOfWeek(new string(*day));

    return true;
}


bool scheduleData::editByTimeInSchedule(int index, Time* time)
{
    scheduleVector[index-1].setTime(new Time(*time));

    return true;
}


bool scheduleData::editByGroupInSchedule(int index, Group* group)
{
    if (!isGroupExist(group))
        this->groupVector.push_back(*(new Group(*group)));
    
    scheduleVector[index-1].setGroup(new Group(*group));


    return true;
}


bool scheduleData::editByAuditoryInSchedule(int index, Auditory* auditory)
{

    if (!isAuditoryExist(auditory))
        this->auditoryVector.push_back(*(new Auditory(*auditory)));

    scheduleVector[index-1].setAuditory(new Auditory(*auditory));

    return true;
}


bool scheduleData::editAuditory(Auditory* oldAuditory, Auditory* newAuditory)
{

    if (auditoryVector.size() == 0) {
        cout << "  ������� ��������� �����!!" << endl;
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
        cout << "������� ����� ��������� �����" << endl;
        return false;
    }

    for (int i = 0; i < groupVector.size(); i++)
        if (groupVector[i] == *oldGroup) {
            groupVector[i].setGroupName(newGroup->getGroupName());
            return true;
        }

    return false;
}

void scheduleData::find(string* str)
{

    vector<string> result;
    vector<schedule> busiAuditory;
    vector<vector<string>> freeAuditory;

    for (int i = 0; i < 18; i++) {
        freeAuditory.push_back(vector<string>());
        freeAuditory[i].push_back("�����������");
        freeAuditory[i].push_back("�������");
        freeAuditory[i].push_back("�����");
        freeAuditory[i].push_back("�������");
        freeAuditory[i].push_back("�������");
        freeAuditory[i].push_back("�������");
    }

    stringstream data(*str);
    string line;

    while (getline(data, line, ' '))
        result.push_back(line);

    int n = result.size();
    vector<string> hourtable;

    for (int i = 0; i < n; i++) {
        data.str(string()); //������� �������
        data.clear();       //����� ���� ������ ������
        line.clear();
        data.str(result[i]);
        while (getline(data, line, '-'))
            hourtable.push_back(line);
    }

    result.clear();
    result.shrink_to_fit();
    
    cout << endl;
    cout << ">> ������� ��������� � ��� �����" << endl;


    for (int i = 0; i<scheduleVector.size(); i++)
    {
        for (int k = 0; k < hourtable.size(); k+=2) {

            if ((*(scheduleVector[i].getTime()->getTimeStart()) == hourtable[k]) && (*(scheduleVector[i].getTime()->getTimeEnd()) == hourtable[k + 1])) {

                busiAuditory.push_back(scheduleVector[i]);

                cout << endl;

                cout << "  " << i+1 << "." << endl;

                cout << "   ����� ������: " << *scheduleVector[i].getWeekNumber() << endl;

                cout << "   ���� ������: " << *scheduleVector[i].getDayOfWeek() << endl;

                cout << "   ����� ������: " << *scheduleVector[i].getTime()->getTimeStart() << endl;

                cout << "   ����� ���������: " << *scheduleVector[i].getTime()->getTimeEnd() << endl;

                cout << *scheduleVector[i].getGroup();

                cout << *scheduleVector[i].getAuditory();

                cout << endl;
            }
        }
    }
        
    cout << endl;
    cout << ">> ���������(-�) ";

    vector<string> auditForPrint;

      for (int i = 0; i < busiAuditory.size(); i++)
    {
        auto iterator = std::find(auditForPrint.begin(), auditForPrint.end(), string(*(busiAuditory[i].getAuditory()->getAuditoryName())));

        if (iterator == auditForPrint.end()) {
            i != 0 ? cout << ", " : cout;
            cout << *(busiAuditory[i].getAuditory()->getAuditoryName());
            auditForPrint.push_back(*(busiAuditory[i].getAuditory()->getAuditoryName()));
        }

        auto it = freeAuditory.begin();

        for (int k = 0; k < *busiAuditory[i].getWeekNumber() - 1; k++)
            it++;

        auto it2 = std::find(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), freeAuditory[std::distance(freeAuditory.begin(), it)].end(), string(*busiAuditory[i].getDayOfWeek()));
        //cout << std::distance(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), it2) << endl;
        if (it2 != freeAuditory[std::distance(freeAuditory.begin(), it)].end())
            freeAuditory[std::distance(freeAuditory.begin(), it)].erase(it2);
    }

    auditForPrint.clear();
    auditForPrint.shrink_to_fit();

    cout << " � ������� �������� ��������(-�) ��:" << endl;
    cout << endl;

    for (int i = 0; i < freeAuditory.size(); i++) {
        cout << ">> " << i + 1 << " ������:";

        for (int k = 0; k < freeAuditory[i].size(); k++) {
            cout << " " << freeAuditory[i][k];
            k != freeAuditory[i].size() - 1 ? cout << "," : cout << "." << endl;
        }
    }

    cout << endl;
    cout << ">> ��� ��������� ��������� � �������� ���� � ������� ����� �������� ���������!" << endl;
    cout << endl;

    hourtable.clear();
    hourtable.shrink_to_fit();

    busiAuditory.clear();
    busiAuditory.shrink_to_fit();

    freeAuditory.clear();
    freeAuditory.shrink_to_fit();

}

void scheduleData::find(int *hoursNumber, int *weekNumber)
{

    vector<string> daysOfWeek;
    vector<vector<string>> hourtable;

    int lessons = *hoursNumber * 60 / 90;

    if (lessons > 42) {
        cout << "!- � ����� ������ �� ����� ���� ������� ���" << endl;
        return;
    }

    daysOfWeek.push_back("�����������");
    daysOfWeek.push_back("�������");
    daysOfWeek.push_back("�����");
    daysOfWeek.push_back("�������");
    daysOfWeek.push_back("�������");
    daysOfWeek.push_back("�������");

    bool isFind = false;

    for (int i = 0; auditoryVector.size() && isFind ==false; i++) {

        for (int i = 0; i < 6; i++) {
            hourtable.push_back(vector<string>());
            hourtable[i].push_back("8:30-10:00");
            hourtable[i].push_back("10:15-11:45");
            hourtable[i].push_back("12:00-13:30");
            hourtable[i].push_back("14:00-15:30");
            hourtable[i].push_back("15:45-17:15");
            hourtable[i].push_back("17:30-19:00");
            hourtable[i].push_back("19:15-20:45");
        }

        vector<schedule> schedAudit;
        for (int k = 0; k < scheduleVector.size(); k++)
            if ((*scheduleVector[k].getAuditory()->getAuditoryName() == *auditoryVector[i].getAuditoryName()) && 
                (*scheduleVector[k].getWeekNumber() == *weekNumber))
                schedAudit.push_back(scheduleVector[k]);

        for (int k = 0;k<schedAudit.size(); k++)
        {

            auto it = hourtable.begin();
            for (int j = 0; j < *schedAudit[k].getWeekNumber() - 1; j++)
                it++;

            string time = *schedAudit[k].getTime()->getTimeStart() + "-" + *schedAudit[k].getTime()->getTimeEnd();
            //cout << time;

            auto it2 = std::find(hourtable[std::distance(hourtable.begin(), it)].begin(), hourtable[std::distance(hourtable.begin(), it)].end(), time);

            if (it2 != hourtable[std::distance(hourtable.begin(), it)].end())
                *it2 = "";
        }

        //���������, ������ �� ������ ������� ��� ���� ���������
        for (int k = 0; k < hourtable.size() && lessons != 0; k++)
            for (int j = 0; j < hourtable[k].size() && lessons != 0; j++) {
                if (hourtable[k][j] == "")
                    continue;
                else
                    lessons--;
            }

        if (!lessons) {

            isFind = true;

            lessons = *hoursNumber * 60 / 90;

            cout << endl;
            cout << ">> ��� ��������� " << *auditoryVector[i].getAuditoryName();
            cout << " ���� ����������� ���������� " << lessons << " �������(-��/-��):";

            for (int k = 0; k < hourtable.size(); k++) {
                k != 1 ? cout << "\n>> � " << daysOfWeek[k] << " � " : cout << "\n>> �� " << daysOfWeek[k] << " � ";
                for (int j = 0; j < hourtable[k].size() && lessons != 0; j++, lessons--) {
                    if (hourtable[k][j] != "") {
                        cout << hourtable[k][j];
                        j == hourtable[k].size() - 1 or lessons - 1 == 0 ? cout << "." : cout << ", ";
                    }
                    else
                        lessons++;
                }
                if (!lessons) {
                    isFind = true;
                    break;
                }
            }
            cout << "\n\n";

        }
        else
            lessons = *hoursNumber * 60 / 90;

        hourtable.clear();
        hourtable.shrink_to_fit();

        schedAudit.clear();
        schedAudit.shrink_to_fit();
    }

    daysOfWeek.clear();
    daysOfWeek.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();


}


void scheduleData::showScheduleVector()
{

    if (!this->scheduleVector.size())
        cout << "\n!- ������� ���������� �����!\n";
    else {
        for (int i = 0; i < this->scheduleVector.size(); i++)
        {

            cout << endl;
            cout << "  " << i + 1 << "." << endl;
            cout << "    ����� ������: " << this->scheduleVector[i].getWeekNumber() << endl;
            cout << "    ���� ������: " << this->scheduleVector[i].getDayOfWeek() << endl;
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
        cout << "\n!- ������� ��������� �����!\n";
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
        cout << "\n!- ������� ����� �����!\n";
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