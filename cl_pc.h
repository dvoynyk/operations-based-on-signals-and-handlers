#ifndef __CL_PC__H
#define __CL_PC__H

#include "cl_base.h"
#include <vector>

// ПК: хранит очередь документов (имена подчинённых объектов-документов)
class cl_pc : public cl_base
{
    int pc_number = 0;
    bool turned_on = true;
    vector<string> doc_queue; // порядок постановки на ПК

public:
    cl_pc(cl_base* p_head_object, string s_object_name, int number);

    int get_pc_number() { return pc_number; }
    bool is_on() { return turned_on; }

    void push_document_name(const string& obj_name);
    void remove_document_name(const string& obj_name);   // нужно, когда принтер забирает документ
    vector<string> get_document_names();                 // нужно для восстановления очереди после замены картриджа

    int get_queue_size();

    string get_condition_line();    

    // Сигнал на принтер (передаём строку как есть: координату документа)
    void signal_to_printer(string& s);

    int get_number_class() { return 4; } // не обязательно
};

#endif