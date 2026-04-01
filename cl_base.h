#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cl_base
{
	string s_object_name;
	cl_base* p_head_object;
	vector < cl_base* > subordinate_objects;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	bool change_s_object_name(string new_name);
	string get_s_object_name();
	cl_base* get_p_head_object();
	int get_count_subordinate_objects();
	void print_three();
	cl_base* get_adress_subordinate_object_name(string name);
	cl_base* get_adress_subordinate_object_index(int index);
	~cl_base();
};
