#ifndef __CL_4__H
#define __CL_4__H

#include "cl_base.h"
class cl_4 : public cl_base                          // Наследование от базового класса
{
public:
	cl_4(cl_base* p_head_object, string s_object_name);// Конструктор класса cl_4
	int get_number_class();                          // Заголовок метода получения номера класса
	void signal(string& message);                    // Заголовок метода сигнала
	void handler(string message);                    // Заголовок метода обработчика
};

#endif
