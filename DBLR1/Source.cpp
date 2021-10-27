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

			cout << "  Введите неделю, день, время начала, время конца, группу и аудиторию" << endl;

			cin >> sch;
			cout << sch;

			if (dataMapper.insert(sch))
				cout << "  Вставка выполнена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			system("pause");

			system("cls");

			console();

			break;
		}
		case 2: {

			int deleteNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> deleteNumber;

			if (dataMapper.remove(deleteNumber))
				cout << "  Удаление выполнено!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;

		}
		case 3: {

			schedule sch;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новые: неделю, день, время начала, время окончания группу и аудиторию" << endl;
			cin >> sch;

			if (dataMapper.edit(editNumber, sch))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произашла ошибка!" << endl;

			break;
		}
		case 4: {

			string hours;
			int audit;

			cout << "  Введите промежутки времени: ";

			cin.get();
			getline(cin, hours);

			dataMapper.find(hours);

			break;

		}
		case 5: {

			string hours;
			int number;

			cout << "  Введите промежутки времени: ";

			cin.get();
			getline(cin, hours);

			cout << "  Введите номер недели: ";
			cin >> number;

			dataMapper.find(hours, number);

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
