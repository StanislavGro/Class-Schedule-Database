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

    dataMapper.insert(*(new schedule(7, "Friday", "12:00-13:30", "���-815", 1)));

    //cout << dataMapper.getSchedule()[0];


	cout << "\t\t\t\t***���������� �������!***\n";

	cout << "1. �������� ������" << endl;
	cout << "2. ������� ������ �� ������" << endl;
	cout << "3. ������� �������� ������" << endl;
	cout << "4. ������������� ������ �� ������" << endl;
	cout << "5. ������������� �������� ������" << endl;
	cout << "6. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
	cout << "7. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������" << endl;
	cout << "8. �������� �������" << endl;
	cout << "9. ������� ������" << endl;
	cout << "10. ���������� �����\n\n";

	int s = 1, func;

	while (s != 0) {

		cout << "�������� ����������� ��������: ";
		cin >> func;

		switch (func) {

		case 1: {



			break;
		}
		case 2: {



			break;
		}case 3: {



			break;
		}case 4: {



			break;
		}
		case 5: {



			break;

		}
		case 6: {



			break;
		}
		case 7: {



			break;
		}
		case 8: {



			break;
		}
		case 9: {
			system("cls");

			cout << "1. �������� ������" << endl;
			cout << "2. ������� ������ �� ������" << endl;
			cout << "3. ������� �������� ������" << endl;
			cout << "4. ������������� ������ �� ������" << endl;
			cout << "5. ������������� �������� ������" << endl;
			cout << "6. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
			cout << "7. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������" << endl;
			cout << "8. �������� �������" << endl;
			cout << "9. ������� ������" << endl;
			cout << "10. ���������� �����\n\n";

			break;
		}
		case 10: {
			s = 0;
			break;
		}
		default: {
			cout << "��������� �������!" << endl;
			break;
		}
		}

	}

	system("pause");

	return 0;
}
