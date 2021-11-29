#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <stdarg.h>
#include "schedule.h"

using namespace::std;

class DataMapper
{
private:

    SQLHENV henv;       // Дескриптор окружения
    SQLHDBC hdbc;       // Дескриптор соединения
    SQLHSTMT hstmt;     // Дескриптор оператора
    SQLRETURN retcode;  // Код возврата

public:

    DataMapper();
    ~DataMapper();

    int connectToDB();
    int disconnectFromDB();

    void creatingTables();
    vector<schedule*> fillAllVectors();
    vector<Auditory*> fillAllVectorsFromAuditory();
    vector<Group*> fillAllVectorsFromGroup();

        
    void printAll();
    void printAuditorySchedule();
    void printGroupSchedule();
    
    bool insert(schedule*);
    bool insertToAuditory(Auditory*);
    bool insertToGroup(Group*);
    
    int findSchedId(schedule*);
    int findAuditId(Auditory*);
    int findGroupId(Group*);

    bool edit(int*, schedule*);
    bool editAuditory(int*, Auditory*);
    bool editAuditory(Auditory*, Auditory*);
    bool editGroup(int*, Group*);
    bool editGroup(Group*, Group*);
    bool editByDay(int*, string*);
    bool editByTime(int*, string*, string*);
    bool editByGroup(int*, string*);
    bool editByAuditory(int*, string*);

    bool remove(int*);
    bool removeByGroup(string*);
    bool removeByAuditory(string*);

    void find(string);
    void find(int, int);
};