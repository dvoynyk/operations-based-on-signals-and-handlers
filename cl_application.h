#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H

#include "cl_base.h"
#include <vector>

class cl_input;
class cl_output;
class cl_printer;
class cl_tray;
class cl_cartridge;
class cl_pc;
class cl_document;

class cl_application : public cl_base
{
    cl_input* p_input = nullptr;
    cl_output* p_output = nullptr;
    cl_printer* p_printer = nullptr;
    cl_tray* p_tray = nullptr;
    cl_cartridge* p_cartridge = nullptr;
    cl_document* p_current_doc = nullptr;

    vector<cl_pc*> pcs;

    int n = 0;
    int m = 0, k = 0, q = 0;

public:
    cl_application(cl_base* p_head_object);

    void build_tree_objects();
    int exec_app();

    // сигнал для отправки строк на Output
    void signal_msg(string& s);

    int get_number_class() { return 1; } // класс корня
};

#endif