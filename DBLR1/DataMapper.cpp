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