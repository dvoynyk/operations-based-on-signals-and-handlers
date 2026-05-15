#ifndef __CL_TRAY__H
#define __CL_TRAY__H

#include "cl_base.h"

// Лоток бумаги
class cl_tray : public cl_base
{
    int capacity = 0;
    int sheets = 0;
    int load_ticks_left = 0; // 3 такта загрузки

public:
    cl_tray(cl_base* p_head_object, string s_object_name);

    void init(int m);

    int get_sheets() { return sheets; }

    // LOAD_PAPER_TRAY: начать загрузку (3 такта)
    void start_loading();

    void do_tact_loading();
    bool is_loading();

    void consume(int x);

    int get_number_class() { return 5; } // не обязательно
};

#endif