#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H

#include "cl_base.h"

// Объект вывода: получает текст по handler и печатает с новой строки
class cl_output : public cl_base
{
public:
    cl_output(cl_base* p_head_object, string s_object_name);

    void handler_print(string s);

    int get_number_class() { return 3; } // не обязательно
};

#endif