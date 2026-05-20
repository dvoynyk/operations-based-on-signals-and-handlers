
#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object, string s_object_name)
	:cl_base(p_head_object, s_object_name)
{

}
void cl_input::signal_read_line(string& s)
{
	//--------------------------------------------------
	// Чтение строки
	// Параметры:
	//     string &s, строка по ссылке
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------
	// 1.1 Ввод значения в строку s

	getline(cin, s);

	return;
}
