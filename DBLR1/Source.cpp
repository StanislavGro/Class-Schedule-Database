#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Auditory.h"
#include "schedule.h"
#include "DataMapper.h"
#include "scheduleData.h"

using namespace::std;

void GetConsBuff(int&, int&);

void CenterString(string&, const size_t&);


void console() {

	cout << endl;

	string mainStr = "***���������� �������!***";
	CenterString(mainStr, 25u);
	
	cout << "   1. �������� ������ � ������� ����������" << endl;
	cout << "   2. �������� ������ � ������� ���������" << endl;
	cout << "   3. �������� ������ � ������� �����\n" << endl;

	cout << "   4. ������� ������ � ������� ���������� �� ������" << endl;
	cout << "   5. ������� ������ � ������� ����� �� ������" << endl;
	cout << "   6. ������� ������ � ������� ��������� �� ���������\n" << endl;

	cout << "   7. ������������� ��� ������ �� ������" << endl;
	cout << "   8. ������������� ���� � ������� ���������� �� ������" << endl;
	cout << "   9. ������������� ����� � ������� ���������� �� ������" << endl;
	cout << "   10. ������������� ������ � ������� ���������� �� ������" << endl;
	cout << "   11. ������������� ��������� � ������� ���������� �� ������" << endl;
	cout << "   12. ������������� ��������� � ������� ��������� �� ������" << endl;
	cout << "   13. ������������� ��������� � ������� ��������� �� ��������" << endl;
	cout << "   14. ������������� ������ � ������� ����� �� ������" << endl;
	cout << "   15. ������������� ������ � ������� ����� �� ��������\n" << endl;

	cout << "   16. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
	cout << "   17. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������\n" << endl;

	cout << "   18. �������� ������� ����������" << endl;
	cout << "   19. �������� ������� ���������" << endl;
	cout << "   20. �������� ������� �����\n" << endl;

	cout << "   21. ������� ������" << endl;
	cout << "   22. ���������� �����\n\n";
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0A");

	scheduleData scheduleDataVector;

	console();

	int s = 1, func;

	while (s != 0) {

		cout << ">> �������� ����������� ��������: ";
		cin >> func;

		switch (func) {
		case 1: {

			schedule sch;

			system("cls");

			cout << ">> ������� ������, ����, ����� ������, ����� �����, ������ � ���������: " << endl;
			cout << ">> ";
			cin >> sch;
			cout << "\n" << sch;

			//1 ����������� 8:30 10:00 ���-815 3-2

			if (scheduleDataVector.ScheduleVectorCheck(sch)) {
				cout << "!- ������� � ������ ������ �������!" << endl;
				if (scheduleDataVector.insertSchedule(sch))
					cout << "!- ������� � �� ������ �������!" << endl;
				else
					cout << "!- ������ ������� � ��" << endl;
			}
			else
				cout << "!- ������ ������� � ������" << endl;
			
			cout << endl;

			system("pause");

			system("cls");

			console();

			break;
		}
		case 2: {

			Auditory auditory;

			system("cls");

			cout << ">> ������� ���������: " << endl;
			cout << ">> ";
			cin >> auditory;
			cout << "\n" << auditory;

			//3-2

			scheduleDataVector.insertAuditoryAndDB(auditory);

			system("pause");

			system("cls");

			console();

			break;
		}
		case 3: {

			Group group;

			system("cls");

			cout << ">> ������� ������: " << endl;
			cout << ">> ";
			cin >> group;
			cout << "\n" << group;

			//����

			scheduleDataVector.insertGroupAndDB(group);

			system("pause");

			system("cls");

			console();

			break;
		}
		case 4: {

			int deleteNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> deleteNumber;

			if (scheduleDataVector.removeInSchedule(deleteNumber))
				cout << "!- ������ ��� ������" << endl;
			else
				cout << "!- ������! ������ �� ��� ������" << endl;

			break;

		}
		case 5: {

			string deleteGroupp;

			cout << "   ������� ������: ";
			cin >> deleteGroupp;

			Group group(deleteGroupp);

			scheduleDataVector.removeOneInGroup(group);

			break;
		}
		case 6: {

			string deleteAuditory;

			cout << ">> ������� ���������: ";
			cin >> deleteAuditory;

			Auditory auditory(deleteAuditory);

			scheduleDataVector.removeOneInAuditory(auditory);

			break;
		}
		case 7: {

			schedule sch;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� �����: ������, ����, ����� ������, ����� ���������, ������ � ���������:" << endl;
			cout << ">> ";
			cin >> sch;

			//1 ����������� 8:30 10:00 ���-815 3-2

			if (scheduleDataVector.editAllSchedule(editNumber, sch))
				cout << "!- " << editNumber << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << editNumber << " ��������" << endl;

			break;
		}
		case 8: {

			string dayStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ���� ������: ";
			cin >> dayStr;

			if (dayStr == "�����������" || dayStr == "�������" || dayStr == "�����" || dayStr == "�������" || dayStr == "�������" || dayStr == "�������") {
				if (scheduleDataVector.editByDayInSchedule(editNumber, dayStr))
					cout << "!- " << editNumber << " ������� ��� �������" << endl;
				else
					cout << "!- ������ ��������� " << editNumber << " ��������" << endl;
			}
			else
				cout << "!- ���������� ��� �� ����������! " << endl;

			break;
		}
		case 9: {

			string timeStartStr, timeEndStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ������: ";
			cin >> timeStartStr;
			cout << ">> ������� ����� ���������: ";
			cin >> timeEndStr;

			if ((timeStartStr == "8:30" && timeEndStr == "10:00") ||
				(timeStartStr == "10:15" && timeEndStr == "11:45") ||
				(timeStartStr == "12:00" && timeEndStr == "13:30") ||
				(timeStartStr == "14:00" && timeEndStr == "15:30") ||
				(timeStartStr == "15:45" && timeEndStr == "17:15") ||
				(timeStartStr == "17:30" && timeEndStr == "19:00") ||
				(timeStartStr == "19:15" && timeEndStr == "20:45")) {
				if (scheduleDataVector.editByTimeInSchedule(editNumber, *(new Time(timeStartStr, timeEndStr))))
					cout << "!- " << editNumber << " ������� ��� �������" << endl;
				else
					cout << "!- ������ ��������� " << editNumber << " ��������" << endl;
			}
			else
				cout << "!- ������! ������� ������������ ���������� " << endl;

			break;
		}
		case 10: {

			string groupStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ������: ";
			cin >> groupStr;

			if (scheduleDataVector.editByGroupInSchedule(editNumber, *(new Group(groupStr))))
				cout << "!- " << editNumber << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << editNumber << " ��������" << endl;

			break;

		}
		case 11: {

			string auditoryStr;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ���������: ";
			cin >> auditoryStr;

			if (scheduleDataVector.editByAuditoryInSchedule(editNumber, *(new Auditory(auditoryStr))))
				cout << "!- " << editNumber << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << editNumber << " ��������" << endl;


			break;
		}
		case 12: {

			Auditory auditory;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ������� ���������: ";
			cin >> editNumber;

			cout << ">> ������� ����� ���������: " << endl;
			cout << ">> ";
			cin >> auditory;

			//3-2

			if (scheduleDataVector.editAuditory(editNumber, auditory))
				cout << "!- " << editNumber << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << editNumber << " ��������" << endl;

			break;
		}
		case 13: {

			Auditory oldAuditory;
			Auditory newAuditory;

			cout << ">> ������� ������� ���������: " << endl;
			cout << ">> ";
			cin >> oldAuditory;

			cout << ">> ������� ����� ���������: " << endl;
			cout << ">> ";
			cin >> newAuditory;

			//3-2

			if (scheduleDataVector.editAuditory(oldAuditory, newAuditory))
				cout << "!- " << oldAuditory.getAuditoryName() << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << oldAuditory.getAuditoryName() << " ��������" << endl;

			break;
		}
		case 14: {

			Group group;
			int editNumber;

			cout << ">> ������� ���������� ����� ������ � ������� �����: ";
			cin >> editNumber;

			cout << ">> ������� ����� ������: " << endl;
			cout << ">> ";
			cin >> group;

			//���-815

			if (scheduleDataVector.editGroup(editNumber, group))
				cout << "!- " << editNumber << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << editNumber << " ��������" << endl;

			break;
		}
		case 15: {

			Group oldGroup;
			Group newGroup;

			cout << ">> ������� ������� ������: " << endl;
			cout << ">> ";
			cin >> oldGroup;

			cout << ">> ������� ����� ������: " << endl;
			cout << ">> ";
			cin >> newGroup;

			//���-815

			if (scheduleDataVector.editGroup(oldGroup, newGroup))
				cout << "!- " << oldGroup.getGroupName() << " ������� ��� �������" << endl;
			else
				cout << "!- ������ ��������� " << oldGroup.getGroupName() << " ��������" << endl;

			break;
		}
		case 16: {

			string hours;
			int audit;

			cout << ">> ������� ���������� �������: ";

			cin.get();
			getline(cin, hours);

			scheduleDataVector.find(hours);

			break;
		}
		case 17: {

			int numberWeek, numberHours;

			cout << ">> ������� ����� �����: ";
			cin >> numberHours;

			cout << ">> ������� ����� ������: ";
			cin >> numberWeek;

			scheduleDataVector.find(numberHours, numberWeek);

			break;
		}
		case 18: {
			scheduleDataVector.printDBShedule();
			break;
		}
		case 19: {
			scheduleDataVector.printDBAuditory();
			break;
		}
		case 20: {
			scheduleDataVector.printDBGroup();
			break;
		}
		case 21: {

			system("cls");

			console();

			break;
		}
		case 22: {
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