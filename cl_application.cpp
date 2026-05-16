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
    // Создание объектов системы
    p_input = new cl_input(this, "Input");
    p_output = new cl_output(this, "Output");
    p_printer = new cl_printer(this, "Printer");

    p_tray = new cl_tray(p_printer, "Tray");
    p_cartridge = new cl_cartridge(p_printer, "Cartridge");
    p_current_doc = new cl_document(p_printer, "Current_document");

    // Связь вывода
    set_connect(
        SIGNAL_D(cl_application::signal_msg),
        p_output,
        HANDLER_D(cl_output::handler_print)
    );

    // Включаем все объекты
    set_state_branch(1);

    string line;

    // Количество ПК
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);
    istringstream iss1(line);
    iss1 >> n;

    // Параметры m k q
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);
    istringstream iss2(line);
    iss2 >> m >> k >> q;

    // End of settings
    p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);

    // Инициализация принтера
    p_tray->init(m);
    p_cartridge->init(k);
    p_current_doc->clear();
    p_printer->init(q, p_tray, p_cartridge, p_current_doc);

    // Создание ПК
    for (int i = 1; i <= n; i++)
    {
        string name = "PC_" + to_string(i);
        cl_pc* pc = new cl_pc(this, name, i);
        pcs.push_back(pc);

        pc->set_connect(
            SIGNAL_D(cl_pc::signal_to_printer),
            p_printer,
            HANDLER_D(cl_printer::handler_add_request)
        );
    }

    p_printer->set_pcs(pcs);

    set_state_branch(1);

    string msg = "Ready to work";
    emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
}

int cl_application::exec_app()
{
    int tact = 1;
    string line;

    // Читаем команды до выключения системы
    while (p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line), cin)
    {
        string cmd = line;

        // SHOWTREE
        if (cmd == "SHOWTREE")
        {
            print_tree_status();
            return 0;
        }

        // Завершение работы
        if (cmd == "Turn off the system")
        {
            string msg = "Turn off the system";
            emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
            return 0;
        }

        // Paper tray condition
        if (cmd == "Paper tray condition")
        {
            string msg = "Paper tray condition: " + to_string(p_tray->get_sheets());
            emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }

        else if (cmd == "Load paper tray")
        {
            p_tray->start_loading();
        }

        else if (cmd == "Replace cartridge")
        {
            p_printer->clear_queue();
            p_cartridge->start_replacing();
        }

        // Cartridge condition
        else if (cmd == "Cartridge condition")
        {
            string msg = "Cartridge: " +
                to_string(p_cartridge->get_remaining());
            emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }

        // System status
        else if (cmd == "System status")
        {
            string msg = p_printer->get_system_status_line(tact);
            emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
        }

        // Команды PC
        else if (cmd.substr(0, 2) == "PC")
        {
            istringstream iss(cmd);
            string w1, w2;
            iss >> w1 >> w2;

            // PC condition
            if (w2 == "condition")
            {
                int pc_num;
                iss >> pc_num;

                for (int i = 0; i < pcs.size(); i++)
                {
                    if (pcs[i]->get_pc_number() == pc_num)
                    {
                        string msg = pcs[i]->get_condition_line();
                        emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
                        break;
                    }
                }
            }
            else
            {
                // PC j pages title
                int pc_num = stoi(w2);
                int pages;
                iss >> pages;

                string title;
                getline(iss, title);

                for (int i = 0; i < pcs.size(); i++)
                {
                    if (pcs[i]->get_pc_number() == pc_num &&
                        pcs[i]->is_on())
                    {
                        string obj_name = "doc_" + to_string(tact);

                        cl_document* d =
                            new cl_document(pcs[i], obj_name);

                        d->init(pc_num, title, pages, tact);
                        d->set_ready(1);

                        pcs[i]->push_document_name(obj_name);

                        string path = d->get_absolute_path();

                        pcs[i]->emit_signal(
                            SIGNAL_D(cl_pc::signal_to_printer),
                            path
                        );

                        break;
                    }
                }
            }
        }

        // Выполнение такта
        p_printer->do_tact();   
        tact++;
    }

    return 0;
}