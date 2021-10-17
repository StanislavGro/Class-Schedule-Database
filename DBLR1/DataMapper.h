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
    ~DataMapper();

    void creatingTables();

    int connectToDB();
    int disconnectFromDB();
    
    vector<schedule> getSchedule();
    
    void printAll();
    
    bool insert(schedule);
    bool edit(int, schedule);
    bool remove(int);
    
    //void find1(string);
    void find(int, string);
    void find(int, string, int);

};

