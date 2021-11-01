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

	cout << "1. Добавить запись\n" << endl;
	cout << "2. Удалить запись по номеру" << endl;
	cout << "3. Удалить записи по группе" << endl;
	cout << "4. Удалить записи по аудитории\n" << endl;
	cout << "5. Редактировать запись по номеру" << endl;
	cout << "6. Редактировать день в записи по номеру" << endl;
	cout << "7. Редактировать время в записи по номеру" << endl;
	cout << "8. Редактировать группу в записи по номеру" << endl;
	cout << "9. Редактировать аудиторию в записи по номеру\n" << endl;
	cout << "10. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
	cout << "11. Поиск свободной аудитории на заданное число часов в указанную неделю\n" << endl;
	cout << "12. Просмотр таблицы" << endl;
	cout << "13. Очистка экрана" << endl;
	cout << "14. Завершение сесии\n\n";

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
			cout << "\n" <<sch;

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

			string deleteGroupp;

			cout << "  Введите группу: ";
			cin >> deleteGroupp;

			if (dataMapper.removeByGroup(deleteGroupp))
				cout << "  Удаление выполнено!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;

		}
		case 4: {

			string deleteAuditory;

			cout << "  Введите аудиторию: ";
			cin >> deleteAuditory;

			if (dataMapper.removeByAuditory(deleteAuditory))
				cout << "  Удаление выполнено!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;

		}
		case 5: {

			schedule sch;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новые: неделю, день, время начала, время окончания группу и аудиторию" << endl;
			cin >> sch;

			if (dataMapper.edit(editNumber, sch))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;
		}
		case 6: {

			string dayStr;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новый день недели: ";
			cin >> dayStr;

			if (dataMapper.editByDay(editNumber, dayStr))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;
		}case 7: {

			string dayStartStr, dayEndStr;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите время начала: ";
			cin >> dayStartStr;
			cout << "  Введите время окончания: ";
			cin >> dayEndStr;

			if (dataMapper.editByTime(editNumber, dayStartStr, dayEndStr))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;
		}
		case 8: {

			string groupStr;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новую группу: ";
			cin >> groupStr;

			if (dataMapper.editByGroup(editNumber, groupStr))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;
		}
		case 9: {

			string auditoryStr;
			int editNumber;

			cout << "  Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << "  Введите новую аудиторию: ";
			cin >> auditoryStr;

			if (dataMapper.editByAuditory(editNumber, auditoryStr))
				cout << "  Запись изменена!" << endl;
			else
				cout << "  Произошла ошибка!" << endl;

			break;
		}
		case 10: {

			string hours;
			int audit;

			cout << "  Введите промежутки времени: ";

			cin.get();
			getline(cin, hours);

			dataMapper.find(hours);

			break;

		}
		case 11: {

			int numberWeek, numberHours;

			cout << "  Введите число часов: ";
			cin >> numberHours;

			cout << "  Введите номер недели: ";
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
			cout << "Повторите попытку!" << endl;
			break;
		}
		}

	}

	return 0;
}
