#include "cl_application.h"
#include "cl_node.h"
#include <iostream>
#include <string>
#include <vector>

cl_application::cl_application(cl_base* p_head_object)
    : cl_base(p_head_object)
{
}

void cl_application::build_tree_objects()
{
    cl_base* header = this;
    cl_base* sub = nullptr;
    std::string head_name, sub_name;

    std::cin >> head_name;
    change_s_object_name(head_name);

    while (true)
    {
        std::cin >> head_name >> sub_name;
        if (head_name == sub_name)
            break;

        if (sub != nullptr && head_name == sub->get_s_object_name())
            header = sub;

        if (head_name == header->get_s_object_name())
        {
            if (header->get_adress_subordinate_object_name(sub_name) == nullptr)
                sub = new cl_node(header, sub_name);
        }
    }
}

int cl_application::exec_app()
{
    print_three();
    int index, level;
    std::string new_name;

    while (std::cin >> level)
    {
        if (level == 0)
            break;

        std::cin >> index >> new_name;
        std::vector<cl_base*> current_level;
        current_level.push_back(this);
        int current_number = 1;

        while (current_number < level)
        {
            std::vector<cl_base*> next_level;
            for (size_t i = 0; i < current_level.size(); ++i)
            {
                for (int j = 1; j <= current_level[i]->get_count_subordinate_objects(); ++j)
                {
                    next_level.push_back(current_level[i]->get_adress_subordinate_object_index(j));
                }
            }
            current_level = next_level;
            ++current_number;
        }

        if (index >= 1 && index <= static_cast<int>(current_level.size()))
        {
            current_level[index - 1]->change_s_object_name(new_name);
        }
    }

    print_three();
    return 0;
}