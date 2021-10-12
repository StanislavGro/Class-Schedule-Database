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
    SQLINTEGER id = sched.getID();
    SQLWCHAR group[100];

    strcpy_s((char*)group, strlen(sched.getGroupName().c_str())+1, sched.getGroupName().c_str());
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO schedule VALUES (?, ?)", SQL_NTS);

    retcode = SQLExecute(hstmt);
    return true;
}

void DataMapper::creatingTables()
{

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "auditory int,"
        "groupp varchar(15),"
        "week int,"
        "day varchar(10),"
        "time varchar(15),"
        "id_Auditory int,"
        "id_Group int,"
        "id_Week int,"
        "id_Day int,"
        "id_Time int"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory_table("
        "id serial primary key,"
        "auditory int"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists groupp_table("
        "id serial primary key,"
        "groupp varchar(15)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists week_table("
        "id serial primary key,"
        "week int"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day_table("
        "id serial primary key,"
        "day varchar(10)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time_table("
        "id serial primary key,"
        "time varchar(15)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time_table("
        "id serial primary key,"
        "time varchar(15)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"alter table schedule add constraint sc_au_for_key foreign key(id_Auditory)" 
        "references auditory_table(id);", SQL_NTS);
    retcode = SQLExecute(hstmt);
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