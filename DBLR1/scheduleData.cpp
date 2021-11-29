#include<iostream>
#include<vector>
#include <sstream>
#include"scheduleData.h"

using namespace::std;

void scheduleData::updateIdVectors(schedule* sch)
{

    int schedId = 0, auditId = 0, groupId = 0;

    schedId = dMapper.findSchedId(sch);
    auditId = dMapper.findAuditId(sch->getAuditory());
    groupId = dMapper.findGroupId(sch->getGroup());

    if (schedId > 0 && auditId > 0 && groupId > 0) {
        cout << "!- Вставка в БД выполнена успешно!" << endl;
        sch->setID(schedId);
        if (insertSchedule(*sch)) {
            cout << "!- Вставка в ОП выполнена успешно!" << endl;
            for (int i = 0; i < getAuditoryVector().size(); i++)
                if (*(getAuditoryVector()[i]) == *(sch->getAuditory())) {
                    //scheduleDataVector->removeOneInAuditory(sch->getAuditory());
                    break;
                }
            string str = sch->getAuditory()->getAuditoryName();
            insertAuditory(*(new Auditory(auditId, str)));

            for (int i = 0; i < getGroupVector().size(); i++)
                if (*getGroupVector()[i] == *(sch->getGroup())) {
                    //scheduleDataVector->removeOneInGroup(sch->getGroup());
                    break;
                }
            string group = sch->getGroup()->getGroupName();
            insertGroup(*(new Group(groupId, group)));

        }
        else
            cout << "!- Ошибка вставки в ОП!" << endl;
    }
    else
        cout << "!- Произошла ошибка вставки в БД!" << endl;

}


bool scheduleData::ScheduleVectorCheck(schedule& schedule)
{
    return (schedule.getWeekNumber() > 0 && schedule.getWeekNumber() <= 18) &&
        (schedule.getDayOfWeek() == "Понедельник" || schedule.getDayOfWeek() == "Вторник" ||
            schedule.getDayOfWeek() == "Среда" || schedule.getDayOfWeek() == "Четверг" ||
            schedule.getDayOfWeek() == "Пятница" || schedule.getDayOfWeek() == "Суббота") &&
        ((schedule.getTime()->getTimeStart() == "8:30" && schedule.getTime()->getTimeEnd() == "10:00") ||
            (schedule.getTime()->getTimeStart() == "10:15" && schedule.getTime()->getTimeEnd() == "11:45") ||
            (schedule.getTime()->getTimeStart() == "12:00" && schedule.getTime()->getTimeEnd() == "13:30") ||
            (schedule.getTime()->getTimeStart() == "14:00" && schedule.getTime()->getTimeEnd() == "15:30") ||
            (schedule.getTime()->getTimeStart() == "15:45" && schedule.getTime()->getTimeEnd() == "17:15") ||
            (schedule.getTime()->getTimeStart() == "17:30" && schedule.getTime()->getTimeEnd() == "19:00") ||
            (schedule.getTime()->getTimeStart() == "19:15" && schedule.getTime()->getTimeEnd() == "20:45"));

}


bool scheduleData::insertSchedule(schedule& sch) 
{ 

    fillAllTablesFromDB();


    if (!isScheduleExist(sch)) {

        insertAuditory(*sch.getAuditory());
        insertGroup(*sch.getGroup());

        int idAuditory = findIdInAuditVector(*sch.getAuditory());
        int idGroup = findIdInGroupVector(*sch.getGroup());
        int idSch = scheduleVector.size() + 1;

        int weekNum = sch.getWeekNumber();
        string dayStr = sch.getDayOfWeek();
        string timeStart = sch.getTime()->getTimeStart();
        string timeEnd = sch.getTime()->getTimeEnd();

        scheduleVector.push_back(new schedule(idSch, weekNum, dayStr, new Time(timeStart, timeEnd), groupVector[idGroup], auditoryVector[idAuditory]));

        dMapper.insert(&sch);

        return true;
    }

    return false; 
}


int scheduleData::findIdInAuditVector(Auditory& auditory)
{

    for (int i = 0; i < auditoryVector.size(); i++)
        if (*auditoryVector[i] == auditory)
            return i;

    return -1;

}


