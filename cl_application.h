#pragma once
#include "cl_base.h"
using namespace std;
class cl_application : public cl_base
{
public:
	cl_application(cl_base* p_head_object);
	void build_tree_objects();
	int exec_app();
};