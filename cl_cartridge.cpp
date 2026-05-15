#include "cl_cartridge.h"

cl_cartridge::cl_cartridge(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_cartridge::init(int k)
{
    capacity = k;
    remaining = k;
}

void cl_cartridge::start_replacing()
{
    if (replace_ticks_left > 0) return;
    replace_ticks_left = 8;
}

void cl_cartridge::do_tact_replacing()
{
    if (replace_ticks_left <= 0) return;
    replace_ticks_left--;
    if (replace_ticks_left == 0)
        remaining = capacity;
}

bool cl_cartridge::is_replacing()
{
    return replace_ticks_left > 0;
}

void cl_cartridge::consume(int x)
{
    remaining -= x;
    if (remaining < 0) remaining = 0;
}