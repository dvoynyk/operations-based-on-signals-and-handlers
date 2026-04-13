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
};
cl_base* cl_base::search_object_branch_name(string name)
{
	vector<cl_base*> objects;
	objects.push_back(this);
	cl_base* result = nullptr;
	int count = 0;
	while (!objects.empty())
	{
		cl_base* current = objects.back();
		objects.pop_back();
		if (current->s_object_name == name)
		{
			count++;
			result = current;
		}
		for (int i = 0; i < current->subordinate_objects.size(); i++)
		{
			objects.push_back(current->subordinate_objects[i]);
		}
	}
	if (count == 1)
	{
		return result;
	}
	return nullptr;
};
cl_base* cl_base::search_object_all_three_name(string name)
{
	cl_base* root = this;
	while (root->p_head_object != nullptr)
	{
		root = root->p_head_object;
	}
	return root->search_object_branch_name(name);
};
void cl_base::print_tree(int level)
{
	for (int i = 0; i < level; i++)
	{
		cout << " ";
	}
	cout << s_object_name << endl;
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		subordinate_objects[i]->print_tree(level + 1);
	}
};
void cl_base::print_tree_status(int level)
{
	for (int i = 0; i < level; i++)
	{
		cout << " ";
	}
	cout << s_object_name;
		if (i_state != 0)
		{
			cout << " is ready";
		}
		else
		{
			cout << " is not ready";
		}
	cout << endl;
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		subordinate_objects[i]->print_tree_status(level + 1);
	}
}
void cl_base::set_ready(int state)
{
	if (p_head_object == nullptr || p_head_object->i_state != 0)
	{
		i_state = state;
	}
	if (state == 0)
	{
		i_state = state;
		for (int i = 0; i < subordinate_objects.size(); i++)
		{
			subordinate_objects[i]->set_ready(state);
		}
	}
};