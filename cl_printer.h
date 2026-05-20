#ifndef CL_PRINTER_H
#define CL_PRINTER_H
#include "cl_base.h"
#include <vector>
#include <string>

class cl_tray;
class cl_cartridge;
class cl_pc;
class cl_document;

class cl_printer : public cl_base	// Класс пульта управления принтером
{
public:
	struct request	// СТРУКТУРА внутри класса пульта управления принтером cl_printer
	{
		string doc_path; 	// Абсолютная координата документа
		int tact_added; 	// Такт постановки
		int pc_number; 	// Номер ПК
	};
	cl_printer(cl_base* p_head_object, string s_object_name);
	void start_replacing_cartridge();
	void power_off();
	void init(int q_per_tact, cl_tray* p_tray, cl_cartridge* p_cart, cl_document* p_current);	// Инициализация полей пульта управления принтером
	void set_pcs(vector <cl_pc*> v);	// Список объектов ПК
	void handler_add_request(string doc_path);	// Обработчик запроса на печать от ПК
	void do_tact();	// Один такт работы принтера
	int get_current_pages_left();	// Получение количества оставшихся страниц у текущего документа
	int get_queue_size();	// Получение количества объектов структуры resuest в массиве
	void clear_queue();	// Удаление очереди запросов
	string get_system_status_line(int tact_number);	// Получение статуса системы
private:
	int q = 1; 	// Количество листов за 1 такт
	bool power_on = true; 	// Состояние включения
	cl_tray* tray = nullptr; 	// Хранение адреса на объект класса cl_tray
	cl_cartridge* cartridge = nullptr; 	// Хранение адреса на объект класса cl_cartridge
	cl_document* current_doc = nullptr; 	// Хранение адреса на объект класса cl_document
	vector <cl_pc*> pcs; 	// Динамический массив для хранения адресов на объекты класса cl_pc
	vector <request> queue_req; 	// Динамический массив для хранения очереди запросов на печать в принтере
};
#endif    // CL_PRINTER_H