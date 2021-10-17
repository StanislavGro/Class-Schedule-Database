#include "DataMapper.h"
#include<iostream>
#include<vector>
#include <sstream>

using namespace::std;

DataMapper::DataMapper() { 

    if (connectToDB() == 1)
        creatingTables();
    else
        cout << "Какая-то неизвестная ошибка!" << endl;

}


int DataMapper::connectToDB() 
{
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retcode < 0)
        return -1;
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_NTS);
    if (retcode < 0)
        return -2;
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (retcode < 0)
        return -3;

    retcode = SQLConnect(hdbc, (SQLWCHAR*)L"Mydbase", SQL_NTS,
        (SQLWCHAR*)L"stanis", SQL_NTS, (SQLWCHAR*)L"130263", SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
        if (retcode < 0)
            return -6;

        return 1;
    }
    if (retcode < 0)
        return -4;

    return -5;
}


bool DataMapper::insert(schedule sched)
{

    scheduleMapper.push_back(sched);
   
    SQLINTEGER week = sched.getWeekNumber();
    SQLWCHAR day[20];
    SQLWCHAR time[20];
    SQLWCHAR group[20];
    SQLINTEGER auditory = sched.getClassroomNumber();

    strcpy_s((char*)group, strlen(sched.getGroupName().c_str()) + 1, sched.getGroupName().c_str());
    strcpy_s((char*)time , strlen(sched.getTimePeriod().c_str()) + 1, sched.getTimePeriod().c_str());
    strcpy_s((char*)day , strlen(sched.getDayOfWeek().c_str()) + 1, sched.getDayOfWeek().c_str());


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory_table(auditory)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO groupp_table(groupp)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO week_table(week)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO schedule(week, day, time, groupp, auditory)"
                        "VALUES (?, ?, ?, ?, ?)", SQL_NTS);
    retcode = SQLExecute(hstmt);

    return true;
}


bool DataMapper::edit(int number, schedule sched)
{
    SQLINTEGER auditory = sched.getClassroomNumber();
    SQLINTEGER week = sched.getWeekNumber();
    SQLWCHAR group[20];
    SQLWCHAR day[20];
    SQLWCHAR time[20];
    SQLINTEGER editNumber = number;


    strcpy_s((char*)group, strlen(sched.getGroupName().c_str()) + 1, sched.getGroupName().c_str());
    strcpy_s((char*)time, strlen(sched.getTimePeriod().c_str()) + 1, sched.getTimePeriod().c_str());
    strcpy_s((char*)day, strlen(sched.getDayOfWeek().c_str()) + 1, sched.getDayOfWeek().c_str());


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory_table(auditory)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO groupp_table(groupp)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO week_table(week)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"update schedule set week = ?, day = ?, time = ?, groupp = ?, auditory = ? where id = ?", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}


bool DataMapper::remove(int number)
{
    SQLINTEGER editNumber = number;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &editNumber, 0, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"delete from schedule where id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}


void DataMapper::find(int audit, string str)
{


    vector<string> result;
    vector<vector<string>> timetable;
    vector<vector<vector<string>>> hourtable;

    int numberOfWeekInTerm = 8;

    for (int i = 0; i < numberOfWeekInTerm; i++) {
        timetable.push_back(vector<string>());
        timetable[i].push_back("Понедельник");
        timetable[i].push_back("Вторник");
        timetable[i].push_back("Среда");
        timetable[i].push_back("Четверг");
        timetable[i].push_back("Пятница");
        timetable[i].push_back("Суббота");
    }


    stringstream data(str);

    string line;

    while (getline(data, line, ' '))
        result.push_back(line);

    int n = result.size();

    for (int i = 0; i < numberOfWeekInTerm; i++) {
        hourtable.push_back(vector<vector<string>>());
        for (int k = 0; k < 7; k++) {
            hourtable[i].push_back(vector<string>());
            for (int q = 0; q < n; q++)
                hourtable[i][k].push_back(result[q]);
        }
    }

    SQLWCHAR** hours = new SQLWCHAR * [n];

    for (int k = 0; k < n; k++)
        hours[k] = new SQLWCHAR[result[k].size()];

    SQLRETURN* newRetcode = new SQLRETURN(n + 1);

    for (int k = 0; k < n; k++)
        strcpy_s((char*)hours[k], strlen(result[k].c_str()) + 1, result[k].c_str());


    for (int k = 0; k < n; k++)
        newRetcode[k] = SQLBindParameter(hstmt, k + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours[k], 255, NULL);
    newRetcode[n] = SQLBindParameter(hstmt, n + 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 255, 0, &audit, 255, NULL);


    wstring output = L"select week, day, time, auditory from schedule where (time = ?";

    for (int k = 0; k < n - 1; k++)
        output += L" or time = ?";

    output += L") and auditory = ?";

    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours, 255, NULL);

    int week = 0;
    char day[20];
    char time[20];
    //char group[20];
    int auditory = 0;

    //const char* charOutput = output.c_str();
    wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, time, 20, NULL);
        //retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, group, 15, NULL);
        retcode = SQLBindCol(hstmt, 4, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);

        for (int i = 1;; i++)
        {

            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                for (int q = 0; q < timetable.size(); q++) {

                    auto it = std::find(timetable[q].begin(), timetable[q].end(), string(day));

                    //cout << std::distance(timetable.begin(), it) << endl;

                    auto it2 = std::find(hourtable[q][std::distance(timetable[q].begin(), it)].begin(), hourtable[q][std::distance(timetable[q].begin(), it)].end(), string(time));
                    if (it2 != hourtable[q][std::distance(timetable[q].begin(), it)].end())
                        hourtable[q][std::distance(timetable[q].begin(), it)].erase(it2);

                    if (hourtable[q][std::distance(timetable[q].begin(), it)].empty())
                        timetable[q][std::distance(timetable[q].begin(), it)] = "-1";
                }
            }
            else
                break;
        }

        cout << "Список свободных аудиторий за весь семестр: " << endl;


        for (int i = 0, s = 1; i < timetable.size(); i++)
            for (int p = 0; p < timetable[i].size(); p++)
                if (timetable[i][p] != "-1")
                    for (int k = 0; k < hourtable[i][p].size(); k++, s++) {

                        cout << endl;

                        cout << s << "." << endl;
                        cout << "  Номер недели: " << i+1 << endl;

                        cout << "  День недели: " << timetable[i][p] << endl;

                        cout << "  Время: " << hourtable[i][p][k] << endl;

                        cout << "  Название группы: ПУСТО" << endl;

                        cout << "  Номер аудитории: " << audit << endl;
                    }

    }


        cout << endl;

    

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    result.clear();
    result.shrink_to_fit();

    timetable.clear();
    timetable.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();
    
}


