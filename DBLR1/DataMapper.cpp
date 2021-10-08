#include "DataMapper.h"

DataMapper::DataMapper()
{
    cout << connectToDB() << endl;
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
    SQLINTEGER id = sched.getID();
    SQLWCHAR group[100];

    strcpy_s((char*)group, strlen(sched.getGroupName().c_str())+1, sched.getGroupName().c_str());
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &id, 0, NULL);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 255, 0, group, 255, NULL);

    retcode = SQLPrepare(hstmt, (SQLWCHAR*)L"INSERT INTO schedule VALUES (?, ?)", SQL_NTS);

    retcode = SQLExecute(hstmt);
    return true;
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