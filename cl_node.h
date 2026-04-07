#pragma once
#include "cl_base.h"
#include <string>

class cl_node : public cl_base
{
public:
    cl_node(cl_base* p_head_object, std::string s_object_name);
};