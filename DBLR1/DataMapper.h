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

    SQLHENV henv; // ���������� ���������
    SQLHDBC hdbc; // ���������� ����������
    SQLHSTMT hstmt; // ���������� ���������
    SQLRETURN retcode; // ��� ��������

public:

    DataMapper();
    ~DataMapper();

    void creatingTables();

    int connectToDB();
    int disconnectFromDB();
    
    vector<schedule> getSchedule();
    
    void printAll();
    
    bool insert(schedule);
    bool edit(int);
    bool edit(schedule);
    bool remove(int);
    bool remove(schedule);
    
    void find(string ,...); //����� �� �������� ����� � ������� �������� (�����: ���������, ������, ����, ����)
    void find(int, int); //����� �� �������� ����� ����� � ��������� ������ (�����: ���������, ������, ����, ����)

};

