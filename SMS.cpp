// Включите все необходимые библиотеки.
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	// Учитывая, что максимальная длина введенных данных (имя)
	// равна 15.
	char data[15];
	int n = 0, option = 0, count_n = 0;
	// Это начальная оценка, присвоенная предмету.
	string empty = "00";
	string proctor = "";
	// Имя файла, в котором хранится база данных.
	ifstream f("StudentsData.txt");
	string line;

	// Следующий цикл for подсчитывает общее количество
	// строк в файле.
	for (int i = 0; std::getline(f, line); ++i) {
		count_n++;
	}

	while (option != 6) {
		// При этом выводятся все доступные параметры в
		// DB
		cout << "Доступные операции: \n1. Добавить новых "
			 "Студентов \n2."
			 << " Логин студента\n3. Выставление оценок\n4. "
			 "Логин преподавателя\n5. Просмотр администратора\n"
			 << "6. Опция выхода из системы\nВвод:";
		cin >> option;

		if (option == 1) {
			cout << "Введите количество студентов: ";
			cin >> n;

			count_n = count_n + n;

			for (int i = 0; i < n; i++) {
				ofstream outfile;
				outfile.open("StudentsData.txt", ios::app);
				// Все данные одного учащегося
				// хранятся построчно.
				cout << "Введите свой регистрационный номер: ";
				cin >> data;
				outfile << data << "\t";

				cout << "Введите своё имя: ";
				cin >> data;
				int len = strlen(data);

				while (len < 15) {
					data[len] = ' ';
					len = len + 1;
				}
				outfile << data << "\t";
				// Первоначальная вставка пустых данных в файл
				outfile << empty << "\t";
				outfile << empty << "\t";

				cout << "Введите свой идентификационный номер: ";
				cin >> proctor;

				outfile << proctor << endl;
			}
		}

		else if (option == 2) {
			char regno[9];
			cout << "Введите свой регистрационный номер: ";
			cin >> regno;
			ifstream infile;
			int check = 0;
			infile.open("StudentsData.txt", ios::in);

			// Этот цикл выводит данные в соответствии с
			// указанным регистрационным номером.
			while (infile >> data) {
				if (strcmp(data, regno) == 0) {
					cout
						<< "\nRegistration Number: " << data
						<< endl;
					infile >> data;
					cout << "Name: " << data << endl;

					infile >> data;
					cout << "CSE1001 mark: " << data
						<< endl;

					infile >> data;
					cout << "CSE1002 mark: " << data
						<< endl;

					infile >> data;
					cout << "Proctor ID: " << data << endl;

					infile.close();
					check = 1;
				}
			}

			if (check == 0) {
				cout << "Такой регистрационный номер не найден!"
					<< endl;
			}
		}

		// Этот цикл используется для просмотра и добавления отметок в
		// базу данных учащегося.
		else if (option == 3) {
			char subcode[7];
			cout << "Введите свой код: ";
			cin >> subcode;
			string code1 = "CSE1001", code2 = "CSE1002",
				mark = "";
			ifstream infile;
			int check = 0;

			cout << "Доступные операции: 1. Добавить данные "
					"о марках"
				<< "2. Просмотреть параметр ввода данных: ";
			cin >> option;

			if (option == 1) {
				cout
					<< "Внимание! Вам нужно будет добавить пометку\n"
					<< "подробности для всех студентов!"
					<< endl;
				for (int i = 0; i < count_n; i++) {
					fstream file("StudentsData.txt");

					// Поиск в файле выполнен
					// в соответствии с длиной
					// вставляемых данных. Его необходимо
					// соответствующим образом настроить для разных
					// длин данных.

					if (strcmp(subcode, code1.c_str())
						== 0) {
						file.seekp(26 + 37 * i,
							std::ios_base::beg);
						cout << "Введите отметку студента#"
							<< (i + 1) << " : ";
						cin >> mark;
						file.write(mark.c_str(), 2);
					}

					if (strcmp(subcode, code2.c_str())
						== 0) {
						file.seekp(29 + 37 * i,
							std::ios_base::beg);
						cout << "Введите отметку студента#"
							<< (i + 1) << " : ";
						cin >> mark;
						file.write(mark.c_str(), 2);
					}
				}
			}

			// Этот цикл используется для просмотра оценок учащегося.
			// Дополнительные команды infile использовались только для
			// получения конкретной оценки, поскольку данные были
			// разделены пробелом табуляции.

			else if (option == 2) {
				infile.open("StudentData.txt", ios::in);
				if (strcmp(subcode, code1.c_str()) == 0) {
					cout << "Регистрауионный номер - отметка\n"
						<< endl;
					while (infile >> data) {
						cout << data;
						infile >> data;
						infile >> data;
						cout << " - " << data << endl;
						infile >> data;
						infile >> data;
						check = 1;
					}
				}

				infile.close();
				infile.open("StudentData.txt", ios::in);

				if (strcmp(subcode, code2.c_str()) == 0) {
					cout << "Регистрауионный номер - отметка\n"
						<< endl;
					while (infile >> data) {
						cout << data;
						infile >> data;
						infile >> data;
						infile >> data;
						cout << " - " << data << endl;
						infile >> data;
						check = 1;
					}
				}
			}

			infile.close();

			if (check == 0) {
				cout << "Такой код темы не найден!"
					<< endl;
			}
		}

		// В этом цикле отображаются все данные об учениках
		// под тем же идентификатором преподавателя.

		else if (option == 4) {
			char procid[7];
			cout << "Введите ID преподователя: ";
			cin >> procid;
			int check = 0;
			char temp1[100], temp2[100], temp3[100];
			char temp4[100], id[100];
			ifstream infile;
			infile.open("StudentData.txt", ios::in);

			while (infile >> temp1) {
				infile >> temp2;
				infile >> temp3;
				infile >> temp4;
				infile >> id;

				if (strcmp(id, procid) == 0) {
					cout << "\nРегистрационный номер: "
						<< temp1 << endl;
					cout << "Имя: " << temp2 << endl;
					cout << "CSE1001 Mark: " << temp3
						<< endl;
					cout << "CSE1002 Mark: " << temp4
						<< endl;
					check = 1;
				}
			}

			if (check == 0) {
				cout << "Такой идентификатор проктора не найден!" << endl;
			}
		}

		// Этот цикл действует как режим администратора, позволяющий просматривать все
		// данные в файле.

		else if (option == 5) {
			char password[25];
			cout << "Введите пароль администратора: ";
			cin >> password;

			// Значение этой переменной может быть изменено в соответствии
			// по вашему требованию администратора
			// пароль.

			string admin_pass = "admin";

			if (strcmp(password, admin_pass.c_str()) == 0) {
				cout << "Регистрационный номер "
						"\tName\tCSE1001\tCSE1002\tProctor "
						"Идентификатор"
					<< endl;
				ifstream infile;
				infile.open("StudentData.txt", ios::in);
				char data[20];

				while (infile >> data) {
					cout << data << "\t";
					infile >> data;
					cout << data << "\t";
					infile >> data;
					cout << data << "\t";
					infile >> data;
					cout << data << "\t";
					infile >> data;
					cout << data << endl;
				}
			}
		}
	}
}
