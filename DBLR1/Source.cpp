#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include "schedule.h"
#include "DataMapper.h"

using namespace::std;

void console() {

	cout << "1. �������� ������" << endl;
	cout << "2. ������� ������ �� ������" << endl;
	cout << "3. ������������� ������ �� ������" << endl;
	cout << "4. ����� ��������� ��������� � �������� ���� � ������� ����� ��������" << endl;
	cout << "5. ����� ��������� ��������� �� �������� ����� ����� � ��������� ������" << endl;
	cout << "6. �������� �������" << endl;
	cout << "7. ������� ������" << endl;
	cout << "8. ���������� �����\n\n";

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

			cout << "  ������� ������, ����, �����, ������ � ��������� ����� ENTER" << endl;

			cin >> sch;

			dataMapper.insert(sch);

			system("cls");

			console();

			break;
		}
		case 2: {

			int deleteNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> deleteNumber;

			dataMapper.remove(deleteNumber);

			break;

		}
		case 3: {

			schedule sch;
			int editNumber;

			cout << "  ������� ���������� ����� ������ � ����������: ";
			cin >> editNumber;

			cout << "  ������� �����: ������, ����, �����, ������ � ��������� ����� ENTER" << endl;
			cin >> sch;

			dataMapper.edit(editNumber, sch);

			break;
		}
		case 4: {



			break;

		}
		case 5: {



			break;
		}
		case 6: {

			dataMapper.printAll();

			break;
		}
		case 7: {

			system("cls");

			console();

			break;
		}
		case 8: {
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
