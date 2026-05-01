#include "cl_application.h"
#include "cl_base.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <iostream>
#include <stack>
using namespace std;
TYPE_SIGNAL class_number_to_signal(int cl_number)        // Функция сопоставления: по номеру класса возвращает указатель на метод сигнала
{
	switch (cl_number)									 // Выбираем ветку в зависимости от номера класса
	{
	case 1: return SIGNAL_D(cl_application::signal); // Класс 1 - возвращение указателя на метод сигнала signal корневого объекта
	case 2: return SIGNAL_D(cl_2::signal);			 // Класс 2 - возвращение указателя на метод сигнала signal объекта класса cl_2
	case 3: return SIGNAL_D(cl_3::signal);			 // Класс 3 - возвращение указателя на метод сигнала signal объекта класса cl_3
	case 4: return SIGNAL_D(cl_4::signal);			 // Класс 4 - возвращение указателя на метод сигнала signal объекта класса cl_4
	case 5: return SIGNAL_D(cl_5::signal);			 // Класс 5 - возвращение указателя на метод сигнала signal объекта класса cl_5
	case 6: return SIGNAL_D(cl_6::signal);			 // Класс 6 - возвращение указателя на метод сигнала signal объекта класса cl_6
	}
	return nullptr;										 // Возвращение нулевого указателя
}

