#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_base.h"
#include <vector>

class cl_input;
class cl_output;
class cl_printer;
class cl_tray;
class cl_cartridge;
class cl_pc;
class cl_document;

class cl_application : public cl_base	// система моделирования работы сетевого принтера
{
public:

	cl_application(cl_base* p_head_object);
	void build_tree_objects();	// Построение дерева иерархии объектов и подготовка системы к работе
	int exec_app();	// Функционирование системы и обработка команд
	void signal_msg(string& s);	// Метод точки входа сигнала

private:

	cl_input* p_input = nullptr; 	// Хранение адреса на объект класса cl_input
	cl_output* p_output = nullptr; 	// Хранение адреса на объект класса cl_output
	cl_printer* p_printer = nullptr; 	// Хранение адреса на объект класса cl_printer
	cl_tray* p_tray = nullptr; // Хранение адреса на объект класса cl_tray
	cl_cartridge* p_cartridge = nullptr; 	// Хранение адреса на объект класса cl_cartridge
	cl_document* p_current_doc = nullptr; 	// Хранение адреса на объекта класса cl_document

	int n = 0; 	// Количество ПК
	int m = 0; 	// Вместимость лотка
	int k = 0; 	// Количество печатаемых листов от одного картриджа
	int q = 0; 	// Количество листов, печатаемых за один такт

	vector<cl_pc*> pcs; // Динамический массив, хранящий адреса на объекты класса cl_pc
};
#endif    // CL_APPLICATION_H