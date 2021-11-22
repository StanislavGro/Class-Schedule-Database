#include "DataMapper.h"
#include<iostream>
#include<vector>
#include <sstream>

using namespace::std;

DataMapper::DataMapper() { 

    if (connectToDB() == 1)
        creatingTables();
    else
        cout << "!- Какая-то неизвестная ошибка!" << endl;

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

    scheduleVectorMapper.getSchedule().push_back(sched);


    int id_auditory = 0;
    int id_group = 0;
    int id_day = 0;
    int id_time = 0;

   
    SQLINTEGER week = sched.getWeekNumber();
    SQLWCHAR day[20];
    SQLWCHAR timeStart[20];
    SQLWCHAR timeEnd[20];
    SQLWCHAR group[20];
    SQLWCHAR auditory[20];

    strcpy_s((char*)group, strlen(sched.getGroupName().c_str()) + 1, sched.getGroupName().c_str());
    strcpy_s((char*)timeStart, strlen(sched.getTimeStart().c_str()) + 1, sched.getTimeStart().c_str());
    strcpy_s((char*)timeEnd, strlen(sched.getTimeEnd().c_str()) + 1, sched.getTimeEnd().c_str());
    strcpy_s((char*)day, strlen(sched.getDayOfWeek().c_str()) + 1, sched.getDayOfWeek().c_str());
    strcpy_s((char*)auditory, strlen(sched.getAuditory().getAuditoryName().c_str()) + 1, sched.getAuditory().getAuditoryName().c_str());


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO groupp_table(groupp)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from groupp_table where groupp = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    //cout << id_group << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory_table(auditory)"
        " VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    //cout << id_auditory << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from auditory_table where auditory = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from day_table where day = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    //cout << id_day << endl;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, timeStart, 255, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, timeEnd, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from time_table where time_start = ? and time_end = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    //cout << id_time << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_auditory, 0, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO schedule(week, day, time, groupp, auditory)"
                        "VALUES (?, ?, ?, ?, ?)", SQL_NTS);
    retcode = SQLExecute(hstmt);

    return true;
}


bool DataMapper::edit(int number, schedule sched)
{
    remove(number);
    insert(sched);

    return true;
}


bool DataMapper::editByDay(int number, string dayStr)
{
    int id_day = 0;
    SQLWCHAR day[20];
    strcpy_s((char*)day, strlen(dayStr.c_str()) + 1, dayStr.c_str());

    int id = 0;
    vector<int> idVector;

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS); 
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    SQLINTEGER removeNumber = idVector[number - 1];
    idVector.clear();
    idVector.shrink_to_fit();

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from day_table where day = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_day, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"update schedule set day = ? where id = ?", SQL_NTS);
    
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;

}


bool DataMapper::editByTime(int number, string timeStartStr, string timeEndStr)
{

    int id_time = 0;
    SQLWCHAR time_start[20];
    SQLWCHAR time_end[20];
    strcpy_s((char*)time_start, strlen(timeStartStr.c_str()) + 1, timeStartStr.c_str());
    strcpy_s((char*)time_end, strlen(timeEndStr.c_str()) + 1, timeEndStr.c_str());


    int id = 0;
    vector<int> idVector;

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS); 
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    SQLINTEGER removeNumber = idVector[number - 1];
    idVector.clear();
    idVector.shrink_to_fit();

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time_start, 255, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, time_end, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from time_table where time_start = ? and time_end = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }
    
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_time, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"update schedule set time = ? where id = ?", SQL_NTS);

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;
}


bool DataMapper::editByGroup(int number, string groupStr)
{

    int id_group = 0;
    SQLWCHAR group[20];
    strcpy_s((char*)group, strlen(groupStr.c_str()) + 1, groupStr.c_str());


    int id = 0;
    vector<int> idVector;

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    SQLINTEGER removeNumber = idVector[number - 1];
    idVector.clear();
    idVector.shrink_to_fit();


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO groupp_table(groupp)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from groupp_table where groupp = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"update schedule set groupp = ? where id = ?", SQL_NTS);

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;
}


bool DataMapper::editByAuditory(int number, string auditoryStr)
{

    int id_auditory = 0;
    SQLWCHAR auditory[20];
    strcpy_s((char*)auditory, strlen(auditoryStr.c_str()) + 1, auditoryStr.c_str());


    int id = 0;
    vector<int> idVector;

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    SQLINTEGER removeNumber = idVector[number - 1];
    idVector.clear();
    idVector.shrink_to_fit();

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory_table(auditory)"
        " VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from auditory_table where auditory = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Ошибка!";
    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_auditory, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"update schedule set auditory = ? where id = ?", SQL_NTS);

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    return true;
}


