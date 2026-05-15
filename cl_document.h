#ifndef __CL_DOCUMENT__H
#define __CL_DOCUMENT__H

#include "cl_base.h"

// Документ: может быть под ПК (в очереди ПК) или "текущий печатаемый" под принтером
class cl_document : public cl_base
{
    int pc_number = 0;
    string title;
    int pages_left = 0;
    int tact_added = 0;

public:
    cl_document(cl_base* p_head_object, string s_object_name);

    void init(int pc, const string& t, int pages, int tact);

    int get_pc_number() { return pc_number; }
    string get_title() { return title; }
    int get_pages_left() { return pages_left; }
    int get_tact_added() { return tact_added; }

    void set_pages_left(int v) { pages_left = v; }
    void clear();

    int get_number_class() { return 6; } // не обязательно
};

#endif