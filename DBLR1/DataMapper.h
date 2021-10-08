#pragma once
#include<iostream>
#include<vector>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
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

    bool insert(schedule);

    ~DataMapper();

};