bool DataMapper::remove(int number)
{
    int id = 0;
    int id_group = 0;
    vector<int> idVector;

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);    
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "!- Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }
    
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    //cout << "NUMBER = " << number << endl;
    //cout << "VECTOR = ";
    /*for (int i = 0; i < idVector.size(); i++)
        cout << idVector[i] << " ";
    cout << endl;*/

    //cout << idVector[number - 1] << endl;
    SQLINTEGER removeNumber = idVector[number - 1];

    /*retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select groupp from schedule where id = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    cout << id_group << endl;*/


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"delete from schedule where id = ?", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    idVector.clear();
    idVector.shrink_to_fit();

    return true;
}


bool DataMapper::removeByGroup(string groupStr)
{

    SQLWCHAR group[20];
    strcpy_s((char*)group, strlen(groupStr.c_str()) + 1, groupStr.c_str());


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"delete from groupp_table where groupp = ?", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    return true;
}


bool DataMapper::removeByAuditory(string auditoryStr)
{

    SQLWCHAR group[20];
    strcpy_s((char*)group, strlen(auditoryStr.c_str()) + 1, auditoryStr.c_str());


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"delete from auditory_table where auditory = ?", SQL_NTS);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    return true;
}


void DataMapper::find(string str)
{
    vector<string> result, hourtable, auditForPrint;
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

    for (int i = 0; i < n; i++) {
        data.str(string()); //обычная очитска
        data.clear();       //сброс всех флагов ошибок
        line.clear();
        data.str(result[i]);
        while (getline(data, line, '-'))
            hourtable.push_back(line);
        //cout << hourtable[2*i] << " - " << hourtable[2*i+1] << endl;
    }
    
    SQLWCHAR** SQLHOURS = new SQLWCHAR* [n*2]; //т.к из одного промежутка получается 2 строки

    for (int i = 0; i < n * 2; i++) {
        SQLHOURS[i] = new SQLWCHAR[hourtable[i].size()];
        strcpy_s((char*)SQLHOURS[i], strlen(hourtable[i].c_str()) + 1, hourtable[i].c_str());
    }

    SQLRETURN* SQLRETCODE = new SQLRETURN(n*2); //т.к в 2р больше бинд параметров

    for (int i = 0; i < n*2; i+=2) {
        SQLRETCODE[i] = SQLBindParameter(hstmt, i + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, SQLHOURS[i], 255, NULL);
        SQLRETCODE[i+1] = SQLBindParameter(hstmt, i + 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, SQLHOURS[i+1], 255, NULL);
    }

    /*wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory where (time_start = ? and time_end = ?)";*/

    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory where (time_start = ? and time_end = ?)";

    for (int i = 0; i < n - 1; i++)
        output += L" or (time_start = ? and time_end = ?)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    int week = 0;
    char day[20] = "";
    char time_start[20] = "";
    char time_end[20] = "";
    char group[20] = "";
    char auditory[20] = "";


    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, time_start, 20, NULL);
        retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, time_end, 20, NULL);
        retcode = SQLBindCol(hstmt, 10, SQL_C_CHAR, group, 20, NULL);
        retcode = SQLBindCol(hstmt, 11, SQL_C_CHAR, auditory, 20, NULL);

        cout << endl;
        cout << ">> ЗАНЯТЫЕ АУДИТОРИИ В ЭТО ВРЕМЯ" << endl;


        for (int i = 1;; i++)
        {
            retcode = SQLFetch(hstmt);

            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "!- Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                cout << endl;

                cout << "  " <<i << "." << endl;
                cout << "   Номер недели: " << week << endl;

                cout << "   День недели: ";
                for (int k = 0; day[k] != '\0'; k++)
                    cout << day[k];
                cout << endl;
                  
                cout << "   Время начала: ";
                for (int k = 0; time_start[k] != '\0'; k++)
                    cout << time_start[k];
                cout << endl;

                cout << "   Время окончания: ";
                for (int k = 0; time_end[k] != '\0'; k++)
                    cout << time_end[k];
                cout << endl;

                cout << "   Название группы: ";
                for (int k = 0; group[k] != '\0'; k++)
                    cout << group[k];
                cout << endl;

                cout << "   Номер аудитории: ";
                for (int k = 0; auditory[k] != '\0'; k++)
                    cout << auditory[k];
                cout << endl;

            }
            else
                break;
        }
    
    }

    //SQLWCHAR** SQLHOURS = new SQLWCHAR * [n * 2]; //т.к из одного промежутка получается 2 строки

    //for (int i = 0; i < n * 2; i++) {
    //    SQLHOURS[i] = new SQLWCHAR[hourtable[i].size()];
    //    strcpy_s((char*)SQLHOURS[i], strlen(hourtable[i].c_str()) + 1, hourtable[i].c_str());
    //}

    //SQLRETURN* SQLRETCODE = new SQLRETURN(n * 2); //т.к в 2р больше бинд параметров

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    
    for (int i = 0; i < n * 2; i += 2) {
        SQLRETCODE[i] = SQLBindParameter(hstmt, i + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, SQLHOURS[i], 255, NULL);
        SQLRETCODE[i + 1] = SQLBindParameter(hstmt, i + 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, SQLHOURS[i + 1], 255, NULL);
    }    

    wstring output1 = L"select sc.week, d.day, ti.time_start, ti.time_end, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join auditory_table as au on au.id = sc.auditory where (time_start = ? and time_end = ?)";

    for (int i = 0; i < n - 1; i++)
        output1 += L" or (time_start = ? and time_end = ?)";

    //wcout << output1 << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output1.c_str()), SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 5, SQL_C_CHAR, auditory, 20, NULL);

        cout << endl;
        cout << ">> Аудитория(-и) ";

        for (int i = 1;; i++)
        {

            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "!- Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                auto iterator = std::find(auditForPrint.begin(), auditForPrint.end(), string(auditory));

                if (iterator == auditForPrint.end()) {
                    i != 1 ? cout << ", " : cout;

                    for (int k = 0; auditory[k] != '\0'; k++)
                        cout << auditory[k];
                    auditForPrint.push_back(auditory);
                }

                auto it = freeAuditory.begin();
                for (int k = 0; k < week-1; k++)
                    it++;
                //cout << std::distance(freeAuditory.begin(), it) << endl;
                auto it2 = std::find(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), freeAuditory[std::distance(freeAuditory.begin(), it)].end(), string(day));
                //cout << std::distance(freeAuditory[std::distance(freeAuditory.begin(), it)].begin(), it2) << endl;
                if (it2 != freeAuditory[std::distance(freeAuditory.begin(), it)].end())
                    freeAuditory[std::distance(freeAuditory.begin(), it)].erase(it2);
            }
            else {
                cout << " в течении семестра свободна(-ы) на:" << endl;
                break;
            }

        }

        cout << endl;

        for (int i = 0; i < freeAuditory.size(); i++) {
            cout << ">> " << i+1 << " неделе:";

            for (int k = 0; k < freeAuditory[i].size(); k++) {
                cout << " " <<freeAuditory[i][k];
                k != freeAuditory[i].size() - 1 ? cout << "," : cout << "."<<endl;
            }
        }

        cout << endl;
        cout << ">> ВСЕ ОСТАЛЬНЫЕ АУДИТОРИИ В ЗАДАННЫЕ ЧАСЫ В ТЕЧЕНИИ ВСЕГО СЕМЕСТРА СВОБОДНЫЕ!" << endl;
        cout << endl;

    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    result.clear();
    result.shrink_to_fit();

    auditForPrint.clear();
    auditForPrint.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();

    freeAuditory.clear();
    freeAuditory.shrink_to_fit();
    
}


