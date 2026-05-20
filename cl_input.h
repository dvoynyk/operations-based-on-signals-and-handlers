#ifndef CL_INPUT_H
#define CL_INPUT_H
#include "cl_base.h"
class cl_input : public cl_base	// Объект ввода
{
public:
	cl_input(cl_base* p_head_object, string s_object_name);
	void signal_read_line(string& s);	// Чтение строки
};
#endif    // CL_INPUT_H