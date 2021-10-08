#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include "schedule.h"
#include "DataMapper.h"

using namespace::std;

int main() {

    setlocale(LC_ALL, "Rus");

    vector<schedule> vector;

    schedule sc(1, 814, 2, "АВТ-815", "14:00-15:30", "Monday");

    vector.push_back(schedule(1, 814, 2, "АВТ-815", "14:00-15:30", "Monday"));
    vector.push_back(schedule(2, 318, 8, "АВТ-819", "8:30-10:00", "Tuesday"));
    vector.push_back(schedule(3, 814, 2, "АВТ-815", "14:00-15:30", "Monday"));

    for (int i = 0; i < vector.size(); i++)
        vector[i].print();

    
    cin >> vector[0];
    cout << vector[0];

    /*
    SQLHENV henv; // Дескриптор окружения
    SQLHDBC hdbc; // Дескриптор соединения
    SQLHSTMT hstmt; // Дескриптор оператора
    SQLRETURN retcode; // Код возврата

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

    */

}
