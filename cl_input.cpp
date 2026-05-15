#include "cl_input.h"
#include <iostream>

cl_input::cl_input(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_input::signal_read_line(string& s)
{
    getline(cin, s); // важно: читает и пустую строку (такт без команды)
}