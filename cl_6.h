#ifndef __CL_6__H
#define __CL_6__H

#include "cl_base.h"
class cl_6 : public cl_base                          // Наследование от базового класса
{
public:
	cl_6(cl_base* p_head_object, string s_object_name);// Конструктор класса cl_6
	int get_number_class();                          // Заголовок метода получения номера класса
	void signal(string& message);                    // Заголовок метода сигнала
	void handler(string message);                    // Заголовок метода обработчика
};

#endif
