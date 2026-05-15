#include "cl_application.h"
#include "cl_input.h"
#include "cl_output.h"
#include "cl_printer.h"
#include "cl_tray.h"
#include "cl_cartridge.h"
#include "cl_pc.h"
#include "cl_document.h"

#include <sstream>
#include <iostream>
using namespace std;

static string trim_spaces(const string& s)
{
    int L = 0;
    while (L < (int)s.size() && (s[L] == ' ' || s[L] == '\t' || s[L] == '\r')) L++;
    int R = (int)s.size() - 1;
    while (R >= L && (s[R] == ' ' || s[R] == '\t' || s[R] == '\r')) R--;
    return s.substr(L, R - L + 1);
}

cl_application::cl_application(cl_base* p_head_object)
    : cl_base(p_head_object, "System")
{
}

void cl_application::signal_msg(string& s)
{
    // текст уже сформирован — ничего не меняем
}

void cl_application::build_tree_objects()
{
    // Создаём дерево системы
    p_input = new cl_input(this, "Input");
    p_output = new cl_output(this, "Output");
    p_printer = new cl_printer(this, "Printer");

    p_tray = new cl_tray(p_printer, "Tray");
    p_cartridge = new cl_cartridge(p_printer, "Cartridge");
    p_current_doc = new cl_document(p_printer, "Current_document");

    // Связь: System.signal_msg -> Output.handler_print
    this->set_connect(SIGNAL_D(cl_application::signal_msg), p_output, HANDLER_D(cl_output::handler_print));

    // Всё включаем
    set_state_branch(1);

    // Читаем настройки (3 строки)
    string line;

    // 1) n
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);
    line = trim_spaces(line);
    n = atoi(line.c_str());

    // 2) m k q
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);
    line = trim_spaces(line);
    {
        istringstream iss(line);
        iss >> m >> k >> q;
    }

    // 3) End of settings
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);

    // Инициализация принтера
    p_tray->init(m);
    p_cartridge->init(k);
    p_current_doc->clear();
    p_printer->init(q, p_tray, p_cartridge, p_current_doc);

    // Создаём ПК 1..n, связываем их с принтером
    for (int i = 1; i <= n; i++)
    {
        string pc_name = "PC_" + to_string(i);
        cl_pc* pc = new cl_pc(this, pc_name, i);
        pcs.push_back(pc);

        // PC.signal_to_printer -> Printer.handler_add_request
        pc->set_connect(SIGNAL_D(cl_pc::signal_to_printer), p_printer, HANDLER_D(cl_printer::handler_add_request));
    }
    p_printer->set_pcs(pcs);

	set_state_branch(1);

    // Готовность системы
    string msg = "Ready to work";
    this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
}

int cl_application::exec_app()
{
    int tact = 1;
    string line;

    while (true)
    {
        // 1) прочитать строку команды (пустая строка = пустая команда)
        p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);

        // если вдруг конец ввода
        if (!cin && line.size() == 0) return 0;

        string cmd = trim_spaces(line);

        // SHOWTREE: вывести дерево готовности и завершить
        if (cmd == "SHOWTREE")
        {
            print_tree_status();
            return 0;
        }

        // Turn off the system: вывести и завершить
        if (cmd == "Turn off the system")
        {
            string msg = "Turn off the system";
            this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
            return 0;
        }

        // 2) обработка команд статуса
        if (cmd == "Paper tray condition")
        {
            ostringstream out;
            out << "Paper tray condition: " << p_tray->get_sheets();
            string msg = out.str();
            this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }
        else if (cmd == "Cartridge condition")
        {
            ostringstream out;
            out << "Cartridge: " << p_cartridge->get_remaining();
            string msg = out.str();
            this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }
        else if (cmd == "System status")
        {
            string msg = p_printer->get_system_status_line(tact);
            this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }
        else
        {
            // 3) команды PC...
            if (cmd.size() >= 2 && cmd[0] == 'P' && cmd[1] == 'C')
            {
                istringstream iss(cmd);
                string w1, w2;
                iss >> w1; // PC
                iss >> w2;

                if (w2 == "condition")
                {
                    int pc_num;
                    iss >> pc_num;

                    cl_pc* pc = nullptr;
                    for (int i = 0; i < (int)pcs.size(); i++)
                        if (pcs[i]->get_pc_number() == pc_num) { pc = pcs[i]; break; }

                    if (pc != nullptr)
                    {
                        string msg = pc->get_condition_line();
                        this->emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
                    }
                }
                else
                {
                    // PC <номер> <листы> <название...>
                    int pc_num = atoi(w2.c_str());
                    int pages = 0;
                    iss >> pages;

                    string title;
                    getline(iss, title);
                    title = trim_spaces(title);

                    cl_pc* pc = nullptr;
                    for (int i = 0; i < (int)pcs.size(); i++)
                        if (pcs[i]->get_pc_number() == pc_num) { pc = pcs[i]; break; }

                    if (pc != nullptr && pc->is_on())
                    {
                        // создаём документ-подчинённый ПК
                        string obj_name = "doc_" + to_string(tact); // уникально по такту
                        cl_document* d = new cl_document(pc, obj_name);
                        d->init(pc_num, title, pages, tact);
                        d->set_ready(1);

                        // добавляем в очередь ПК
                        pc->push_document_name(obj_name);

                        // посылаем запрос принтеру (координата документа)
                        string doc_path = d->get_absolute_path();
                        pc->emit_signal(SIGNAL_D(cl_pc::signal_to_printer), doc_path);
                    }
                }
            }

            // пустая команда: cmd == "" -> просто такт, ничего не делаем
        }

        // 4) отработка такта принтера
        p_printer->do_tact();

        // 5) следующий такт
        tact++;
    }

    return 0;
}