void DataMapper::find(int hoursNumber, int weekNumber)
{

    vector<string> auditories, daysOfWeek;
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

    int week = 0;
    char day[20] = "";
    char time[20] = "";
    char group[20] = "";
    char auditory[20] = "";

    int day_id = 0;
    int time_id = 0;


    SQLINTEGER sqlWeek = weekNumber;
    bool isFind = false;

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select(auditory) from auditory_table", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, auditory, 20, NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            auditories.push_back(auditory);
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    for (int i = 1; isFind == false; i++) {

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

        SQLWCHAR auditory[20];
        //cout << auditories[i - 1] << endl;
        strcpy_s((char*)auditory, strlen(auditories[i - 1].c_str()) + 1, auditories[i - 1].c_str());

        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &sqlWeek, 0, NULL);
        retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);

        wstring output = L"select sc.day, sc.time "
            "from schedule as sc "
            "join auditory_table as au on au.id = sc.auditory where sc.week = ? and au.auditory = ?";

        //wcout << output << endl;

        retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

            retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &day_id, sizeof(day_id), NULL);
            retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &time_id, sizeof(time_id), NULL);

            for (int k = 1;; k++)
            {
                retcode = SQLFetch(hstmt);
                if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                    cout << "!- Ошибка!";
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                    auto it = hourtable.begin();
                    for (int j = 0; j < day_id - 1; j++)
                        it++;

                    //cout << std::distance(hourtable.begin(), it) << endl;
                    auto it2 = hourtable[std::distance(hourtable.begin(), it)].begin();

                    for (int j = 0; j < time_id - 1; j++)
                        it2++;

                    if (it2 != hourtable[std::distance(hourtable.begin(), it)].end()) {
                        *it2 = "";
                    }
                }
                else
                    break;
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

                lessons = hoursNumber * 60 / 90;

                cout << endl;
                cout << ">> Для аудитории " << auditories[i-1];
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

            retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
            retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
            retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
        }

        hourtable.clear();
        hourtable.shrink_to_fit();
    }


    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    auditories.clear();
    auditories.shrink_to_fit();

    daysOfWeek.clear();
    daysOfWeek.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();

}


