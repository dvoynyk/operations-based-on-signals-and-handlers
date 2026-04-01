#include "cl_base.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

cl_base::cl_base(cl_base* p_head_object, string s_object_name)
{
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object)
	{
		p_head_object->subordinate_objects.push_back(this);
	}
}
bool cl_base::change_s_object_name(string new_name)
{
	if (p_head_object == nullptr)
	{
		s_object_name = new_name;
		return true;
	}
	for (int i = 0; i < p_head_object->subordinate_objects.size(); i++)
	{
		if (p_head_object->subordinate_objects[i] != this && p_head_object->subordinate_objects[i]->s_object_name == new_name)
		{
			return false;
		}
	}
	s_object_name = new_name;
	return true;
}
string cl_base::get_s_object_name()
{
	return s_object_name;
}
cl_base* cl_base::get_p_head_object()
{
	return p_head_object;
}
int cl_base::get_count_subordinate_objects()
{
	return subordinate_objects.size();
};
void cl_base::print_three()
{
	cout << s_object_name << endl;
	vector<cl_base*> current_level;
	current_level.push_back(this);
	while (!current_level.empty())
	{
		vector<cl_base*> next_level;
		bool has_children = false;

		for (int i = 0; i < current_level.size(); i++)
		{
			if (current_level[i]->subordinate_objects.size() > 0)
			{
				has_children = true;
				cout << current_level[i]->s_object_name;

				for (int j = 0; j < current_level[i]->subordinate_objects.size(); j++)
				{
					cout << "  " << current_level[i]->subordinate_objects[j]->s_object_name;
					next_level.push_back(current_level[i]->subordinate_objects[j]);
				}
				cout << endl;
			}
		}
		if (!has_children)
		{
			break;
		}
		current_level = next_level;
	}
};
cl_base* cl_base::get_adress_subordinate_object_name(string name)
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		if (subordinate_objects[i]->s_object_name == name)
		{
			return subordinate_objects[i];
		}
	}
	return nullptr;
};
cl_base* cl_base::get_adress_subordinate_object_index(int index)
{
	if (index < 1 || index > subordinate_objects.size())
	{
		return nullptr;
	}
	return subordinate_objects[index - 1];
};

cl_base::~cl_base()
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		delete subordinate_objects[i];
	}
}