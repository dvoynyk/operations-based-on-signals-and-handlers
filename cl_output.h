#ifndef CL_OUTPUT_H
#define CL_OUTPUT_H

#include "cl_base.h"

class cl_output : public cl_base	// Класс вывода
{
public:
	cl_output(cl_base* p_head_object, string s_object_name);
	void handler_print(string s);	// Вывод строки
};
#endif    // CL_OUTPUT_H