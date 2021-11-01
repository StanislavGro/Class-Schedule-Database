#pragma once
#include<iostream>
#include<vector>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include<stdarg.h>
#include"schedule.h"

using namespace::std;

class DataMapper
{
private:

    vector<schedule> scheduleMapper;

    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

public:

    DataMapper();
    int connectToDB();
    int disconnectFromDB();
    ~DataMapper();

    void creatingTables();    
    
    vector<schedule> getSchedule();
    
    void printAll();
    
    bool insert(schedule);

    bool edit(int, schedule);
    bool editByDay(int, string);
    bool editByTime(int, string, string);
    bool editByGroup(int, string);
    bool editByAuditory(int, string);

    bool remove(int);
    bool removeByGroup(string);
    bool removeByAuditory(string);
    
    void find(string);
    void find(int, int);

};

