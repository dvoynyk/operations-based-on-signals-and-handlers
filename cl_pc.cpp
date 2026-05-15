#include "cl_pc.h"
#include "cl_document.h"
#include <sstream>

cl_pc::cl_pc(cl_base* p_head_object, string s_object_name, int number)
    : cl_base(p_head_object, s_object_name), pc_number(number)
{
}

void cl_pc::push_document_name(const string& obj_name)
{
    doc_queue.push_back(obj_name);
}

void cl_pc::remove_document_name(const string& obj_name)
{
    for (int i = 0; i < (int)doc_queue.size(); i++)
    {
        if (doc_queue[i] == obj_name)
        {
            doc_queue.erase(doc_queue.begin() + i);
            return;
        }
    }
}

vector<string> cl_pc::get_document_names()
{
    return doc_queue; // копия
}

int cl_pc::get_queue_size()
{
    return (int)doc_queue.size();
}

string cl_pc::get_condition_line()
{
    // PC condition j turned on doc1; doc2;
    // PC condition j turned off
    ostringstream out;
    out << "PC condition " << pc_number << " ";
    if (!turned_on)
    {
        out << "turned off";
        return out.str();
    }

    out << "turned on";

    for (int i = 0; i < (int)doc_queue.size(); i++)
    {
        cl_base* p = get_adress_subordinate_object_name(doc_queue[i]);
        cl_document* d = (cl_document*)p;
        if (d != nullptr)
        {
            out << " " << d->get_title() << ";";
        }
    }
    return out.str();
}

void cl_pc::signal_to_printer(string& s)
{
    // Ничего не меняем. Содержимое s будет обработано принтером.
}