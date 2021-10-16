#include <iostream>
#include <Windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <vector>
#include "schedule.h"
#include "DataMapper.h"

using namespace::std;

void console() {

	cout << "1. Добавить запись" << endl;
	cout << "2. Удалить запись по номеру" << endl;
	cout << "3. Редактировать запись по номеру" << endl;
	cout << "4. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
	cout << "5. Поиск свободной аудитории на заданное число часов в указанную неделю" << endl;
	cout << "6. Просмотр таблицы" << endl;
	cout << "7. Очистка экрана" << endl;
	cout << "8. Завершение сесии\n\n";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    DataMapper dataMapper;

	cout << "\t\t\t\t***Расписание занятий!***\n";

	console();

	int s = 1, func;

	while (s != 0) {

		cout << "Выберите необходимое действие: ";
		cin >> func;

		switch (func) {

		case 1: {

			schedule sch;

			system("cls");

			cout << "  Введите неделю, день, время, группу и аудиторию через ENTER" << endl;

			cin >> sch;

			dataMapper.insert(sch);

			system("cls");

			console();

			break;
		}
		case 2: {

			int deleteNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> deleteNumber;

			dataMapper.remove(deleteNumber);

			break;

		}
		case 3: {

			schedule sch;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новые: неделю, день, время, группу и аудиторию через ENTER" << endl;
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
			cout << "Повторите попытку!" << endl;
			break;
		}
		}

	}

	return 0;
}
