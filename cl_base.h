#pragma once
#include <iostream>
#include <vector>
#include <string>

class cl_base
{
    std::string s_object_name;
    cl_base* p_head_object;
    std::vector<cl_base*> subordinate_objects;

public:
    cl_base(cl_base* p_head_object, std::string s_object_name = "Base_object");
    bool change_s_object_name(std::string new_name);
    std::string get_s_object_name();
    cl_base* get_p_head_object();
    int get_count_subordinate_objects();
    void print_three();
    cl_base* get_adress_subordinate_object_name(std::string name);
    cl_base* get_adress_subordinate_object_index(int index);
    ~cl_base();
};