TYPE_HANDLER class_number_to_handler(int cl_number)      // Функция сопоставления: по номеру класса возвращает указатель на метод обработчика
{
	switch (cl_number)                                    // Выбираем ветку в зависимости от номера класса
	{
	case 1:return HANDLER_D(cl_application::handler);// Класс 1 - возвращение указателя на метод обработчика handler корневого объекта
	case 2:return HANDLER_D(cl_2::handler);          // Класс 2 - возвращение указателя на метод обработчика handler объекта класса cl_2
	case 3:return HANDLER_D(cl_3::handler);          // Класс 3 - возвращение указателя на метод обработчика handler объекта класса cl_3
	case 4:return HANDLER_D(cl_4::handler);          // Класс 4 - возвращение указателя на метод обработчика handler объекта класса cl_4
	case 5:return HANDLER_D(cl_5::handler);          // Класс 5 - возвращение указателя на метод обработчика handler объекта класса cl_5
	case 6:return HANDLER_D(cl_6::handler);          // Класс 6 - возвращение указателя на метод обработчика handler объекта класса cl_6
	}
	return nullptr;                                      // Возвращение нулевого указателя
}
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object) {} // Конструктор cl_application с вызовом конструктора базового класса для прикрепления к дереву 
void cl_application::build_tree_objects()				 // Метод построения дерева
{
	cout << "Object tree" << endl;                       // Вывод заголовка "Object tree"

	string root_name;									 // Строка для хранения имени корневого объекта
	cin >> root_name;                                    // Ввод имени корнего объекта
	change_s_object_name(root_name);                     // Смена имени корнего объекта с базового имени Base_object на введенное

	string path, sub_name;                                // Строки для хранения пути(координат) объекта и имени создаваемого объекта 
	int cl_obj;                                          // Номер класса создаваемого объекта

	cl_base* p_new = nullptr;                             // Указатель для найденного объекта
	cl_base* p_last = this;                               // Указатель для последнего созданного объекта

	cin >> path;                                         // Ввод первой координаты головного объекта
	while (path != "endtree")                             // Пока не было введено "endtree"
	{
		cin >> sub_name >> cl_obj;                       // Ввод имени нового объекта и номера его класса

		p_new = p_last->get_pointer_by_path(path);       // Найти указатель на головной объект по введенной координате от последнего последнего созданного
		if (p_new == nullptr)							 // Головной объект не найден
		{
			this->print_tree();                          // Печать дерева
			cout << "The head object " << path << " is not found" << endl; // Вывод текста ошибки и координат объекта
			exit(1);                                     // Завершение работы системы с кодом 1
		}
		if (p_new->get_adress_subordinate_object_name(sub_name) != nullptr)        //Есть дубляж среди подчиненых у текущего головного объекта
		{
			cout << endl << path << "	Dubbing the names of subordinate objects";//Объект не создается, выводится сообщение об ошибке
		}
		else {
			switch (cl_obj)                               // Выбираем ветку в зависимости от номера класса объекта
			{
			case 2:
				p_last = new cl_2(p_new, sub_name);    // Создание динамического объекта класса cl_2
				break;								 // Выход из switch
			case 3:
				p_last = new cl_3(p_new, sub_name);   // Создание динамического объекта класса cl_3
				break;
			case 4:
				p_last = new cl_4(p_new, sub_name);   // Создание динамического объекта класса cl_4
				break;
			case 5:
				p_last = new cl_5(p_new, sub_name);   // Создание динамического объекта класса cl_5
				break;
			case 6:
				p_last = new cl_6(p_new, sub_name);   // Создание динамического объекта класса cl_6
				break;
			default: break;                          // Номер класса некорректный - ничего не создается
			}
		}
		cin >> path;                                     // Ввод следующей координаты

	}

	cl_base* target_ptr;                                 // Указатель на целевой объекта
	string target_path;                                  // Строка для пути(координаты) целового объекта
	cin >> path;                                         // Ввод координаты объекта выдающего сигнал
	while (path != "end_of_connections")                 // Пока не введено "end_of_connections"
	{
		cin >> target_path;                              // Ввод координаты целового объекта
		p_new = get_pointer_by_path(path);               // Нахождение указателя на объект, выдающего сигнал по введенному пути
		target_ptr = get_pointer_by_path(target_path);   // Нахождение указателя на целевой объект 
		TYPE_SIGNAL signal_f = class_number_to_signal(p_new->get_number_class());        // Указатель на метод сигнала по номеру класса объекта, выдающего сигнал
		TYPE_HANDLER handler_f = class_number_to_handler(target_ptr->get_number_class());// Указатель на метод обработчика по номеру класса целевого объекта
		p_new->set_connect(signal_f, target_ptr, handler_f);// Установка связи между сигналом и обработчиком target_ptr
		cin >> path;                                     // Ввод следующей координаты объекта, выдающего сигнал
	}

}
int cl_application::exec_app()        // Метод запуска системы и обработки команд
{

	TYPE_SIGNAL signal_f;             // Указатель на метод сигнала 
	TYPE_HANDLER handler_f;           // Указатель на метод обработчика

	this->set_state_branch(1);        // Приведение объектов в состояние готовности, включение ветки от корня

	string command, input, message;   // Строки комманды, координаты и сообщения
	int new_state;                    // Строка для ввода значения в нее нового состояния объекта
	cl_base* extra_ptr;               // Указатель на объект, к которому применяются команды
	cl_base* target_ptr;              // Указатель на целевой объект

	this->print_tree();               // Печать дерева

	while (cin >> command && command != "END")                                   // Пока команда не "END" и ввод успешен
	{
		if (command == "EMIT")                                                   // Команда "EMIT"   
		{
			cin >> input; 														// Ввод координаты объекта источника
			getline(cin, message);                                               // Считать остаток строки как сообщение, включая пробелы

			extra_ptr = this->get_pointer_by_path(input);                       // Поиск объекта источника
			if (extra_ptr == nullptr)                                            // Если объект не найден
			{
				cout << "Object " << input << " not found" << endl;             // Вывод сообщения об ошибки и координаты                                              
				continue;                                                       // Переход к чтению следующей команды
			}

			int cl_n = extra_ptr->get_number_class();                           // Получение номера класса объекта, выдающего сигнал
			extra_ptr->emit_signal(class_number_to_signal(cl_n), message);       // Выдача сигнала от extra_ptr, передача указателя на правильный метод сигнала signal для этого класса и передача message по ссылке
		}
		else if (command == "SET_CONNECT")                                       // Команда "SET_CONNECT"
		{
			string src_path, trg_path;                                          // Строки для 2 координат
			cin >> src_path >> trg_path;                                        // Ввод источника и целового объекта

			extra_ptr = this->get_pointer_by_path(src_path);                    // Поиск объекта источника
			if (extra_ptr == nullptr)                                            // Если объект не найден
			{
				cout << "Object " << src_path << " not found" << endl;          // Вывод сообщения об ошибки и координаты                                              
				continue;                                                       // Переход к чтению следующей команды
			}

			target_ptr = this->get_pointer_by_path(trg_path);                   // Поиск указателя на целевой объект по координате input
			if (target_ptr == nullptr)                                           // Целевой объект не найден по координате
			{
				cout << "Handler object " << trg_path << " not found" << endl;  // Вывод сообщения об ошибке 
				continue;                                                       // Пропуск установки связи
			}

			signal_f = class_number_to_signal(extra_ptr->get_number_class());   // Получение указателя на метод сигнала signal для объекта, выдающего сигнал
			handler_f = class_number_to_handler(target_ptr->get_number_class());// Получение указателя на метод обработчика handler для целевого объекта
			extra_ptr->set_connect(signal_f, target_ptr, handler_f);              // Установка сзязи между сигналом и обработчиком
		}
		else if (command == "DELETE_CONNECT")                                    // Команда "DELETE_CONNECT"
		{
			string src_path, trg_path;                                          // Строки для 2 координат
			cin >> src_path >> trg_path;                                        // Ввод источника и целового объекта

			extra_ptr = this->get_pointer_by_path(src_path);                    // Поиск объекта источника
			if (extra_ptr == nullptr)                                            // Если объект не найден
			{
				cout << "Object " << src_path << " not found" << endl;          // Вывод сообщения об ошибки и координаты                                              
				continue;                                                       // Переход к чтению следующей команды
			}

			target_ptr = this->get_pointer_by_path(trg_path);                   // Поиск указателя на целевой объект по координате input
			if (target_ptr == nullptr)                                           // Целевой объект не найден по координате
			{
				cout << "Handler object " << trg_path << " not found" << endl;  // Вывод сообщения об ошибке 
				continue;                                                       // Пропуск установки связи
			}

			signal_f = class_number_to_signal(extra_ptr->get_number_class());   // Получение указателя на метод сигнала signal для объекта, выдающего сигнал
			handler_f = class_number_to_handler(target_ptr->get_number_class());// Получение указателя на метод обработчика handler для целевого объекта
			extra_ptr->delete_connect(signal_f, target_ptr, handler_f);           // Удаление сзязи между сигналом и обработчиком
		}
		else if (command == "SET_CONDITION")                       // Команда "SET_CONDITION"
		{
			string coord;                                         // Строка для координаты объекта
			cin >> coord >> new_state;                            // Ввод координаты и нового состояния

			extra_ptr = this->get_pointer_by_path(coord);         // Поиск объекта источника
			if (extra_ptr == nullptr)                              // Если объект не найден
			{
				cout << "Object " << coord << " not found" << endl;   // Вывод сообщения об ошибки и координаты                                              
				continue;                                         // Переход к чтению следующей команды
			}
			extra_ptr->set_ready(new_state);                      // Установка нового статуса

		}
	}
	return(0);                                                    // Завершение работы системы с кодом 0
}

int cl_application::get_number_class()                            // Метод получения номера класса
{
	return 1;                                                     // Возвращение 1
}

void cl_application::signal(string& message)                      // Метод сигнала
{
	cout << "Signal from " << get_absolute_path() << endl;        // Вывод источника сигнала и абсолютного пути до него
	message += " (class: " + to_string(get_number_class()) + ")"; // Прибавление к сообщению номера класса текущего объекта
}

void cl_application::handler(string message)                      // Метод обработчика
{
	cout << "Signal to " << get_absolute_path() << " Text: " << message << endl; // Вывод абсолютного пути куда пришел сигнал и вывод сообщения	 
}

