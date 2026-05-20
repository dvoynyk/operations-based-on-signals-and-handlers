
#include "cl_output.h"
cl_output::cl_output(cl_base* p_head_object, string s_object_name)
	:cl_base(p_head_object, s_object_name)
{

}
void cl_output::handler_print(string s)
{
	//--------------------------------------------------
	// Вывод строки
	// Параметры:
	//     string s, строка по значению
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	// 1.1 Вывод на экран значения параметра s
	cout << s << endl;
}
