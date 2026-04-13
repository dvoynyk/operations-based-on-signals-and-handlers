#include "cl_application.h"
#include "cl_base.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <iostream>
using namespace std;
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object) {}
void cl_application::build_tree_objects()
{
	string root_name;
	cin >> root_name;
	change_s_object_name(root_name);
	string head_name, sub_name;
	int cl_obj;
	cl_base* p_last = this;
	while (cin >> head_name)
	{
		if (head_name == "endtree")
		{
			return;
		}
		cin >> sub_name >> cl_obj;
		cl_base* p_head = p_last->search_object_all_three_name(head_name);
		if (!p_head)
		{
			continue;
		}
		if (p_head->get_adress_subordinate_object_name(sub_name) != nullptr)
		{
			continue;
		}
		if (search_object_all_three_name(sub_name) != nullptr)
		{
			continue;
		}
		cl_base* p_new = nullptr;
		switch (cl_obj)
		{
		case 2:
			p_new = new cl_2(p_head, sub_name);
			break;
		case 3:
			p_new = new cl_3(p_head, sub_name);
			break;
		case 4:
			p_new = new cl_4(p_head, sub_name);
			break;
		case 5:
			p_new = new cl_5(p_head, sub_name);
			break;
		case 6:
			p_new = new cl_6(p_head, sub_name);
			break;
		default: break;
		}
		if (p_new != nullptr)
		{
			p_last = p_new;
		}
	}
}
int cl_application::exec_app()
{
	cout << "Object tree" << endl;
	print_tree();
	string head_name;
	int state;
	while (cin >> head_name >> state)
	{
		cl_base* p_object = search_object_all_three_name(head_name);
		if (p_object != nullptr)
		{
			p_object->set_ready(state);
		}
	}
	cout << "The tree of objects and their readiness" << endl;
	print_tree_status();
	return(0);
}