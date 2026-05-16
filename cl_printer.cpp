#include "cl_printer.h"
#include "cl_tray.h"
#include "cl_cartridge.h"
#include "cl_pc.h"
#include "cl_document.h"
#include <sstream>

cl_printer::cl_printer(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_printer::init(int q_per_tact, cl_tray* p_tray, cl_cartridge* p_cart, cl_document* p_current)
{
    q = q_per_tact;
    tray = p_tray;
    cartridge = p_cart;
    current_doc = p_current;
}

void cl_printer::set_pcs(const vector<cl_pc*>& v)
{
    pcs = v;
}

void cl_printer::handler_add_request(string doc_path)
{
    cl_base* p = get_pointer_by_path(doc_path);
    if (p == nullptr) return;

    cl_document* d = (cl_document*)p;

    request r;
    r.doc_path = doc_path;
    r.tact_added = d->get_tact_added();
    r.pc_number = d->get_pc_number();

    // вставка по tact_added (пузырьком назад)
    int pos = (int)queue_req.size();
    queue_req.push_back(r);

    while (pos > 0 && queue_req[pos - 1].tact_added > queue_req[pos].tact_added)
    {
        request tmp = queue_req[pos - 1];
        queue_req[pos - 1] = queue_req[pos];
        queue_req[pos] = tmp;
        pos--;
    }
}

void cl_printer::do_tact()
{
    // 1. Если идёт загрузка лотка — уменьшаем таймер
    if (tray->is_loading())
    {
        tray->do_tact_loading();
        return;
    }

    // 2. Если идёт замена картриджа — уменьшаем таймер
    if (cartridge->is_replacing())
    {
        power_on = false;
        cartridge->do_tact_replacing();

        // Если замена завершена — включаем принтер
        if (!cartridge->is_replacing())
        {
            power_on = true;
            queue_req.clear();   // очередь очищается по ТЗ
        }

        return;
    }

    // 3. Если принтер выключен — ничего не делаем
    if (!power_on)
        return;

    // 4. Если нет бумаги — ждём команду загрузки
    if (tray->get_sheets() == 0)
        return;

    // 5. Если нет чернил — ждём команду замены
    if (cartridge->get_remaining() == 0)
        return;

    // 6. Если текущего документа нет — берём следующий
    if (current_doc->get_pages_left() == 0)
    {
        if (queue_req.empty())
            return;

        cl_base* p = get_pointer_by_path(queue_req[0].doc_path);

        if (p != nullptr)
        {
            cl_document* d = (cl_document*)p;

            current_doc->init(
                d->get_pc_number(),
                d->get_title(),
                d->get_pages_left(),
                d->get_tact_added()
            );

            cl_pc* pc = (cl_pc*)d->get_p_head_object();

            if (pc != nullptr)
            {
                pc->remove_document_name(d->get_s_object_name());
                pc->del_sub_obj(d->get_s_object_name());
            }
        }

        queue_req.erase(queue_req.begin());
    }

    // 7. Печать документа
    int pages_left = current_doc->get_pages_left();

    if (pages_left == 0)
        return;

    int can_print = q;

    if (can_print > pages_left)
        can_print = pages_left;

    if (can_print > tray->get_sheets())
        can_print = tray->get_sheets();

    if (can_print > cartridge->get_remaining())
        can_print = cartridge->get_remaining();

    tray->consume(can_print);
    cartridge->consume(can_print);

    current_doc->set_pages_left(pages_left - can_print);

    if (current_doc->get_pages_left() == 0)
        current_doc->clear();
}

int cl_printer::get_current_pages_left()
{
    return current_doc->get_pages_left();
}

int cl_printer::get_queue_size()
{
    return (int)queue_req.size();
}

string cl_printer::get_system_status_line(int tact_number)
{
    // Printer tact: t; print document: r; queue documents: Q  PC: (j:c) ...
    ostringstream out;
    out << "Printer tact: " << tact_number
        << "; print document: " << get_current_pages_left()
        << "; queue documents: " << get_queue_size();

    // считаем ПК только по очереди принтера (как ты просила)
    vector<int> pc_nums;
    vector<int> pc_cnts;

    for (int i = 0; i < (int)queue_req.size(); i++)
    {
        int pc = queue_req[i].pc_number;
        int pos = -1;
        for (int j = 0; j < (int)pc_nums.size(); j++)
            if (pc_nums[j] == pc) { pos = j; break; }

        if (pos == -1)
        {
            int ins = (int)pc_nums.size();
            pc_nums.push_back(pc);
            pc_cnts.push_back(1);
            while (ins > 0 && pc_nums[ins - 1] > pc_nums[ins])
            {
                int t1 = pc_nums[ins - 1]; pc_nums[ins - 1] = pc_nums[ins]; pc_nums[ins] = t1;
                int t2 = pc_cnts[ins - 1]; pc_cnts[ins - 1] = pc_cnts[ins]; pc_cnts[ins] = t2;
                ins--;
            }
        }
        else pc_cnts[pos]++;
    }

    if (!pc_nums.empty())
    {
        out << "  PC:"; // две позиции пробела перед PC: как в примере
        for (int i = 0; i < (int)pc_nums.size(); i++)
            out << " (" << pc_nums[i] << ":" << pc_cnts[i] << ")";
    }

    return out.str();
}

void cl_printer::clear_queue()
{
    queue_req.clear();
}