void DataMapper::creatingTables()
{

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists auditory_table("
        "id serial primary key,"
        "auditory varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists groupp_table("
        "id serial primary key,"
        "groupp varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists day_table("
        "id serial primary key,"
        "day varchar(20) unique"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists time_table("
        "id serial primary key,"
        "time_start time,"
        "time_end time,"
        "unique(time_start, time_end)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "week int check (week >= 1 and week <= 18),"
        "day int references day_table(id) on update cascade on delete cascade,"
        "time int references time_table(id) on update cascade on delete cascade,"
        "groupp int references groupp_table(id) on update cascade on delete cascade,"
        "auditory int references auditory_table(id) on update cascade on delete cascade,"
        "unique(week, day, time, auditory)); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Понедельник')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Вторник')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Среда')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Четверг')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Пятница')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Суббота')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('8:30', '10:00')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('10:15', '11:45')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('12:00', '13:30')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('14:00', '15:30')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('15:45', '17:15')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('17:30', '19:00')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO time_table(time_start,  time_end) VALUES ('19:15', '20:45')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

}


//scheduleVector DataMapper::getSchedule() { return scheduleVectorMapper; }


void DataMapper::printAll()
{

    bool isEmpty = true;

    int id_week = 0;
    int id_day = 0;
    int id_time = 0;
    int id_groupp = 0;
    int id_auditory = 0;

    int week = 0;
    char day [20] = "";
    char time_start[20] = "";
    char time_end[20] = "";
    char group[20] = "";
    char auditory[20] = "";

    //retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select week, day, time, groupp, auditory from schedule", SQL_NTS);
    wstring output = L"select sc.*, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory "
        //"order by (sc.week, d.day, ti.time_start, ti.time_end, au.auditory)";
        "order by(sc.week, sc.day, ti.time_start, ti.time_end, au.auditory)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);


    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         
        retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 7, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, time_start, 20, NULL);
        retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, time_end, 20, NULL);
        retcode = SQLBindCol(hstmt, 10, SQL_C_CHAR, group, 20, NULL);
        retcode = SQLBindCol(hstmt, 11, SQL_C_CHAR, auditory, 20, NULL);

        for (int i = 1;; i++)
        {
            retcode = SQLFetch(hstmt);
            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                cout << "!- Ошибка!";
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                isEmpty = false;

                cout << endl;

                cout << "  " << i << "." << endl;
                cout << "    Номер недели: " << week << endl;

                cout << "    День недели: ";
                for (int k = 0; day[k] != '\0'; k++)
                    cout << day[k];
                cout << endl;

                cout << "    Время начала: ";
                for (int k = 0; time_start[k] != '\0'; k++)
                    cout << time_start[k];
                cout << endl;

                cout << "    Время окончания: ";
                for (int k = 0; time_end[k] != '\0'; k++)
                    cout << time_end[k];
                cout << endl;

                cout << "    Название группы: ";
                for (int k = 0; group[k] != '\0'; k++)
                    cout << group[k];
                cout << endl;
            
                cout << "    Номер аудитории: ";
                for (int k = 0; auditory[k] != '\0'; k++)
                    cout << auditory[k];
                cout << endl;

            }
            else {
                if (isEmpty) {
                    cout << "\n!- Таблица пуста!\n";
                }
                break;
            }
        }

        cout << endl;

    }

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLFreeStmt(hstmt, SQL_UNBIND);
    retcode = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
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
    system("color 04");
    cout << ">> Ну пока)" << endl; 

    scheduleVectorMapper.getSchedule().clear();
    scheduleVectorMapper.getSchedule().shrink_to_fit();

}