int scheduleData::findIdInGroupVector(Group& group)
{

    for (int i = 0; i < groupVector.size(); i++)
        if (*groupVector[i] == group)
            return i;

    return -1;
}


int scheduleData::findIdInScheduleVector(schedule& sch)
{

    for (int i = 0; i < scheduleVector.size(); i++)
        if (*scheduleVector[i] == sch)
            return i;

    return -1;
}


bool scheduleData::isScheduleExist(schedule& sch) 
{
    for(int i = 0; i < scheduleVector.size(); i++)
        if (*scheduleVector[i] == sch)
            return true;

    return false;
}


bool scheduleData::insertAuditory(Auditory& auditory) {

    if (!isAuditoryExist(auditory)) {
        int id = auditory.getId();
        string auditoryStr = auditory.getAuditoryName();
        this->auditoryVector.push_back(new Auditory(id, auditoryStr));
        return true;
    }

    return false;

}

void scheduleData::fillAllTablesFromDB()
{

    vector <schedule*> SDV;
    vector <Auditory*> ADV;
    vector <Group*> GDV;

    if (auditoryVector.size() == 0 || groupVector.size() == 0) {
        SDV = dMapper.fillAllVectors();
        ADV = dMapper.fillAllVectorsFromAuditory();
        GDV = dMapper.fillAllVectorsFromGroup();


        for (int i = 0; i < ADV.size(); i++) {
            insertAuditory(*ADV[i]);
        }

        for (int i = 0; i < GDV.size(); i++) {
            insertGroup(*GDV[i]);
        }

        for (int i = 0; i < SDV.size(); i++) {
            if (!isScheduleExist(*SDV[i])) {

                int idAuditory = findIdInAuditVector(*SDV[i]->getAuditory());
                int idGroup = findIdInGroupVector(*SDV[i]->getGroup());
                int idSch = scheduleVector.size() + 1;

                int weekNum = SDV[i]->getWeekNumber();
                string dayStr = SDV[i]->getDayOfWeek();
                string timeStart = SDV[i]->getTime()->getTimeStart();
                string timeEnd = SDV[i]->getTime()->getTimeEnd();

                scheduleVector.push_back(new schedule(idSch, weekNum, dayStr, new Time(timeStart, timeEnd), groupVector[idGroup], auditoryVector[idAuditory]));

            }
        }


    }

    SDV.clear();
    SDV.shrink_to_fit();
    
    ADV.clear();
    ADV.shrink_to_fit();
    
    GDV.clear();
    GDV.shrink_to_fit();

}


bool scheduleData::insertAuditoryAndDB(Auditory& auditory)
{

    fillAllTablesFromDB();

    if (!isAuditoryExist(auditory)) {
        if (dMapper.insertToAuditory(&auditory)) {
            cout << "!- Вставка в БД прошла успешно!" << endl;
            int IdAuditory = dMapper.findAuditId(&auditory);
            string auditoryStr = auditory.getAuditoryName();
            this->auditoryVector.push_back(new Auditory(IdAuditory, auditoryStr));
            cout << "!- Вставка в ВЕКТОР прошла успешно!" << endl;

            return true;
        }
        cout << "!- Ошибка вставки в БД" << endl;
        return false;
        
    }

    
    return false;
}


bool scheduleData::isAuditoryExist(Auditory& auditory)
{
    for (int i = 0; i < auditoryVector.size(); i++)
        if (*auditoryVector[i] == auditory)
            return true;

    return false;
}


bool scheduleData::insertGroup(Group& group) {

    if (!isGroupExist(group)) {
        int id = group.getId();
        string groupStr = group.getGroupName();
        this->groupVector.push_back(new Group(id, groupStr));
        return true;
    }

    return false;
}


bool scheduleData::insertGroupAndDB(Group& group)
{
    fillAllTablesFromDB();

    if (!isGroupExist(group)) {
        if (dMapper.insertToGroup(&group)) {
            cout << "!- Вставка в БД прошла успешно!" << endl;
            int IdGroup = dMapper.findGroupId(&group);
            string groupStr = group.getGroupName();
            this->groupVector.push_back(new Group(IdGroup, groupStr));
            cout << "!- Вставка в ВЕКТОР прошла успешно!" << endl;

            return true;
        }
        cout << "!- Ошибка вставки в БД" << endl;
        return false;

    }

    return false;
}



