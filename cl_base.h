#ifndef __CL_BASE__H
#define __CL_BASE__H

#include <iostream>
#include <vector>
#include <string>

// параметризированное макроопределение препроцессора
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

using namespace std;

class cl_base;
// Определение указателя на метод сигнала
typedef void (cl_base ::* TYPE_SIGNAL) (string&);
typedef void (cl_base ::* TYPE_HANDLER) (string);

class cl_base
{
	struct o_sh               // Структура задания одной связи
	{
		TYPE_SIGNAL  p_signal;    // Указатель на метод сигнала
		cl_base* p_cl_base;   // Указатель на целевой объект
		TYPE_HANDLER p_handler;   // Указатель на метод обработчика
	};
private:

	string s_object_name;                     // Поле с имененм объекта
	cl_base* p_head_object;                   // Поле с указателем на головной объекта класса cl_base
	vector < cl_base* > subordinate_objects; // Поле динамического массива с указателями на подчиненные объекты класса cl_base
	int i_state = 0;                          // Поле состояния готовности объекта
	vector < o_sh* > connects;               // Поле динамического массива с указателями на объект структуры o_sh для хранения связи

public:

	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");//Констуктор базового класса
	bool change_s_object_name(string new_name);                             // Заголовок метода смены имени объекта
	string get_s_object_name();                                             // Заголовок метода получения имени объекта
	cl_base* get_p_head_object();                                           // Заголовок метода получения указателя на головной объект
	int get_count_subordinate_objects();                                    // Заголовок метода возвращение количества подчиненных объектов
	cl_base* get_adress_subordinate_object_name(string name);               // Заголовок метода получения указателя на подчиненный объкт по его имени
	cl_base* get_adress_subordinate_object_index(int index);                // Заголовок метода получения указателя на подчиненный объкт по его индексу
	~cl_base();                                                             // Деструктор базового класса
	cl_base* search_object_branch_name(string name);                         // Заголовок метода получения указателя на объект в ветке дерева по имени объекта
	cl_base* search_object_all_three_name(string name);                      // Заголовок метода получения указателя на объект во всём дереве по имени объекта
	void print_tree(int level = 0);                                         // Заголовок метода печати дерева
	void print_tree_status(int level = 0);                                  // Заголовок метода печати дерева со статусом головности объекта
	void set_ready(int state);                                              // Заголовок метода установки готовности объекта
	bool redefine_head_obj(cl_base* new_head_p);                            // Заголовок метода переопределения головного объекта
	void del_sub_obj(string name);                                          // Заголовок метода удаления подчиненного объекта по его имени
	cl_base* get_pointer_by_path(string path);                              // Заголовок метода получения указателя на объект по его координате
	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_hendler);   // Заголовок метода установки связи
	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_hendler);// Заголовок метода удаления связи
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);// Заголовок метода выдачи сигнала
	string get_absolute_path();                                // Заголовок метода получения абсолютного пути до объекта
	virtual int get_number_class();                            // Заговок виртуального метода получения номера класса
	void set_state_branch(int new_state);                      // Заголовок метода установки готовности объектов по ветви дерева
};


#endif
