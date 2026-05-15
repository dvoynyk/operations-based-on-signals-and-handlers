#include "cl_application.h"

int main()
{
    cl_application ob(nullptr);
    ob.build_tree_objects();
    return ob.exec_app();
}