bool scheduleData::isGroupExist(Group& group)
{

    for (int i = 0; i < groupVector.size(); i++)
        if (*groupVector[i] == group)
            return true;

    return false;
}


bool scheduleData::removeOneInAuditory(Auditory& auditory)
{

    fillAllTablesFromDB();

    Auditory* delA, a;
    auto itAuditory = auditoryVector.begin();

    for (int i = 0; i < auditoryVector.size(); i++) {
        if (*auditoryVector[i] == auditory) {
            delA = auditoryVector[i];
            a = *auditoryVector[i];
            auditoryVector.erase(itAuditory + i);
            delete delA;
            break;
        }
    }

    freeSchedule();

    dMapper.removeByAuditory(&a.getAuditoryName());

    return true;
}


bool scheduleData::removeOneInGroup(Group& group)
{
    fillAllTablesFromDB();


    Group* delG, g;
    auto itGroup = groupVector.begin();

    for (int i = 0; i < groupVector.size(); i++)
        if (*groupVector[i] == group) {
            delG = groupVector[i];
            g = *groupVector[i];
            groupVector.erase(itGroup + i);
            delete delG;
            break;
        }

    freeSchedule();

    dMapper.removeByGroup(&g.getGroupName());

    return true;
}


bool scheduleData::removeInSchedule(int& index)
{

    fillAllTablesFromDB();

    if (index > 0 && index <= getScheduleVector().size()) {


        int delNum = scheduleVector[index - 1]->getID();
        auto scheduleIt = scheduleVector.begin();

        for (int i = 0; i < scheduleVector.size(); i++, scheduleIt++) {
            if (scheduleVector[i]->getID() == delNum) {
                scheduleVector.erase(scheduleIt);
                break;
            }
        }
        dMapper.remove(&index);
        return true;
    }
    else
        return false;

}


bool scheduleData::freeSchedule()
{
    for (int i = 0; i < scheduleVector.size(); i++) {

        if (scheduleVector[i]->getAuditory()->getId() < 0 || scheduleVector[i]->getGroup()->getId() < 0) {
            scheduleVector.erase(scheduleVector.begin() + i);
            i--;
        }

    }

    return true;
}


bool scheduleData::editAllSchedule(int& index, schedule& sc)
{
    fillAllTablesFromDB();

    if (index > 0 && index <= getScheduleVector().size()) {

        if (removeInSchedule(index)) {
            insertSchedule(sc);
            return true;
        }
        return false;
    }
    return false;
}


bool scheduleData::editByDayInSchedule(int& index, string& day)
{
    fillAllTablesFromDB();

    if (index > 0 && index <= getScheduleVector().size()) {

        scheduleVector[index - 1]->setDayOfWeek(day);

        dMapper.editByDay(&index, &day);
        return true;

    }
    return false;
}


bool scheduleData::editByTimeInSchedule(int& index, Time& time)
{
    fillAllTablesFromDB();

    if (index > 0 && index <= getScheduleVector().size()) {

        scheduleVector[index - 1]->setTime(&time);

        dMapper.editByTime(&index, &time.getTimeStart(), &time.getTimeEnd());
        return true;

    }
    return false;
}


bool scheduleData::editByGroupInSchedule(int& index, Group& group)
{
    fillAllTablesFromDB();

    if (index > 0 && index <= getScheduleVector().size()) {

        if (!isGroupExist(group))
            insertGroup(group);

        scheduleVector[index - 1]->setGroup(&group);

        dMapper.editByGroup(&index, &group.getGroupName());

        return true;
    }
    return false;
}


bool scheduleData::editByAuditoryInSchedule(int& index, Auditory& auditory)
{
    fillAllTablesFromDB();
    if (index > 0 && index <= getScheduleVector().size()) {
        if (!isAuditoryExist(auditory))
            insertAuditory(auditory);

        scheduleVector[index - 1]->setAuditory(&auditory);

        dMapper.editByAuditory(&index, &auditory.getAuditoryName());

        return true;
    }
    return false;
}

