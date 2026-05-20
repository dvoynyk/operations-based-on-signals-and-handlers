#include "cl_application.h"
#include "cl_base.h"
#include "cl_input.h"
#include "cl_output.h"
#include "cl_printer.h"
#include "cl_tray.h"
#include "cl_cartridge.h"
#include "cl_pc.h"
#include "cl_document.h"
#include <iostream>
#include <sstream>
using namespace std;


static string trim_spaces(const string& s)
{
	//--------------------------------------------------
	// Удаление пробелов по краям строки
	// Параметры:
	//     string s
	// Возвращаемое значение:
	//     string, строка без пробелов
	//--------------------------------------------------

	// 1.1 Инициализация целочисленной переменной L = 0
	// 2.1 START cycle
	// 2.1 L < длины s и (s с индексом L == " "  или s с индексом L == "\t" или s с индексом L == "\r")
	int L = 0;
	while (L < (int)s.size() && (s[L] == ' ' || s[L] == '\t' || s[L] == '\r'))
	{
		L++;// 2.1 L++
	}
	// 2.2 Инициализация целочисленной переменной R = длина s - 1
	// 4.1 START cycle
	// 4.1 R >= L и (s с идексом R == " " или s с индексом R == "\t" или s с индексом R == "\r")
	int R = (int)s.size() - 1;
	while (R >= L && (s[R] == ' ' || s[R] == '\t' || s[R] == '\r'))
	{
		R--;// 4.1 R--
	}
	// 4.2 Возвращение строки s с измененными краями
	return s.substr(L, R - L + 1);
};

cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object, "System") {} // Конструктор cl_application с вызовом конструктора базового класса для прикрепления к дереву 

