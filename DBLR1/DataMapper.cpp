#include "DataMapper.h"
#include<iostream>
#include<vector>

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
   
    SQLINTEGER auditory = sched.getClassroomNumber();
    SQLWCHAR group[20];
    SQLWCHAR time[20];
    SQLWCHAR day[20];
    SQLINTEGER week = sched.getWeekNumber();

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


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time, 255, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO schedule(auditory, groupp, week, day, time )"
                        "VALUES (?, ?, ?, ?, ?)", SQL_NTS);
    retcode = SQLExecute(hstmt);

    return true;
}

void DataMapper::creatingTables()
{

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "auditory int,"
        "groupp varchar(20),"
        "week int,"
        "day varchar(20),"
        "time varchar(20)"
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
        "groupp varchar(15) unique"
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
        "day varchar(10) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time_table("
        "id serial primary key,"
        "time varchar(15) unique"
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

void DataMapper::download()
{
}

vector<schedule> DataMapper::getSchedule()
{
    return scheduleMapper;
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