bool scheduleData::editAuditory(int& id, Auditory& newAuditory)
{
    fillAllTablesFromDB();

    if (auditoryVector.size() == 0) {
        cout << "  Таблица Аудиторий пуста!!" << endl;
        return false;
    }

    for (int i = 0; i < auditoryVector.size(); i++) {
        if (i == id-1) {
            string newStringAuditory = newAuditory.getAuditoryName();
            auditoryVector[i]->setAuditoryName(newStringAuditory);
            dMapper.editAuditory(&id, auditoryVector[i]);
            return true;
        }
    }


    return false;
}


bool scheduleData::editAuditory(Auditory& oldAuditory, Auditory& newAuditory)
{

    fillAllTablesFromDB();


    if (auditoryVector.size() == 0) {
        cout << "  Таблица Аудиторий пуста!!" << endl;
        return false;
    }


    for (int i = 0; i < auditoryVector.size(); i++) {
        if (*auditoryVector[i] == oldAuditory) {
            string newStringAuditory = newAuditory.getAuditoryName();
            auditoryVector[i]->setAuditoryName(newStringAuditory);
            dMapper.editAuditory(&oldAuditory, &newAuditory);
            return true;
        }
    }

    return false;
}

bool scheduleData::editGroup(int& id, Group& newGroup)
{
    fillAllTablesFromDB();

    if (groupVector.size() == 0) {
        cout << "  Таблица ГРУПП пуста!!" << endl;
        return false;
    }

    for (int i = 0; i < groupVector.size(); i++) {
        if (i == id - 1) {
            string newStringGroup = newGroup.getGroupName();
            groupVector[i]->setGroupName(newStringGroup);
            dMapper.editGroup(&id, groupVector[i]);
            return true;
        }
    }


    return false;
}


bool scheduleData::editGroup(Group& oldGroup, Group& newGroup)
{

    fillAllTablesFromDB();


    if (groupVector.size() == 0) {
        cout << "  Таблица ГРУПП пуста!!" << endl;
        return false;
    }


    for (int i = 0; i < groupVector.size(); i++) {
        if (*groupVector[i] == oldGroup) {
            string newStringAuditory = newGroup.getGroupName();
            groupVector[i]->setGroupName(newStringAuditory);
            dMapper.editGroup(&oldGroup, &newGroup);
            return true;
        }
    }

    return false;
}


