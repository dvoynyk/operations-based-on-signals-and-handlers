#include "cl_document.h"

cl_document::cl_document(cl_base* p_head_object, string s_object_name)
    : cl_base(p_head_object, s_object_name)
{
}

void cl_document::init(int pc, const string& t, int pages, int tact)
{
    pc_number = pc;
    title = t;
    pages_left = pages;
    tact_added = tact;
}

void cl_document::clear()
{
    pc_number = 0;
    title = "";
    pages_left = 0;
    tact_added = 0;
}