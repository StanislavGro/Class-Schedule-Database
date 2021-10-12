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

    DataMapper dataMapper;

    //dataMapper.insert(*(new schedule(2, 315, 5, "AVT-819", "14:00-15:30", "Monday")));

    /*vector<schedule> vector;
    
    schedule sced;

    cin >> sced;

    vector.push_back(sced);
    cout << vector[vector.size()-1];*/


}
