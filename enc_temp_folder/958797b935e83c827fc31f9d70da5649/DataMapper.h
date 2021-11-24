#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <stdarg.h>
#include "schedule.h"
#include "scheduleData.h"


using namespace::std;

class DataMapper
{
private:

    SQLHENV henv;       // Дескриптор окружения
    SQLHDBC hdbc;       // Дескриптор соединения
    SQLHSTMT hstmt;     // Дескриптор оператора
    SQLRETURN retcode;  // Код возврата

public:

    DataMapper(scheduleData*);
    ~DataMapper();

    int connectToDB();
    int disconnectFromDB();

    void creatingTables();
    void fillAllVectors(scheduleData*);
    void updateIdVectors(scheduleData*, schedule*);
        
    void printAll();
    
    bool insert(schedule*);
    
    int findSchedId(schedule*);
    int findAuditId(Auditory*);
    int findGroupId(Group*);

    bool edit(int*, schedule*);
    bool editByDay(int, string);
    bool editByTime(int, string, string);
    bool editByGroup(int, string);
    bool editByAuditory(int, string);

    bool remove(int*);
    bool removeByGroup(string*);
    bool removeByAuditory(string*);

    void find(string);
    void find(int, int);
};