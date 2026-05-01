#ifndef __CL_5__H
#define __CL_5__H

#include "cl_base.h"
class cl_5 : public cl_base                          // Наследование от базового класса
{
public:
	cl_5(cl_base* p_head_object, string s_object_name);// Конструктор класса cl_5
	int get_number_class();                          // Заголовок метода получения номера класса 
	void signal(string& message);                    // Заголовок метода сигнала
	void handler(string message);                    // Заголовок метода обработчика
};

#endif
