#include "cl_printer.h"
#include "cl_tray.h"
#include "cl_cartridge.h"
#include "cl_pc.h"
#include "cl_document.h"
#include "cl_base.h"
#include <sstream>
cl_printer::cl_printer(cl_base* p_head_object, string s_object_name)
	:cl_base(p_head_object, s_object_name)
{

}
void cl_printer::init(int q_per_tact, cl_tray* p_tray, cl_cartridge* p_cart, cl_document* p_current)
{
	//--------------------------------------------------
	// Инициализация полей пульта управления принтером
	// Параметры:
	//     int q_per_tact, cl_tray* p_tray, cl_cartridge* p_cart, cl_document* p_current, количество листов, адрес объекта лотка для бумаги, адрес объекта картриджа, адрес объекта документа   
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	// 1.1 Присвоение полю q значения параметра q_per_tact
	q = q_per_tact;
	// 2.1 Присвоение полю tray значения параметра p_tray
	tray = p_tray;
	// 3.1 Присвоение полю cartridge значения параметра p_cart
	cartridge = p_cart;
	// 4.1 Присвоение полю current_doc значения параметра p_current
	current_doc = p_current;
}
void cl_printer::set_pcs(vector <cl_pc*> v)
{
	//--------------------------------------------------
	// Список объектов ПК
	// Параметры:
	//     vector <cl_pc*> v, динамический массив с адресами объектов класса cl_pc
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	// 1.1 Присвоение полю pcs значения параметра v
	pcs = v;
}
void cl_printer::handler_add_request(string doc_path)
{
	//--------------------------------------------------
	// Обработчик запроса на печать от ПК
	// Параметры:
	//     string doc_path, путь документа
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	// 1.1 Инициализация указателя p адресом объекта документа по значению пути параметра doc_path
	cl_base* p = get_pointer_by_path(doc_path);
	// 2.1 Указатель p равен значению нулевого указателя
	if (p == nullptr)
	{
		return;
	}
	// 2.2 Инициализация указателя d на объекта класса cl_document приведенным типом значения указателя p
	cl_document* d = (cl_document*)p;
	// 3.1 Объявление объекта r структуры request 
	request r;
	// 4.1 Присвоение полю doc_path объекта структуры r значения параметра doc_path
	r.doc_path = doc_path;
	// 5.1 Присвоение полю tact_added объекта r результата вызова метода количества тактов у объекта документа по адресу d
	r.tact_added = d->get_tact_added();
	// 6.1 Присвоение полю pc_number объекта r результата вызова метода получения номера ПК у объекта документа по адресу d
	r.pc_number = d->get_pc_number();
	// 7.1 Добавление объекта запроса r структуры request в динамический массив с хранением очереди на печать queue_req
	queue_req.push_back(r);
}
void cl_printer::do_tact()
{
	if (cartridge->is_replacing())
	{
		cartridge->do_tact_replacing();

		if (!cartridge->is_replacing())
			power_on = true;

		return;
	}

	if (!power_on)
		return;

	// Загрузка бумаги
	if (tray->is_loading())
	{
		tray->do_tact_loading();
	}

	if (tray->get_sheets() == 0)
	{
		if (!tray->is_loading())
			tray->start_loading();
		return;
	}

	if (cartridge->get_remaining() == 0)
	{
		power_on = false;
		queue_req.clear();
		return;
	}

	if (current_doc->get_pages_left() == 0)
	{
		if (queue_req.empty())
			return;

		cl_base* p = get_pointer_by_path(queue_req[0].doc_path);

		if (p != nullptr)
		{
			cl_document* d = (cl_document*)p;

			current_doc->init(
				d->get_pc_number(),
				d->get_title(),
				d->get_pages_left(),
				d->get_tact_added()
			);

			cl_pc* pc = (cl_pc*)d->get_p_head_object();

			if (pc != nullptr)
			{
				pc->remove_document_name(d->get_s_object_name());
				pc->del_sub_obj(d->get_s_object_name());
			}
		}

		queue_req.erase(queue_req.begin());
	}

	int pages_left = current_doc->get_pages_left();
	if (pages_left == 0)
		return;

	int can_print = q;

	if (can_print > pages_left)
		can_print = pages_left;

	if (can_print > tray->get_sheets())
		can_print = tray->get_sheets();

	if (can_print > cartridge->get_remaining())
		can_print = cartridge->get_remaining();

	tray->consume(can_print);
	cartridge->consume(can_print);
	current_doc->set_pages_left(pages_left - can_print);

	if (current_doc->get_pages_left() == 0)
		current_doc->clear();
}
void cl_printer::start_replacing_cartridge()
{
	power_on = false;
	queue_req.clear();
	cartridge->start_replacing();
}
void cl_printer::power_off()
{
	power_on = false;
	queue_req.clear();
}
int cl_printer::get_current_pages_left()
{
	//--------------------------------------------------
	// Получение количества оставшихся страниц у текущего документа
	// Параметры:
	//     
	// Возвращаемое значение:
	//     int, количество страниц
	//--------------------------------------------------

	// 1.1 Возвращение результата метода get_pages_left для текущего документа
	return current_doc->get_pages_left();
}
int cl_printer::get_queue_size()
{
	//--------------------------------------------------
	// Получение количества объектов структуры resuest в массиве
	// Параметры:
	//     
	// Возвращаемое значение:
	//     int, количество объектов
	//--------------------------------------------------

	// 1.1 Возвращение размера динамического массива queue_req
	return queue_req.size();
}
string cl_printer::get_system_status_line(int tact_number)
{
	//--------------------------------------------------
	// Получение статуса системы
	// Параметры:
	//     int tact_number, номр
	// Возвращаемое значение:
	//     string, строка состояния системы
	//--------------------------------------------------

	// 1.1 Объявление строковой переменной result
	string result;
	// 2.1 Переменная result = "Printer tact" + значение параметра tact_number
	result = "Printer tact: " + to_string(tact_number);
	// 3.1 Переменная result = result + "; print document" + количество листов, оставшихся для печати
	result += "; print document: " + to_string(get_current_pages_left());
	// 4.1 Переменная result = result  + "queue documents" + длина массива queue_req
	result += "; queue documents: " + to_string(get_queue_size());
	// 5.1 Объявление динамического массива с номерами ПК pc_numbers
	vector<int> pc_numbers;
	// 6.1 Объявление динамического массива с количеством документов у каждого ПК pc_counts
	vector<int> pc_counts;
	// 7.1 Инициализация переменной счетчика i = 0
	// 8.1 i < размера массива queue_req
	for (int i = 0; i < queue_req.size(); i++)
	{
		// 8.1 Инициализация целочисленной переменной pc номером i-го ПК из массива очереди документов для принтера queue_req
		int pc = queue_req[i].pc_number;
		// 9.1 Инициализация целочисленной переменной pos = -1
		int pos = -1;

		// 10.1 Инициализация переменной счетчика j = 0
		// 11.1 j < размера массива pc_numbers
		for (int j = 0; j < pc_numbers.size(); j++)
		{
			// 12.1 START cycle
			// 12.1 j-й элемент массива pc_numbers = значению переменной pc
			if (pc_numbers[j] == pc)
			{
				// 12.1 Присвоение переменной pos = j
				pos = j;
				break;
			}
		}
		// 14.1 Переменная pos = -1
		if (pos == -1)
		{
			// 14.1 Добавление значения pc в динамический массив pc_numbers
			pc_numbers.push_back(pc);
			// 15.1 Добавление значения 1 в динамический массив pc_counts
			pc_counts.push_back(1);
		}
		// else
		else
		{
			// 14.2 Увеличение элемента с индексом pos массива pc_counts на 1
			pc_counts[pos]++;
		}
	}
	// 17.1 Размера массива pc_numbers > 0
	if (pc_numbers.size() > 0)
	{
		// 17.1 result = result + "PC: "
		result += "  PC:";
		// 18.1 Инициализация переменной счётчика i = 0
		// 19.1 START cycle
		// 19.1 i < размера массива pc_numbers
		for (int i = 0; i < pc_numbers.size(); i++)
		{
			// 19.1 result = result + "(" + i-й элемент массива pc_numbers + i-й элемента массива pc_counts + ")"
			result += " (" + to_string(pc_numbers[i]) + ":" + to_string(pc_counts[i]) + ")";
		}

	}
	// 21.1 Возвращение переменной result
	return result;
}
void cl_printer::clear_queue()
{
	//--------------------------------------------------
	// Удаление очереди запросов
	// Параметры:
	//     
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	// 1.1 Удаление очереди запросов в динамическом массиве queue_req
	queue_req.clear();
}
