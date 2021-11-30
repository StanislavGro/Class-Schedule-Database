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

	string mainStr = "***Расписание занятий!***";
	CenterString(mainStr, 25u);
	
	cout << "   1. Добавить запись в таблицу расписания" << endl;
	cout << "   2. Добавить запись в таблицу аудиторий" << endl;
	cout << "   3. Добавить запись в таблицу групп\n" << endl;

	cout << "   4. Удалить запись в таблице расписаний по номеру" << endl;
	cout << "   5. Удалить записи в таблице групп по группе" << endl;
	cout << "   6. Удалить записи в таблице аудиторий по аудитории\n" << endl;

	cout << "   7. Редактировать всю запись по номеру" << endl;
	cout << "   8. Редактировать день в таблице расписаний по номеру" << endl;
	cout << "   9. Редактировать время в таблице расписаний по номеру" << endl;
	cout << "   10. Редактировать группу в таблице расписаний по номеру" << endl;
	cout << "   11. Редактировать аудиторию в таблице расписаний по номеру" << endl;
	cout << "   12. Редактировать аудиторию в таблице аудиторий по номеру" << endl;
	cout << "   13. Редактировать аудиторию в таблице аудиторий по названию" << endl;
	cout << "   14. Редактировать группу в таблице групп по номеру" << endl;
	cout << "   15. Редактировать группу в таблице групп по названию\n" << endl;

	cout << "   16. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
	cout << "   17. Поиск свободной аудитории на заданное число часов в указанную неделю\n" << endl;

	cout << "   18. Просмотр таблицы расписания" << endl;
	cout << "   19. Просмотр таблицы аудиторий" << endl;
	cout << "   20. Просмотр таблицы групп\n" << endl;

	cout << "   21. Очистка экрана" << endl;
	cout << "   22. Завершение сесии\n\n";
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0A");

	scheduleData scheduleDataVector;

	console();

	int s = 1, func;

	while (s != 0) {

		cout << ">> Выберите необходимое действие: ";
		cin >> func;

		switch (func) {
		case 1: {

			schedule sch;

			system("cls");

			cout << ">> Введите неделю, день, время начала, время конца, группу и аудиторию: " << endl;
			cout << ">> ";
			cin >> sch;
			cout << "\n" << sch;

			//1 Понедельник 8:30 10:00 АВТ-815 3-2

			if (scheduleDataVector.ScheduleVectorCheck(sch)) {
				cout << "!- Вставка в ВЕКТОР прошла успешно!" << endl;
				if (scheduleDataVector.insertSchedule(sch))
					cout << "!- Вставка в БД прошла успешно!" << endl;
				else
					cout << "!- Ошибка вставки в БД" << endl;
			}
			else
				cout << "!- Ошибка вставки в ВЕКТОР" << endl;
			
			cout << endl;

			system("pause");

			system("cls");

			console();

			break;
		}
		case 2: {

			Auditory auditory;

			system("cls");

			cout << ">> Введите аудиторию: " << endl;
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

			cout << ">> Введите группу: " << endl;
			cout << ">> ";
			cin >> group;
			cout << "\n" << group;

			//АБВГ

			scheduleDataVector.insertGroupAndDB(group);

			system("pause");

			system("cls");

			console();

			break;
		}
		case 4: {

			int deleteNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> deleteNumber;

			if (scheduleDataVector.removeInSchedule(deleteNumber))
				cout << "!- Объект был удален" << endl;
			else
				cout << "!- Ошибка! Объект не был удален" << endl;

			break;

		}
		case 5: {

			string deleteGroupp;

			cout << "   Введите группу: ";
			cin >> deleteGroupp;

			Group group(deleteGroupp);

			scheduleDataVector.removeOneInGroup(group);

			break;
		}
		case 6: {

			string deleteAuditory;

			cout << ">> Введите аудиторию: ";
			cin >> deleteAuditory;

			Auditory auditory(deleteAuditory);

			scheduleDataVector.removeOneInAuditory(auditory);

			break;
		}
		case 7: {

			schedule sch;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новые: неделю, день, время начала, время окончания, группу и аудиторию:" << endl;
			cout << ">> ";
			cin >> sch;

			//1 Понедельник 8:30 10:00 АВТ-815 3-2

			if (scheduleDataVector.editAllSchedule(editNumber, sch))
				cout << "!- " << editNumber << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;

			break;
		}
		case 8: {

			string dayStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новый день недели: ";
			cin >> dayStr;

			if (dayStr == "Понедельник" || dayStr == "Вторник" || dayStr == "Среда" || dayStr == "Четверг" || dayStr == "Пятница" || dayStr == "Суббота") {
				if (scheduleDataVector.editByDayInSchedule(editNumber, dayStr))
					cout << "!- " << editNumber << " элемент был изменен" << endl;
				else
					cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;
			}
			else
				cout << "!- Введенного дня не существует! " << endl;

			break;
		}
		case 9: {

			string timeStartStr, timeEndStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите время начала: ";
			cin >> timeStartStr;
			cout << ">> Введите время окончания: ";
			cin >> timeEndStr;

			if ((timeStartStr == "8:30" && timeEndStr == "10:00") ||
				(timeStartStr == "10:15" && timeEndStr == "11:45") ||
				(timeStartStr == "12:00" && timeEndStr == "13:30") ||
				(timeStartStr == "14:00" && timeEndStr == "15:30") ||
				(timeStartStr == "15:45" && timeEndStr == "17:15") ||
				(timeStartStr == "17:30" && timeEndStr == "19:00") ||
				(timeStartStr == "19:15" && timeEndStr == "20:45")) {
				if (scheduleDataVector.editByTimeInSchedule(editNumber, *(new Time(timeStartStr, timeEndStr))))
					cout << "!- " << editNumber << " элемент был изменен" << endl;
				else
					cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;
			}
			else
				cout << "!- Ошибка! Введены неправильные промежутки " << endl;

			break;
		}
		case 10: {

			string groupStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новую группу: ";
			cin >> groupStr;

			if (scheduleDataVector.editByGroupInSchedule(editNumber, *(new Group(groupStr))))
				cout << "!- " << editNumber << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;

			break;

		}
		case 11: {

			string auditoryStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новую аудиторию: ";
			cin >> auditoryStr;

			if (scheduleDataVector.editByAuditoryInSchedule(editNumber, *(new Auditory(auditoryStr))))
				cout << "!- " << editNumber << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;


			break;
		}
		case 12: {

			Auditory auditory;
			int editNumber;

			cout << ">> Введите порядковый номер записи в таблице аудиторий: ";
			cin >> editNumber;

			cout << ">> Введите новую аудиторию: " << endl;
			cout << ">> ";
			cin >> auditory;

			//3-2

			if (scheduleDataVector.editAuditory(editNumber, auditory))
				cout << "!- " << editNumber << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;

			break;
		}
		case 13: {

			Auditory oldAuditory;
			Auditory newAuditory;

			cout << ">> Введите текущую аудиторию: " << endl;
			cout << ">> ";
			cin >> oldAuditory;

			cout << ">> Введите новую аудиторию: " << endl;
			cout << ">> ";
			cin >> newAuditory;

			//3-2

			if (scheduleDataVector.editAuditory(oldAuditory, newAuditory))
				cout << "!- " << oldAuditory.getAuditoryName() << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << oldAuditory.getAuditoryName() << " элемента" << endl;

			break;
		}
		case 14: {

			Group group;
			int editNumber;

			cout << ">> Введите порядковый номер записи в таблице групп: ";
			cin >> editNumber;

			cout << ">> Введите новую группу: " << endl;
			cout << ">> ";
			cin >> group;

			//АВТ-815

			if (scheduleDataVector.editGroup(editNumber, group))
				cout << "!- " << editNumber << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << editNumber << " элемента" << endl;

			break;
		}
		case 15: {

			Group oldGroup;
			Group newGroup;

			cout << ">> Введите текущую группу: " << endl;
			cout << ">> ";
			cin >> oldGroup;

			cout << ">> Введите новую группу: " << endl;
			cout << ">> ";
			cin >> newGroup;

			//АВТ-815

			if (scheduleDataVector.editGroup(oldGroup, newGroup))
				cout << "!- " << oldGroup.getGroupName() << " элемент был изменен" << endl;
			else
				cout << "!- Ошибка изменения " << oldGroup.getGroupName() << " элемента" << endl;

			break;
		}
		case 16: {

			string hours;
			int audit;

			cout << ">> Введите промежутки времени: ";

			cin.get();
			getline(cin, hours);

			scheduleDataVector.find(hours);

			break;
		}
		case 17: {

			int numberWeek, numberHours;

			cout << ">> Введите число часов: ";
			cin >> numberHours;

			cout << ">> Введите номер недели: ";
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
			cout << "!- Повторите попытку!" << endl;
			break;
		}
		}

	}

	return 0;
}

//Получение размеров окна консоли без прокрутки
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