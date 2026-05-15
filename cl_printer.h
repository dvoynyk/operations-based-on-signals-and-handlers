#ifndef __CL_PRINTER__H
#define __CL_PRINTER__H

#include "cl_base.h"
#include <vector>
#include <string>

class cl_tray;
class cl_cartridge;
class cl_pc;
class cl_document;

// Принтер (пульт управления): очередь запросов + печать по тактам
class cl_printer : public cl_base
{
public:
    struct request
    {
        string doc_path;   // абсолютная координата документа (например /PC_3/doc_7)
        int tact_added;    // такт постановки
        int pc_number;     // номер ПК
    };

private:
    int q = 1; // листов за такт
    bool power_on = true;

    cl_tray* tray = nullptr;
    cl_cartridge* cartridge = nullptr;
    cl_document* current_doc = nullptr;

    vector<cl_pc*> pcs;
    vector<request> queue_req;

public:
    cl_printer(cl_base* p_head_object, string s_object_name);

    void init(int q_per_tact, cl_tray* p_tray, cl_cartridge* p_cart, cl_document* p_current);
    void set_pcs(const vector<cl_pc*>& v);

    // обработчик от ПК: пришла координата документа -> добавить в очередь запросов
    void handler_add_request(string doc_path);

    // 1 такт работы
    void do_tact();

    int get_current_pages_left();
    int get_queue_size();
    string get_system_status_line(int tact_number);

    int get_number_class() { return 1; } // не обязательно
};

#endif