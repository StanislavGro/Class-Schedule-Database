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

    SQLHENV henv; // ���������� ���������
    SQLHDBC hdbc; // ���������� ����������
    SQLHSTMT hstmt; // ���������� ���������
    SQLRETURN retcode; // ��� ��������

public:

    DataMapper();

    int connectToDB();
    int disconnectFromDB();

    bool insert(schedule);

    ~DataMapper();

};

