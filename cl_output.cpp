#include "cl_output.h"
#include <iostream>

cl_output::cl_output(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_output::handler_print(string s)
{
    cout << s << endl;
}