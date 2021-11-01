#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include <string>
#include "schedule.h"
#include "DataMapper.h"

using namespace::std;

void console() {

	cout << "1. �������� ������\n" << endl;
	cout << "2. ������� ������ �� ������" << endl;
	cout << "3. ������� ������ �� ������" << endl;
	cout << "4. ������� ������ �� ���������\n" << endl;
	cout << "5. ������������� ������ �� ������" << endl;
	cout << "6. ������������� ���� � ������ �� ������" << endl;
	cout << "7. ������������� ����� � ������ �� ������" << endl;
	cout << "8. ������������� ������ � ������ �� ������" << endl;
	cout << "9. ������������� ��������� � ������ �� ������\n" << endl;
	cout << "10. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
	cout << "11. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������\n" << endl;
	cout << "12. �������� �������" << endl;
	cout << "13. ������� ������" << endl;
	cout << "14. ���������� �����\n\n";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    DataMapper dataMapper;

	cout << "\t\t\t\t***���������� �������!***\n";

	console();

	int s = 1, func;

	while (s != 0) {

		cout << "�������� ����������� ��������: ";
		cin >> func;

		switch (func) {
		case 1: {

			schedule sch;

			system("cls");

			cout << "  ������� ������, ����, ����� ������, ����� �����, ������ � ���������" << endl;

			cin >> sch;
			cout << "\n" <<sch;

			if (dataMapper.insert(sch))
				cout << "  ������� ���������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			system("pause");

			system("cls");

			console();

			break;
		}
		case 2: {

			int deleteNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> deleteNumber;

			if (dataMapper.remove(deleteNumber))
				cout << "  �������� ���������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;

		}
		case 3: {

			string deleteGroupp;

			cout << "  ������� ������: ";
			cin >> deleteGroupp;

			if (dataMapper.removeByGroup(deleteGroupp))
				cout << "  �������� ���������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;

		}
		case 4: {

			string deleteAuditory;

			cout << "  ������� ���������: ";
			cin >> deleteAuditory;

			if (dataMapper.removeByAuditory(deleteAuditory))
				cout << "  �������� ���������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;

		}
		case 5: {

			schedule sch;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� �����: ������, ����, ����� ������, ����� ��������� ������ � ���������" << endl;
			cin >> sch;

			if (dataMapper.edit(editNumber, sch))
				cout << "  ������ ��������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;
		}
		case 6: {

			string dayStr;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� ����� ���� ������: ";
			cin >> dayStr;

			if (dataMapper.editByDay(editNumber, dayStr))
				cout << "  ������ ��������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;
		}case 7: {

			string dayStartStr, dayEndStr;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� ����� ������: ";
			cin >> dayStartStr;
			cout << "  ������� ����� ���������: ";
			cin >> dayEndStr;

			if (dataMapper.editByTime(editNumber, dayStartStr, dayEndStr))
				cout << "  ������ ��������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;
		}
		case 8: {

			string groupStr;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� ����� ������: ";
			cin >> groupStr;

			if (dataMapper.editByGroup(editNumber, groupStr))
				cout << "  ������ ��������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;
		}
		case 9: {

			string auditoryStr;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� ����� ���������: ";
			cin >> auditoryStr;

			if (dataMapper.editByAuditory(editNumber, auditoryStr))
				cout << "  ������ ��������!" << endl;
			else
				cout << "  ��������� ������!" << endl;

			break;
		}
		case 10: {

			string hours;
			int audit;

			cout << "  ������� ���������� �������: ";

			cin.get();
			getline(cin, hours);

			dataMapper.find(hours);

			break;

		}
		case 11: {

			int numberWeek, numberHours;

			cout << "  ������� ����� �����: ";
			cin >> numberHours;

			cout << "  ������� ����� ������: ";
			cin >> numberWeek;

			dataMapper.find(numberHours, numberWeek);

			break;
		}
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
			cout << "��������� �������!" << endl;
			break;
		}
		}

	}

	return 0;
}
