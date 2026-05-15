#ifndef __CL_INPUT__H
#define __CL_INPUT__H

#include "cl_base.h"

// Объект ввода: по сигналу считывает одну строку (включая пустую)
class cl_input : public cl_base
{
public:
    cl_input(cl_base* p_head_object, string s_object_name);

    // signal: читает строку целиком в s (по ссылке)
    void signal_read_line(string& s);

    int get_number_class() { return 2; } // не обязательно, но пусть будет
};

#endif