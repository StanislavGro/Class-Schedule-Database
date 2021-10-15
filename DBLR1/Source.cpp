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

    dataMapper.insert(*(new schedule(7, "Friday", "12:00-13:30", "АВТ-815", 1)));

    //cout << dataMapper.getSchedule()[0];


	cout << "\t\t\t\t***Расписание занятий!***\n";

	cout << "1. Добавить запись" << endl;
	cout << "2. Удалить запись по номеру" << endl;
	cout << "3. Удалить ввденную запись" << endl;
	cout << "4. Редактировать запись по номеру" << endl;
	cout << "5. Редактировать ввденную запись" << endl;
	cout << "6. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
	cout << "7. Поиск свободной аудитории на заданное число часов в указанную неделю" << endl;
	cout << "8. Просмотр таблицы" << endl;
	cout << "9. Очистка экрана" << endl;
	cout << "10. Завершение сесии\n\n";

	int s = 1, func;

	while (s != 0) {

		cout << "Выберите необходимое действие: ";
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

			cout << "1. Добавить запись" << endl;
			cout << "2. Удалить запись по номеру" << endl;
			cout << "3. Удалить ввденную запись" << endl;
			cout << "4. Редактировать запись по номеру" << endl;
			cout << "5. Редактировать ввденную запись" << endl;
			cout << "6. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
			cout << "7. Поиск свободной аудитории на заданное число часов в указанную неделю" << endl;
			cout << "8. Просмотр таблицы" << endl;
			cout << "9. Очистка экрана" << endl;
			cout << "10. Завершение сесии\n\n";

			break;
		}
		case 10: {
			s = 0;
			break;
		}
		default: {
			cout << "Повторите попытку!" << endl;
			break;
		}
		}

	}

	system("pause");

	return 0;
}
