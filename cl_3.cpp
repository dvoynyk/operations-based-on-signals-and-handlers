#include "cl_3.h"
#include "cl_base.h"
// Конструктор класса
cl_3::cl_3(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name) {}

int cl_3::get_number_class()      // Метод возвращения номера класса
{
	return 3;                     // Возвращение 3
}

void cl_3::signal(string& message)// Метод сигнала
{
	cout << "Signal from " << get_absolute_path() << endl;                      // Вывод откуда сигнал
	message += " (class: " + to_string(get_number_class()) + ")";               // Добавление к сообщению номера класса
}

void cl_3::handler(string message)                                              // Метод обработчика
{
	cout << "Signal to " << get_absolute_path() << " Text: " << message << endl;// Вывод куда направлен сигнал
}