void DataMapper::find(int audit, string str, int number)
{

    vector<string> result;
    vector<string> timetable;
    vector<vector<string>> hourtable;

    timetable.push_back("Понедельник");
    timetable.push_back("Вторник");
    timetable.push_back("Среда");
    timetable.push_back("Четверг");
    timetable.push_back("Пятница");
    timetable.push_back("Суббота");        

    stringstream data(str);

    string line;

    while (getline(data, line, ' '))
        result.push_back(line);

    int n = result.size();

    for (int i = 0; i < 7; i++) {
        hourtable.push_back(vector<string>());
        for (int k = 0; k < n; k++)
            hourtable[i].push_back(result[k]);
    }

    SQLWCHAR** hours = new SQLWCHAR * [n];
    SQLINTEGER num = number;

    for (int k = 0; k < n; k++)
        hours[k] = new SQLWCHAR[result[k].size()];

    SQLRETURN* newRetcode = new SQLRETURN(n+2);

    for (int k = 0; k < n; k++)
        strcpy_s((char*)hours[k], strlen(result[k].c_str()) + 1, result[k].c_str());


    for (int k = 0; k < n; k++)
        newRetcode[k] = SQLBindParameter(hstmt, k + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours[k], 255, NULL);
    newRetcode[n] = SQLBindParameter(hstmt, n+1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 255, 0, &num, 255, NULL);
    newRetcode[n+1] = SQLBindParameter(hstmt, n + 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 255, 0, &audit, 255, NULL);


    wstring output = L"select week, day, time, auditory from schedule where (time = ?";

    for (int k = 0; k < n - 1; k++)
        output += L" or time = ?";

    output += L") and week = ? and auditory = ?";

    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours, 255, NULL);

    int week = 0;
    char day[20];
    char time[20];
    //char group[20];
    int auditory = 0;

    //const char* charOutput = output.c_str();
    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, time, 20, NULL);
        //retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, group, 15, NULL);
        retcode = SQLBindCol(hstmt, 4, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);

        for (int i = 1;; i++)
        {
            
            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                
                auto it = std::find(timetable.begin(), timetable.end(), string(day));

                //cout << std::distance(timetable.begin(), it) << endl;

                auto it2 = std::find(hourtable[std::distance(timetable.begin(), it)].begin(), hourtable[std::distance(timetable.begin(), it)].end(), string(time));
                if (it2 != hourtable[std::distance(timetable.begin(), it)].end())
                    hourtable[std::distance(timetable.begin(), it)].erase(it2);

                if(hourtable[std::distance(timetable.begin(), it)].empty())
                    timetable[std::distance(timetable.begin(), it)] = "-1";

            }
            else
                break;
        }

        cout << "Список свободных аудиторий: " << endl;
        

        for (int i = 0, s=1; i < timetable.size(); i++)   
            if (timetable[i] != "-1")
                for (int k = 0; k < hourtable[i].size(); k++, s++) {
                    cout << endl;

                    cout << s << "." << endl;
                    cout << "  Номер недели: " << number << endl;

                    cout << "  День недели: " << timetable[i] << endl;

                    cout << "  Время: " << hourtable[i][k] << endl;

                    cout << "  Название группы: ПУСТО" << endl;

                    cout << "  Номер аудитории: " << audit << endl;

                }
         
        cout << endl;

    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    result.clear();
    result.shrink_to_fit();

    timetable.clear();
    timetable.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();


}