void scheduleData::find(const string& str)
{

    fillAllTablesFromDB();

    vector<string> result;
    vector<schedule> busiAuditory;
    vector<vector<string>> freeAuditory;

    for (int i = 0; i < 18; i++) {
        freeAuditory.push_back(vector<string>());
        freeAuditory[i].push_back("Понедельник");
        freeAuditory[i].push_back("Вторник");
        freeAuditory[i].push_back("Среда");
        freeAuditory[i].push_back("Четверг");
        freeAuditory[i].push_back("Пятница");
        freeAuditory[i].push_back("Суббота");
    }

    stringstream data(str);
    string line;

    while (getline(data, line, ' '))
        result.push_back(line);

    int n = result.size();
    vector<string> hourtable;

    for (int i = 0; i < n; i++) {
        data.str(string()); //обычная очитска
        data.clear();       //сброс всех флагов ошибок
        line.clear();
        data.str(result[i]);
        while (getline(data, line, '-'))
            hourtable.push_back(line);
    }

    result.clear();
    result.shrink_to_fit();
    
    cout << endl;
    cout << ">> ЗАНЯТЫЕ АУДИТОРИИ В ЭТО ВРЕМЯ" << endl;


    for (int i = 0; i<scheduleVector.size(); i++)
    {
        for (int k = 0; k < hourtable.size(); k+=2) {

            if (((scheduleVector[i]->getTime()->getTimeStart()) == hourtable[k]) && ((scheduleVector[i]->getTime()->getTimeEnd()) == hourtable[k + 1])) {

                busiAuditory.push_back(*scheduleVector[i]);

                cout << endl;

                cout << "  " << i+1 << "." << endl;

                cout << "   Номер недели: " << scheduleVector[i]->getWeekNumber() << endl;

                cout << "   День недели: " << scheduleVector[i]->getDayOfWeek() << endl;

                cout << "   Время начала: " << scheduleVector[i]->getTime()->getTimeStart() << endl;

                cout << "   Время окончания: " << scheduleVector[i]->getTime()->getTimeEnd() << endl;

                cout << *scheduleVector[i]->getGroup();

                cout << *scheduleVector[i]->getAuditory();

                cout << endl;
            }
        }
    }
        
    cout << endl;
    cout << ">> Аудитория(-и) ";

    vector<string> auditForPrint;

      for (int i = 0; i < busiAuditory.size(); i++)
    {
        auto iterator = std::find(auditForPrint.begin(), auditForPrint.end(), string((busiAuditory[i].getAuditory()->getAuditoryName())));

        if (iterator == auditForPrint.end()) {
            i != 0 ? cout << ", " : cout;
            cout << (busiAuditory[i].getAuditory()->getAuditoryName());
            auditForPrint.push_back((busiAuditory[i].getAuditory()->getAuditoryName()));
        }

        auto it = freeAuditory.begin();

        for (int k = 0; k < busiAuditory[i].getWeekNumber() - 1; k++)
            it++;

        auto it2 = std::find(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), freeAuditory[std::distance(freeAuditory.begin(), it)].end(), string(busiAuditory[i].getDayOfWeek()));
        //cout << std::distance(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), it2) << endl;
        if (it2 != freeAuditory[std::distance(freeAuditory.begin(), it)].end())
            freeAuditory[std::distance(freeAuditory.begin(), it)].erase(it2);
    }

    auditForPrint.clear();
    auditForPrint.shrink_to_fit();

    cout << " в течении семестра свободна(-ы) на:" << endl;
    cout << endl;

    for (int i = 0; i < freeAuditory.size(); i++) {
        cout << ">> " << i + 1 << " неделе:";

        for (int k = 0; k < freeAuditory[i].size(); k++) {
            cout << " " << freeAuditory[i][k];
            k != freeAuditory[i].size() - 1 ? cout << "," : cout << "." << endl;
        }
    }

    cout << endl;
    cout << ">> ВСЕ ОСТАЛЬНЫЕ АУДИТОРИИ В ЗАДАННЫЕ ЧАСЫ В ТЕЧЕНИИ ВСЕГО СЕМЕСТРА СВОБОДНЫЕ!" << endl;
    cout << endl;

    hourtable.clear();
    hourtable.shrink_to_fit();

    busiAuditory.clear();
    busiAuditory.shrink_to_fit();

    freeAuditory.clear();
    freeAuditory.shrink_to_fit();

}


