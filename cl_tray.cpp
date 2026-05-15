#include "cl_tray.h"

cl_tray::cl_tray(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_tray::init(int m)
{
    capacity = m;
    sheets = m;
}

void cl_tray::start_loading()
{
    if (load_ticks_left > 0) return;
    load_ticks_left = 3;
}

void cl_tray::do_tact_loading()
{
    if (load_ticks_left <= 0) return;
    load_ticks_left--;
    if (load_ticks_left == 0)
        sheets = capacity;
}

bool cl_tray::is_loading()
{
    return load_ticks_left > 0;
}

void cl_tray::consume(int x)
{
    sheets -= x;
    if (sheets < 0) sheets = 0;
}