void cl_application::build_tree_objects()
{
	//--------------------------------------------------
	// Построение дерева иерархии объектов и подготовка системы к работе
	// Параметры:
	//     
	// Возвращаемое значение:
	//     Не возвращает
	//--------------------------------------------------

	p_input = new cl_input(this, "Input");                  // 1.1 Присвоение указателю p_input адреса динамически созданного объекта класса cl_input с аргументами адрес текущего объекта и именем "Input"
	p_output = new cl_output(this, "Output");               // 2.1 Присвоение указателю p_output адреса динамически созданного объекта класса cl_output с аргументами адрес текущего объекта и именем "Output"
	p_printer = new cl_printer(this, "Printer");            // 3.1 Присвоение указателю p_printer адреса динамически созданного объекта класса cl_printer с аргументами адрес текущего объекта и именем "Printer"

	p_tray = new cl_tray(p_printer, "Tray");                 // 4.1 Присвоение указателю p_tray адреса динамически созданного объекта класса cl_tray с аргументами объект принтера по адресу p_printer и именем "Tray"
	p_cartridge = new cl_cartridge(p_printer, "Cartridge");  // 5.1 Присвоение указателю p_cartridge адреса динамически созданного объекта класса cl_cartridge с аргументами объект принтера по адресу p_printer и именем "Cartridge"
	p_current_doc = new cl_document(p_printer, "Printer");   // 6.1 Присвоение указателю p_current_doc адреса динамически созданного объекта класса cl_document с аргументами объект принтера по адресу p_printer и именем "Current_document"

	// 7.1 Установка связи с помощью метода set_connect между текущим объектом и объектом вывода Output
	set_connect(
		SIGNAL_D(cl_application::signal_msg),
		p_output,
		HANDLER_D(cl_output::handler_print)
	);

	set_state_branch(1);									// 8.1 Установка готовности объектов методом set_state_branch

	string line;											// 9.1 Объявление строковой переменной line

	p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);// 10.1 Вызов метода выдачи сигнала emit_signal для объекта по адресу p_input с аргументами указатель на метод сигнала signal_read_line и переменной line
	istringstream iss1(line);										// 11.1 Ввод количества ПК в поле n
	iss1 >> n;

	p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);// 12.1 Вызов метода выдачи сигнала emit_signal для объекта по адресу p_input с аргументами указатель на метод сигнала signal_read_line и переменной line
	istringstream iss2(line);									    // 13.1 Ввод вместимости лотка для бумаги, ёмкости картриджа и листов за 1 такт в поля m, k, q соответственно
	iss2 >> m >> k >> q;

	p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line);// 14.1 Ввод строки "End of settings" в переменную line													        
	p_tray->init(m);                                                // 15.1 Вызов метода init с аргументом m для объекта по адресу p_tray для установки вместимости лотка для бумаги 
	p_cartridge->init(k);											// 16.1 Вызов метода init с аргументом k для объекта по адресу p_cartridge для установки ёмкости картриджа
	p_current_doc->clear();										    // 17.1 Вызов метода clear для объекта по адресу p_current_doc 
	p_printer->init(q, p_tray, p_cartridge, p_current_doc);		    // 18.1 Вызов метода init c аргументами q, p_tray, p_cartridge, p_current_doc для объекта по адресу p_printer 

	// 19.1 Инициализация переменной счетчика i = 1
	// 20.1 START cycle
	// 20.1 i <= n
	for (int i = 1; i <= n; i++)
	{
		// 20.1 Инициализация строковой переменной name = PC + i
		string name = "PC" + to_string(i);
		// 21.1 Инициализация указателя pc на объект класса cl_pc адресом динамически созданного объекта с аргументами адрес текущего объекта, name, i
		cl_pc* pc = new cl_pc(this, name, i);
		// 22.1 Добавление адреса pc в динамический массив pcs 
		pcs.push_back(pc);
		// 23.1 Вызов метода установки связи set_connect между ПК и принтером 
		pc->set_connect(
			SIGNAL_D(cl_pc::signal_to_printer),
			p_printer,
			HANDLER_D(cl_printer::handler_add_request)
		);
		// 24.1 i++
	}
	// 25.1 Вызов метода set_pcs c аргументом pcs для объекта пульта управления принтером по адресу p_printer 
	p_printer->set_pcs(pcs);
	// 26.1 Установка готовности объектов методов set_state_branch 
	set_state_branch(1);
	// 27.1 Инициализация строковой переменной msg = "Ready to work"
	string msg = "Ready to work";
	// 28.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
	emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
}
int cl_application::exec_app()
{
	//--------------------------------------------------
	// Функционирование системы и обработка команд
	// Параметры:
	//     
	// Возвращаемое значение:
	//     int, результат выполнения метода
	//--------------------------------------------------

	// 1.1 Инициализация целочисленной переменной tact = 1
	int tact = 1;
	// 2.1 Объявление строковой переменной line
	string line;
	// 3.1 Есть ввод в переменную line
	while (p_input->emit_signal(SIGNAL_D(cl_input::signal_read_line), line), cin)
	{
		// 3.1 Инициализация строковой переменной cmd значением переменной line
		string cmd = trim_spaces(line);
		// 4.1 Переменная cmd равна "SHOWTREE"
		if (cmd == "SHOWTREE")
		{
			// 4.1 Вызов метода печати дерева с готовностью print_tree_status для текущего объекта
			print_tree_status();
			return 0;
		}
		// else
		// 5.1 Переменная cmd равна "Turn of the system"
		if (cmd == "Turn off the system")
		{
			// 5.1 Инициализация строковой переменной msg = "Turn off the system"
			string msg = "Turn off the system";
			// 6.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
			emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
			return 0;
		}
		// 7.1 Переменная cmd равна "Paper tray condition"
		if (cmd == "Paper tray condition")
		{
			// 7.1 Инициализация строковой переменной msg = "Paper tray condition" + текущее количество листов в лотке
			string msg = "Paper tray condition: " + to_string(p_tray->get_sheets());
			// 8.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
			emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
		}
		// 9.1 Переменная cmd равна "Load paper tray"
		else if (cmd == "Load paper tray")
		{
			// 9.1 Вызов метода загрузки бумаги в лоток start_loading для объекта по адресу p_tray
			p_tray->start_loading();
		}
		// 10.1 Переменная cmd равна "Replace cartridge"
		else if (cmd == "Replace cartridge")
		{
			p_printer->start_replacing_cartridge();
		}
		// 12.1 Переменная cmd равна "Cartridge condition"
		else if (cmd == "Cartridge condition")
		{
			// 12.1 Инициализация строковой переменной msg = "Cartridge" + количество листов, которые еще можно напечатать
			string msg = "Cartridge: " + to_string(p_cartridge->get_remaining());
			// 13.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
			emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
		}
		// 14.1 Переменная cmd равна "System status"
		if (cmd == "System status")
		{
			// 14.1 Инициализация строковой переменной msg результатом вызова метода get_system_status_line с аргументом tact для объекта принтера по адресу p_printer
			string msg = p_printer->get_system_status_line(tact);
			// 15.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
			emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
		}
		// 16.1 Первые 2 символа переменной cmd равны "PC"
		else if (cmd.substr(0, 2) == "PC")
		{
			// 16.1 Объявление строковых переменных word1, word2
			string w1, w2;
			// 17.1 Разделение строки cmd на 2 строки и присвоение их в word1 и word2 соответственно
			istringstream iss(cmd);
			iss >> w1 >> w2;
			// 18.1 Переменная word2 равна "condition"
			if (w2 == "condition")
			{
				// 18.1 Объявление целочисленной переменной pc_num
				int pc_num;
				// 19.1 Присвоение pc_num последнего значения из переменной word2 
				iss >> pc_num;

				// 20.1 Инициализация переменной счетчика i = 0
				// 21.1 START cycle
				// 21.1 i < размера динамического массива pcs
				for (int i = 0; i < pcs.size(); i++)
				{
					// 22.1 номер компьютера i-го элемента массива pcs равен значению переменной pc_num
					if (pcs[i]->get_pc_number() == pc_num)
					{
						// 22.1 Инициализация строковой переменной msg результатом вызова метода состояния ПК get_condition_line для i-го элемента массива pcs
						string msg = pcs[i]->get_condition_line();
						// 23.1 Вызов метода вызова сигнала emit_signal для текущего объекта c аргументами указатель на метод сигнала signal_msg, msg 
						emit_signal(SIGNAL_D(cl_application::signal_msg), msg);
						break;
					}
				}
			}
			// else
			else
			{
				// 24.1 Инициализация целочисленной переменной pc_num значением из переменной word2
				int pc_num = stoi(w2);
				// 25.1 Инициализация целочисленной переменной pages значением, полученным из потока ввода
				int pages;
				iss >> pages;
				// 26.1 Инициализация строковой переменной title оставшимся значением из переменной word2
				string title;
				getline(iss, title);

				// 27.1 Инициализация переменной счетчика i = 0
				// 28.1 START cycle
				// 28.1 i < размера динамического массива pcs
				for (int i = 0; i < pcs.size(); i++)
				{
					// 29.1 номер компьютера i-го элемента массива pcs равен значению переменной pc_num и i-й ПК включен
					if (pcs[i]->get_pc_number() == pc_num && pcs[i]->is_on())
					{
						// 29.1 Инициализация строковой переменной obj_name = "doc_ " +  номер такта
						string obj_name = "doc_" + to_string(tact);
						// 30.1 Инициализация указателя d на объект класса cl_document адресом динамически созданного объекта документа класса cl_document c аргументами адрес i-го ПК, значение переменной obj_name
						cl_document* d = new cl_document(pcs[i], obj_name);
						// 31.1 Вызов метода init для объекта документа по адресу d с аргументами pc_num, title,pages,tact
						d->init(pc_num, title, pages, tact);
						// 32.1 Установка готовности для объекта документа по адресу d
						d->set_ready(1);
						// 33.1 Добавление документа в очередь i-го ПК
						pcs[i]->push_document_name(obj_name);
						// 34.1 Инициализация строковой переменной path абсолютной координатой объекта документа по адресу d
						string path = d->get_absolute_path();
						// 35.1 Вызов метода вызова сигнала emit_signal для i-го объекта ПК с аргументами указатель на метод сигнала signal_to_printer и path
						pcs[i]->emit_signal(SIGNAL_D(cl_pc::signal_to_printer), path);
						break;
					}
				}
			}
		}
		// 36.1 Вызов метода выполнения такта do_tact для объекта принтера
		p_printer->do_tact();
		// 37.1 tact++
		tact++;

	}
	return 0;
}
void cl_application::signal_msg(string& s) // Метод точки входа сигнала
{
}
