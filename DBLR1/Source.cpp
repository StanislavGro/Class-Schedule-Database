#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "schedule.h"
#include "DataMapper.h"
#include "scheduleData.h"

using namespace::std;

void GetConsBuff(int&, int&);

void CenterString(string&, const size_t&);

void console() {

	string mainStr = "***���������� �������!***";
	CenterString(mainStr, 25u);
	
	cout << "   1. �������� ������\n" << endl;
	cout << "   2. ������� ������ �� ������" << endl;
	cout << "   3. ������� ������ �� ������" << endl;
	cout << "   4. ������� ������ �� ���������\n" << endl;
	cout << "   5. ������������� ������ �� ������" << endl;
	cout << "   6. ������������� ���� � ������ �� ������" << endl;
	cout << "   7. ������������� ����� � ������ �� ������" << endl;
	cout << "   8. ������������� ������ � ������ �� ������" << endl;
	cout << "   9. ������������� ��������� � ������ �� ������\n" << endl;
	cout << "   10. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
	cout << "   11. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������\n" << endl;
	cout << "   12. �������� �������" << endl;
	cout << "   13. ������� ������" << endl;
	cout << "   14. ���������� �����\n\n";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0A");

    DataMapper dataMapper;
	scheduleData scheduleDataVector;

	console();

	int s = 1, func;

	while (s != 0) {

		cout << ">> �������� ����������� ��������: ";
		cin >> func;

		switch (func) {
		case 1: {

			schedule sch;

			int schedId = 0;
			int auditId = 0;
			int groupId = 0;

			system("cls");

			cout << ">> ������� ������, ����, ����� ������, ����� �����, ������ � ���������: " << endl;
			cout << ">> ";
			cin >> sch;
			cout << "\n" << sch;

			dataMapper.insert(&sch);

			schedId = dataMapper.findSchedId(&sch);
			auditId = dataMapper.findAuditId(sch.getAuditory());
			groupId = dataMapper.findGroupId(sch.getGroup());

			if (schedId > 0 && auditId > 0 && groupId > 0) {
				cout << "!- ������� � �� ��������� �������!" << endl;
				sch.setID(schedId);
				if (scheduleDataVector.insertSchedule(new schedule(sch))) {
					cout << "!- ������� � �� ��������� �������!" << endl;
					for (int i = 0; i < scheduleDataVector.getAuditoryVector().size(); i++)
						if ((scheduleDataVector.getAuditoryVector())[i] == *(sch.getAuditory())) {
							scheduleDataVector.removeOneInAuditory(sch.getAuditory());
							break;
						}
					scheduleDataVector.insertAuditory(new Auditory(auditId, sch.getAuditory()->getAuditoryName()));
					
					for (int i = 0; i < scheduleDataVector.getGroupVector().size(); i++)
						if ((scheduleDataVector.getGroupVector())[i] == *(sch.getGroup())) {
							scheduleDataVector.removeOneInGroup(sch.getGroup());
							break;
						}
					scheduleDataVector.insertGroup((new Group(groupId, sch.getGroup()->getGroupName())));

				}
				else
					cout << "!- ������ ������� � ��!" << endl;
			}
			else 
				cout << "!- ��������� ������ ������� � ��!" << endl;
			
			system("pause");

			system("cls");

			console();

			break;
		}
		/*
		case 2: {

			int deleteNumber, schedId = 0, auditId = 0, int groupId = 0;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> deleteNumber;

			dataMapper.remove(deleteNumber);

			schedId = scheduleDataVector.removeInSchedule(deleteNumber);
			auditId = scheduleDataVector.removeOneInAuditory()
			groupId = dataMapper.findGroupId(sch.getGroup());

			if (dataMapper.remove(deleteNumber))
				cout << "!- �������� ���������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;

		}
		case 3: {

			string deleteGroupp;

			cout << "   ������� ������: ";
			cin >> deleteGroupp;

			if (dataMapper.removeByGroup(deleteGroupp))
				cout << "!- �������� ���������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;

		}
		case 4: {

			string deleteAuditory;

			cout << ">> ������� ���������: ";
			cin >> deleteAuditory;

			if (dataMapper.removeByAuditory(deleteAuditory))
				cout << "!- �������� ���������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;

		}
		case 5: {

			schedule sch;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� �����: ������, ����, ����� ������, ����� ���������, ������ � ���������:" << endl;
			cout << ">> ";
			cin >> sch;

			if (dataMapper.edit(editNumber, sch))
				cout << "!- ������ ��������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;
		}
		case 6: {

			string dayStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ���� ������: ";
			cin >> dayStr;

			if (dataMapper.editByDay(editNumber, dayStr))
				cout << "!- ������ ��������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;
		}
		case 7: {

			string dayStartStr, dayEndStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ������: ";
			cin >> dayStartStr;
			cout << ">> ������� ����� ���������: ";
			cin >> dayEndStr;

			if (dataMapper.editByTime(editNumber, dayStartStr, dayEndStr))
				cout << "!- ������ ��������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;
		}
		case 8: {

			string groupStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ������: ";
			cin >> groupStr;

			if (dataMapper.editByGroup(editNumber, groupStr))
				cout << "!- ������ ��������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;
		}
		case 9: {

			string auditoryStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ���������: ";
			cin >> auditoryStr;

			if (dataMapper.editByAuditory(editNumber, auditoryStr))
				cout << "!- ������ ��������!" << endl;
			else
				cout << "!- ��������� ������!" << endl;

			break;
		}
		case 10: {

			string hours;
			int audit;

			cout << ">> ������� ���������� �������: ";

			cin.get();
			getline(cin, hours);

			dataMapper.find(hours);

			break;

		}
		case 11: {

			int numberWeek, numberHours;

			cout << ">> ������� ����� �����: ";
			cin >> numberHours;

			cout << ">> ������� ����� ������: ";
			cin >> numberWeek;

			dataMapper.find(numberHours, numberWeek);

			break;
		}
		*/
		case 12: {

			dataMapper.printAll();

			break;
		}
		case 13: {

			system("cls");

			console();

			break;
		}
		case 14: {
			s = 0;
			break;
		}
		default: {
			cout << "!- ��������� �������!" << endl;
			break;
		}
		}

	}

	return 0;
}

//��������� �������� ���� ������� ��� ���������
void GetConsBuff(int& x, int& y)
{
	HANDLE hWndConsole;
	if (hWndConsole = GetStdHandle(-12))
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
		{
			x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
			y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
		}
		else
			printf("Error: %d\n", GetLastError());
	}
	else
		printf("Error: %d\n", GetLastError());
}

void CenterString(string& s, const size_t& width)
{
	int buffer_x_size, buffer_y_size;
	GetConsBuff(buffer_x_size, buffer_y_size);
	size_t left_bord = (buffer_x_size - width) / 2.;
	for (;;)
	{
		cout << setw(left_bord) << "";
		cout << s.substr(0u, width) << endl;
		s.erase(s.begin(), s.begin() + (s.size() < width ? s.size() : width));
		if (s.empty())
			break;
	}
}