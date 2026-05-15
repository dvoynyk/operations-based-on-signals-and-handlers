#ifndef __CL_CARTRIDGE__H
#define __CL_CARTRIDGE__H

#include "cl_base.h"

// Картридж
class cl_cartridge : public cl_base
{
    int capacity = 0;
    int remaining = 0;
    int replace_ticks_left = 0; // 8 тактов замены

public:
    cl_cartridge(cl_base* p_head_object, string s_object_name);

    void init(int k);

    int get_remaining() { return remaining; }

    // REPLACE_CARTRIDGE: начать замену (8 тактов)
    void start_replacing();

    void do_tact_replacing();
    bool is_replacing();

    void consume(int x);

    int get_number_class() { return 6; } // не обязательно
};

#endif