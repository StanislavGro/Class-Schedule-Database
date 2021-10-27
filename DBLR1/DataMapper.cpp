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

    int id_auditory = 0;
    int id_group = 0;
    int id_week = 0;
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
    strcpy_s((char*)day , strlen(sched.getDayOfWeek().c_str()) + 1, sched.getDayOfWeek().c_str());
    strcpy_s((char*)auditory, strlen(sched.getClassroomNumber().c_str()) + 1, sched.getClassroomNumber().c_str());



    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO groupp_table(groupp)"
        "VALUES (?)", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, auditory, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from auditory_table where auditory = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_auditory, sizeof(id_auditory), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    //cout << id_auditory << endl;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from groupp_table where groupp = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
   //cout << id_group << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &week, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from week_table where week = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_week, sizeof(id_week), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    //cout << id_week << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, day, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from day_table where day = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_day, sizeof(id_day), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    //cout << id_day << endl;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, timeStart, 255, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, timeEnd, 255, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from time_table where time_start = ? and time_end = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_time, sizeof(id_time), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    //cout << id_time << endl;


    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_week, 0, NULL);
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


bool DataMapper::remove(int number)
{
    int id = 0;
    int id_group = 0;
    vector<int> idVector;

    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select id from schedule", SQL_NTS);
    retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id, sizeof(id), NULL);

    for (int i = 0; ; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Error" << endl;
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            idVector.push_back(id);
        else break;
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    SQLINTEGER removeNumber = idVector[number - 1];
    idVector.clear();
    idVector.shrink_to_fit();

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select groupp from schedule where id = ?", SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &id_group, sizeof(id_group), NULL);
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
            cout << "Ошибка!";
    }
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    //cout << id_group << endl;

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id_group, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"delete from groupp_table where id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &removeNumber, 0, NULL);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"delete from schedule where id = ?;", SQL_NTS);
    retcode = SQLExecute(hstmt);
    if (retcode < 0) return false;
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    return true;
}


void DataMapper::find(string str)
{
    vector<string> result;
    vector<string> hourtable;

    stringstream data(str);

    string line;

    while (getline(data, line, ' '))
        result.push_back(line);

    int n = result.size();

    for (int q = 0; q < n; q++) {
        stringstream data2(result[q]);
        string line2;
        while (getline(data2, line2, '-'))
            hourtable.push_back(line2);
        //cout << hourtable[2*q] << " - " << hourtable[2*q+1] << endl;
    }

    
    SQLWCHAR** hours = new SQLWCHAR* [n*2];

    for (int k = 0; k < n * 2; k++) {
        hours[k] = new SQLWCHAR[hourtable[k].size()];
        strcpy_s((char*)hours[k], strlen(hourtable[k].c_str()) + 1, hourtable[k].c_str());
    }

    SQLRETURN* newRetcode = new SQLRETURN(n*2);

    for (int k = 0; k < n*2; k+=2) {
        newRetcode[k] = SQLBindParameter(hstmt, k + 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours[k], 255, NULL);
        newRetcode[k+1] = SQLBindParameter(hstmt, k + 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours[k+1], 255, NULL);
    }
    //newRetcode[n] = SQLBindParameter(hstmt, n + 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 255, 0, &audit, 255, NULL);


    wstring output = L"select sc.*, w.week, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join week_table as w on w.id = sc.week "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory where (time_start = ? and time_end = ?)";

    //wcout << output << endl;

    for (int k = 0; k < n - 1; k++)
        output += L" or (time_start = ? and time_end = ?)";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    //retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, hours, 255, NULL);

    int week = 0;
    char day[20];
    char time_start[20];
    char time_end[20];
    char group[20];
    int auditory = 0;

    //const char* charOutput = output.c_str();
    //wcout << output << endl;

    //retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLBindCol(hstmt, 7, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, time_start, 20, NULL);
        retcode = SQLBindCol(hstmt, 10, SQL_C_CHAR, time_end, 20, NULL);
        retcode = SQLBindCol(hstmt, 11, SQL_C_CHAR, group, 20, NULL);
        retcode = SQLBindCol(hstmt, 12, SQL_C_SLONG, &auditory, sizeof(auditory), NULL);

        cout << "-----------------------------" << endl;
        cout << "**ЗАНЯТЫЕ АУДИТОРИИ ПО ДНЯМ**" << endl;
        cout << "-----------------------------";


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

                cout << "  Время начала: ";
                for (int k = 0; time_start[k] != '\0'; k++)
                    cout << time_start[k];
                cout << endl;

                cout << "  Время окончания: ";
                for (int k = 0; time_end[k] != '\0'; k++)
                    cout << time_end[k];
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
    }
    cout << "--------------------------------------" << endl;

    cout << "**ВСЕ ОСТАЛЬНЫЕ АУДИТОРИИ СВОБОДНЫЕ!**" << endl;

    cout << "--------------------------------------\n\n";

    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

    result.clear();
    result.shrink_to_fit();

    hourtable.clear();
    hourtable.shrink_to_fit();
    
}