void DataMapper::creatingTables()
{

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "week int,"
        "day varchar(20),"
        "time varchar(20),"
        "groupp varchar(20),"
        "auditory int"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory_table("
        "id serial primary key,"
        "auditory int unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists groupp_table("
        "id serial primary key,"
        "groupp varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists week_table("
        "id serial primary key,"
        "week int unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day_table("
        "id serial primary key,"
        "day varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time_table("
        "id serial primary key,"
        "time varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint auditoryForKey foreign key(auditory)" 
        "references auditory_table(auditory) on update cascade on delete cascade;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint grouppForKey foreign key(groupp)" 
        "references groupp_table(groupp) on update cascade on delete cascade;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint weekForKey foreign key(week)"
        "references week_table(week) on update cascade on delete cascade;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint dayForKey foreign key(day)"
        "references day_table(day) on update cascade on delete cascade;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint timeForKey foreign key(time)"
        "references time_table(time) on update cascade on delete cascade;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

}


vector<schedule> DataMapper::getSchedule()
{
    return scheduleMapper;
}


void DataMapper::printAll()
{

    int week = 0;
    char day [20];
    char time [20];
    char group [20];
    int auditory = 0;

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select week, day, time, groupp, auditory from schedule", SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 15, NULL);
        retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, time, 15, NULL);
        retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, group, 15, NULL);
        retcode = SQLBindCol(hstmt, 5, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);

        for (int i = 1;; i++)
        {
            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                cout << endl;

                cout << i << "." << endl;
                cout << "  Номер недели: " << week << endl;

                cout << "  День недели: ";
                for (int k = 0; day[k] != '\0'; k++)
                    cout << day[k];
                cout << endl;

                cout << "  Время: ";
                for (int k = 0; time[k] != '\0'; k++)
                    cout << time[k];
                cout << endl;

                cout << "  Название группы: ";
                for (int k = 0; group[k] != '\0'; k++)
                    cout << group[k];
                cout << endl;
            
                cout << "  Номер аудитории: " << auditory << endl;

            }
            else
                break;
        }

        cout << endl;

    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

}


int DataMapper::disconnectFromDB() 
{

    retcode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    if (retcode < 0)
        return -21;
    retcode = SQLDisconnect(hdbc);
    if (retcode < 0)
        return -22;
    retcode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    if (retcode < 0)
        return -23;
    retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
    if (retcode < 0)
        return -24;

    return 2;

}


DataMapper::~DataMapper() 
{ 
    cout << disconnectFromDB() << endl; 

    scheduleMapper.clear();
    scheduleMapper.shrink_to_fit();

}


/*

void DataMapper::find1(string str)
{

    SQLWCHAR hours[20];

    strcpy_s((char*)hours, strlen(str.c_str()) + 1, str.c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours, 255, NULL);

    int week = 0;
    char day[20];
    char time[20];
    char group[20];
    int auditory = 0;

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select week, day, time, groupp, auditory from schedule where time = ?", SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 15, NULL);
        retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, time, 15, NULL);
        retcode = SQLBindCol(hstmt, 4, SQL_C_CHAR, group, 15, NULL);
        retcode = SQLBindCol(hstmt, 5, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);

        for (int i = 1;; i++)
        {
            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                cout << endl;

                cout << i << "." << endl;
                cout << "  Номер недели: " << week << endl;

                cout << "  День недели: ";
                for (int k = 0; day[k] != '\0'; k++)
                    cout << day[k];
                cout << endl;

                cout << "  Время: ";
                for (int k = 0; time[k] != '\0'; k++)
                    cout << time[k];
                cout << endl;

                cout << "  Название группы: ";
                for (int k = 0; group[k] != '\0'; k++)
                    cout << group[k];
                cout << endl;

                cout << "  Номер аудитории: " << auditory << endl;

            }
            else
                break;
        }

        cout << endl;

    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
}


bool DataMapper::remove(schedule sched)
{

    cout << sched;

    SQLINTEGER week = sched.getWeekNumber();
    SQLWCHAR day[20];
    SQLWCHAR time[20];
    SQLWCHAR group[20];
    SQLINTEGER auditory = sched.getClassroomNumber();

    strcpy_s((char*)group, strlen(sched.getGroupName().c_str()) + 1, sched.getGroupName().c_str());
    strcpy_s((char*)time, strlen(sched.getTimePeriod().c_str()) + 1, sched.getTimePeriod().c_str());
    strcpy_s((char*)day, strlen(sched.getDayOfWeek().c_str()) + 1, sched.getDayOfWeek().c_str());

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"delete from schedule where week = ? and day = ? and time = ? and groupp = ? and auditory = ?", SQL_NTS);

    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}
*/