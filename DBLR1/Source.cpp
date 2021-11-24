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


//доделать функции с 6-9
//проверить их
//добавить все 4 файнда
//добавить еще пару функций на каждый класс


void console() {

	string mainStr = "***Расписание занятий!***";
	CenterString(mainStr, 25u);
	
	cout << "   1. Добавить запись\n" << endl;
	cout << "   2. Удалить запись по номеру" << endl;
	cout << "   3. Удалить записи по группе" << endl;
	cout << "   4. Удалить записи по аудитории\n" << endl;
	cout << "   5. Редактировать запись по номеру" << endl;
	cout << "   6. Редактировать день в записи по номеру" << endl;
	cout << "   7. Редактировать время в записи по номеру" << endl;
	cout << "   8. Редактировать группу в записи по номеру" << endl;
	cout << "   9. Редактировать аудиторию в записи по номеру\n" << endl;
	cout << "   10. Поиск свободной аудитории в заданные часы в течение всего семестра" << endl;
	cout << "   11. Поиск свободной аудитории на заданное число часов в указанную неделю\n" << endl;
	cout << "   12. Просмотр таблицы" << endl;
	cout << "   13. Очистка экрана" << endl;
	cout << "   14. Завершение сесии\n\n";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0A");

	scheduleData scheduleDataVector;
    DataMapper dataMapper(&scheduleDataVector);

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

			dataMapper.insert(&sch);

			dataMapper.updateIdVectors(&scheduleDataVector, &sch);
			
			system("pause");

			system("cls");

			console();

			break;
		}
		case 2: {

			if (scheduleDataVector.getScheduleVector().size() != 0) {

				int deleteNumber, schedId = 0, auditId = 0, groupId = 0;

				cout << ">> Введите порядковый номер записи в расписании: ";
				cin >> deleteNumber;

				if (deleteNumber <= scheduleDataVector.getScheduleVector().size()) {

					int* delNum = new int(scheduleDataVector.getScheduleVector()[deleteNumber - 1].getID());

					if (dataMapper.remove(delNum))
						if (scheduleDataVector.removeInSchedule(*delNum))
							cout << "!- Удаление выполнено!" << endl;
						else
							cout << "!- Произошла ошибка!" << endl;
					else
						cout << "!- Произошла ошибка!" << endl;
				}
				else
					cout << "!- Такого порядкового номера нет!" << endl;
			}
			else
				cout << "!- Таблица пуста! Нельзя ничего удалить" << endl;

			break;

		}
		
		case 3: {

			string deleteGroupp;

			cout << "   Введите группу: ";
			cin >> deleteGroupp;
			//scheduleDataVector.removeAllInGroup(new Group(&deleteGroupp));

			if (dataMapper.removeByGroup(&deleteGroupp)) {
				scheduleDataVector.removeAllInGroup(new Group(&deleteGroupp));
				cout << "!- Удаление выполнено!" << endl;
			}
			else
				cout << "!- Произошла ошибка!" << endl;

			break;

		}
		
		case 4: {

			string deleteAuditory;

			cout << ">> Введите аудиторию: ";
			cin >> deleteAuditory;

			scheduleDataVector.removeAllInAuditory(new Auditory(&deleteAuditory));

			if (dataMapper.removeByAuditory(&deleteAuditory)) {
				scheduleDataVector.removeAllInAuditory(new Auditory(&deleteAuditory));
				cout << "!- Удаление выполнено!" << endl;
			}
			else
				cout << "!- Произошла ошибка!" << endl;


			break;

		}
		
		case 5: {

			schedule sch;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новые: неделю, день, время начала, время окончания, группу и аудиторию:" << endl;
			cout << ">> ";
			cin >> sch;
			scheduleDataVector.editAllSchedule(editNumber, &sch);

			if (dataMapper.edit(&editNumber, &sch)) {
				scheduleDataVector.editAllSchedule(editNumber, &sch);
				cout << "!- Запись изменена!" << endl;
			}
			else
				cout << "!- Произошла ошибка!" << endl;

			break;
		}
			  
		case 6: {

			string dayStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новый день недели: ";
			cin >> dayStr;

			if (dataMapper.editByDay(&editNumber, &dayStr))
				cout << "!- Запись изменена!" << endl;
			else
				cout << "!- Произошла ошибка!" << endl;

			break;
		}
			  
		case 7: {

			string dayStartStr, dayEndStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите время начала: ";
			cin >> dayStartStr;
			cout << ">> Введите время окончания: ";
			cin >> dayEndStr;

			if (dataMapper.editByTime(&editNumber, &dayStartStr, &dayEndStr))
				cout << "!- Запись изменена!" << endl;
			else
				cout << "!- Произошла ошибка!" << endl;

			break;
		}
		case 8: {

			string groupStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новую группу: ";
			cin >> groupStr;

			if (dataMapper.editByGroup(&editNumber, &groupStr))
				cout << "!- Запись изменена!" << endl;
			else
				cout << "!- Произошла ошибка!" << endl;

			break;
		}
		case 9: {

			string auditoryStr;
			int editNumber;

			cout << ">> Введите порядковый номер записи в расписании: ";
			cin >> editNumber;

			cout << ">> Введите новую аудиторию: ";
			cin >> auditoryStr;

			if (dataMapper.editByAuditory(&editNumber, &auditoryStr))
				cout << "!- Запись изменена!" << endl;
			else
				cout << "!- Произошла ошибка!" << endl;

			break;
		}
		/*
		case 10: {

			string hours;
			int audit;

			cout << ">> Введите промежутки времени: ";

			cin.get();
			getline(cin, hours);

			dataMapper.find(hours);

			break;

		}
		case 11: {

			int numberWeek, numberHours;

			cout << ">> Введите число часов: ";
			cin >> numberHours;

			cout << ">> Введите номер недели: ";
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