void DataMapper::find(string str, int number)
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
        for (int k = 0; k < n; k++) {
            hourtable[i].push_back(result[k].substr(0, 4));
            hourtable[i].push_back(result[k].substr(6, 10));

            cout << hourtable[i][0] << "\n" << hourtable[i][1] << endl;
        }
    }
    /*
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

    */
}


void DataMapper::creatingTables()
{

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
        "week int unique check (week >= 1 and week <= 18)"
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
        "time_start time,"
        "time_end time,"
        "unique(time_start, time_end)"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    retcode = SQLPrepare(hstmt,
        (SQLWCHAR*)L"create table if not exists schedule ("
        "id serial primary key,"
        "week int references week_table(id) on update cascade on delete cascade,"
        "day int references day_table(id) on update cascade on delete cascade,"
        "time int references time_table(id) on update cascade on delete cascade,"
        "groupp int references groupp_table(id) on update cascade on delete cascade,"
        "auditory int references auditory_table(id) on update cascade on delete cascade"
        "); ", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);


    for (int i = 101; i <= 820; i++) {
        if (i % 100 < 21) {
            retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &i, 0, NULL);
            retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO auditory_table(auditory) VALUES (?)", SQL_NTS);
            retcode = SQLExecute(hstmt);
            retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
        }
        else
            i += 79;
    }
    
    for (int i = 1; i <= 18; i++) {
        retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &i, 0, NULL);
        retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO week_table(week) VALUES (?)", SQL_NTS);
        retcode = SQLExecute(hstmt);
        retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    }
    

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Понедельник')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Вторник')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Среда')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Четверг')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Пятница')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);
    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO day_table(day) VALUES ('Суббота')", SQL_NTS);
    retcode = SQLExecute(hstmt);
    retcode = SQLFreeStmt(hstmt, SQL_CLOSE);

}


vector<schedule> DataMapper::getSchedule()
{
    return scheduleMapper;
}


void DataMapper::printAll()
{

    int id_week = 0;
    int id_day = 0;
    int id_time = 0;
    int id_groupp = 0;
    int id_auditory = 0;

    int week = 0;
    char day [20];
    char time_start[20];
    char time_end[20];
    char group [20];
    char auditory [20];

    //retcode = SQLExecDirect(hstmt, (SQLWCHAR*)L"select week, day, time, groupp, auditory from schedule", SQL_NTS);
    wstring output = L"select sc.*, w.week, d.day, ti.time_start, ti.time_end, gr.groupp, au.auditory "
        "from schedule as sc "
        "join week_table as w on w.id = sc.week "
        "join day_table as d on d.id = sc.day "
        "join time_table as ti on ti.id = sc.time "
        "join groupp_table as gr on gr.id = sc.groupp "
        "join auditory_table as au on au.id = sc.auditory";

    //wcout << output << endl;

    retcode = SQLExecDirect(hstmt, const_cast<SQLWCHAR*>(output.c_str()), SQL_NTS);


    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         
        retcode = SQLBindCol(hstmt, 7, SQL_C_SLONG, &week, sizeof(week), NULL);
        retcode = SQLBindCol(hstmt, 8, SQL_C_CHAR, day, 20, NULL);
        retcode = SQLBindCol(hstmt, 9, SQL_C_CHAR, time_start, 20, NULL);
        retcode = SQLBindCol(hstmt, 10, SQL_C_CHAR, time_end, 20, NULL);
        retcode = SQLBindCol(hstmt, 11, SQL_C_CHAR, group, 20, NULL);
        retcode = SQLBindCol(hstmt, 12, SQL_C_CHAR, auditory, 20, NULL);

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

                cout << "  Время начала: ";
                for (int k = 0; time_start[k] != '\0'; k++)
                    cout << time_start[k];
                cout << endl;

                cout << "  Время окончания: ";
                for (int k = 0; time_end[k] != '\0'; k++)
                    cout << time_end[k];
                cout << endl;

                cout << "  Название группы: ";
                for (int k = 0; group[k] != '\0'; k++)
                    cout << group[k];
                cout << endl;
            
                cout << "  Номер аудитории: ";
                for (int k = 0; auditory[k] != '\0'; k++)
                    cout << auditory[k];
                cout << endl;

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