void scheduleData::find(const int &hoursNumber, const int &weekNumber)
{

    fillAllTablesFromDB();

    vector<string> daysOfWeek;
    vector<vector<string>> hourtable;

    int lessons = hoursNumber * 60 / 90;

    if (lessons > 42) {
        cout << "!- В одной неделе не может быть столько пар" << endl;
        return;
    }

    daysOfWeek.push_back("понедельник");
    daysOfWeek.push_back("вторник");
    daysOfWeek.push_back("среду");
    daysOfWeek.push_back("четверг");
    daysOfWeek.push_back("пятницу");
    daysOfWeek.push_back("субботу");

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
            if ((scheduleVector[k]->getAuditory()->getAuditoryName() == auditoryVector[i]->getAuditoryName()) &&
                (scheduleVector[k]->getWeekNumber() == weekNumber))
                schedAudit.push_back(*scheduleVector[k]);

        for (int k = 0;k<schedAudit.size(); k++)
        {

            auto it = hourtable.begin();
            for (int j = 0; j < schedAudit[k].getWeekNumber() - 1; j++)
                it++;

            string time = schedAudit[k].getTime()->getTimeStart() + "-" + schedAudit[k].getTime()->getTimeEnd();
            //cout << time;

            auto it2 = std::find(hourtable[std::distance(hourtable.begin(), it)].begin(), hourtable[std::distance(hourtable.begin(), it)].end(), time);

            if (it2 != hourtable[std::distance(hourtable.begin(), it)].end())
                *it2 = "";
        }

        //проверяем, хватит ли вообще занятий для этой аудитории
        for (int k = 0; k < hourtable.size() && lessons != 0; k++)
            for (int j = 0; j < hourtable[k].size() && lessons != 0; j++) {
                if (hourtable[k][j] == "")
                    continue;
                else
                    lessons--;
            }

        if (!lessons) {

            isFind = true;

            lessons = hoursNumber * 60 / 90;

            cout << endl;
            cout << ">> Для аудитории " << auditoryVector[i]->getAuditoryName();
            cout << " есть возможность заниматься " << lessons << " занятия(-ие/-ий):";

            for (int k = 0; k < hourtable.size(); k++) {
                k != 1 ? cout << "\n>> В " << daysOfWeek[k] << " в " : cout << "\n>> Во " << daysOfWeek[k] << " в ";
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
            lessons = hoursNumber * 60 / 90;

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
        cout << "\n!- Таблица РАСПИСАНИЯ пуста!\n";
    else {
        for (int i = 0; i < this->scheduleVector.size(); i++)
        {

            cout << endl;
            cout << "  " << i + 1 << "." << endl;
            cout << "    Номер недели: " << scheduleVector[i]->getWeekNumber() << endl;
            cout << "    День недели: " <<  scheduleVector[i]->getDayOfWeek() << endl;
            cout << *scheduleVector[i]->getTime();
            cout << *scheduleVector[i]->getGroup();
            cout << *scheduleVector[i]->getAuditory();

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

            cout << "  " << i + 1 << "." << auditoryVector[i]->getAuditoryName() << endl;

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
            cout << "  " << i + 1 << "." << groupVector[i]->getGroupName() << endl;
        }
    }   
    cout << endl;
}


void scheduleData::printDBShedule() { dMapper.printAll(); }


void scheduleData::printDBAuditory() { dMapper.printAuditorySchedule(); }


void scheduleData::printDBGroup() { dMapper.printGroupSchedule(); }


vector<schedule*> scheduleData::getScheduleVector() { return scheduleVector; }


vector<Auditory*> scheduleData::getAuditoryVector() { return auditoryVector; }


vector<Group*> scheduleData::getGroupVector() { return groupVector; }


scheduleData::~scheduleData()
{
    this->scheduleVector.clear();
    this->scheduleVector.shrink_to_fit();

    this->auditoryVector.clear();
    this->auditoryVector.shrink_to_fit();

    this->groupVector.clear();
    this->groupVector.shrink_to_fit();
}


//bool scheduleData::removeAllInGroup(Group* group)
//{
//
//    bool removed = false;
//    auto itSchedule = scheduleVector.begin();
//    auto itGroup = groupVector.begin();
//
//    /*auto it = std::find(groupVector.begin(), groupVector.end(), group->getGroupName());
//    if (it != groupVector.end())
//        groupVector.erase(it);*/
//
//    for (int i = 0; i < groupVector.size(); i++, itGroup++)
//        if (groupVector[i] == *group) {
//            groupVector.erase(itGroup);
//            removed = true;
//            break;
//        }
//
//    if (removed) {
//        for (int i = 0; i < scheduleVector.size(); i++) {
//            if (*(scheduleVector[i].getGroup()) == *group) {
//                scheduleVector.erase(itSchedule + i);
//                itSchedule = scheduleVector.begin();
//                i--;
//            }
//        }
//        return true;
//    }
//
//    return false;
//
//}
//bool scheduleData::removeAllInAuditory(Auditory* auditory)
//{
//    bool removed = false;
//
//    auto itAuditory = auditoryVector.begin();
//    auto itSchedule = scheduleVector.begin();
//
//    for (int i = 0; i < auditoryVector.size(); i++, itAuditory++)
//        if (auditoryVector[i] == *auditory) {
//            auditoryVector.erase(itAuditory);
//            removed = true;
//            break;
//        }
//
//    if (removed) {
//        for (int i = 0; i < scheduleVector.size(); i++)
//            if (*(scheduleVector[i].getAuditory()) == *auditory) {
//                scheduleVector.erase(itSchedule + i);
//                itSchedule = scheduleVector.begin();
//                i--;
//            }
//
//        return true;
//    }
//
//    return false;
//}