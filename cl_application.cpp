#include "cl_application.h"
#include "cl_base.h"
#include <iostream>
using namespace std;
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object) {}
void cl_application::build_tree_objects()
{
	cl_base* header = this;
	cl_base* sub = nullptr;
	string head_name, sub_name;

	cin >> head_name;
	change_s_object_name(head_name);
	while (true)
	{
		cin >> head_name >> sub_name;
		if (head_name == sub_name)
		{
			break;
		}
		if (sub != nullptr && head_name == sub->get_s_object_name())
		{
			header = sub;
		}
		if (header->get_adress_subordinate_object_name(sub_name) == nullptr)
		{
			sub = new cl_base(header, sub_name);
		}
	}
}
int cl_application::exec_app()
{
	print_three();
	int index, level;
	string new_name;
	while (cin >> level)
	{
		if (level == 0)
		{
			break;
		}
		cin >> index >> new_name;
		vector <cl_base*> current_level;
		current_level.push_back(this);
		int current_number = 1;
		while (current_number < level)
		{
			vector <cl_base*> next_level;
			for (int i = 0; i < current_level.size(); i++)
			{
				for (int j = 1; j <= current_level[i]->get_count_subordinate_objects(); j++)
				{
					next_level.push_back(current_level[i]->get_adress_subordinate_object_index(j));
				}
			}
			current_level = next_level;
			current_number++;
		}
		if (index >= 1 && index <= current_level.size())
		{
			current_level[index - 1]->change_s_object_name(new_name);
		}

	}
	print_three();
	return(0);
}