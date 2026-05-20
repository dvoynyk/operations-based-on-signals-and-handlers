#ifndef CL_PC_H
#define CL_PC_H
#include "cl_base.h"
#include <vector>
class cl_pc : public cl_base	// класс ПК
{
public:
	cl_pc(cl_base* p_head_object, string s_object_name, int number);
	int get_pc_number();	// Получение номера ПК
	bool is_on();	// Проверка включения ПК
	void push_document_name(string obj_name);	// Добавление документа в очередь
	void remove_document_name(string obj_name);	// Удаление документа из очереди
	vector<string> get_document_names();	// Восстановление очереди после замены картриджа
	int get_queue_size();	// Получение количества документов в очереди
	string get_condition_line();	// Получение состояние ПК
	void signal_to_printer(string& s);	// Получение сигнала на принтер
private:
	int pc_number = 0; 	// Номер класса компьютера
	bool turned_on = true; 	// Состояние готовности ПК
	vector<string> doc_queue; 	// Динамический массив с строковым названием документа
};
#endif    // CL_PC_H