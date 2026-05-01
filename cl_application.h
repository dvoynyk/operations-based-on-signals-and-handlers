#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H

#include "cl_base.h"
using namespace std;
class cl_application : public cl_base     // Наследование от базового класса
{
public:
	cl_application(cl_base* p_head_object);// Конструктор класса cl_application
	void build_tree_objects();            // Заголовок метода построения объекта
	int exec_app();                       // Заголовок метода запуска системы и обработки команд
	int get_number_class();               // Заголовок метода получения номера класса
	void signal(string& message);         // Заголовок метода сигнала 
	void handler(string message);         // Заголовок метода обработчика
};

#endif
