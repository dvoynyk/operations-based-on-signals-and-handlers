#include "cl_base.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

cl_base::cl_base(cl_base* p_head_object, string s_object_name)        // Конструктор базового класса
{
	this->p_head_object = p_head_object;   							   // Текущий объект знает своего головного объекта
	this->s_object_name = s_object_name;                               // Имя текущего объекта
	if (p_head_object)                                                 // Если объект не корневой 
	{
		p_head_object->subordinate_objects.push_back(this);            // Добавляем текущий объект в подчиненные  
	}
}
bool cl_base::change_s_object_name(string new_name)                    // Изменить имя объекта 
{
	if (p_head_object == nullptr)                                      // Если объект корневой
	{
		s_object_name = new_name;                                      // Сменить имя объекта
		return true;                                                   // Возвращение истины
	}
	for (int i = 0; i < p_head_object->subordinate_objects.size(); i++)// Цикл по подчиненным объектам головного объекта
	{
		// Условие если найден объект с тем же именем, то менять нельзя 
		if (p_head_object->subordinate_objects[i] != this && p_head_object->subordinate_objects[i]->s_object_name == new_name)
		{
			return false;                                        // Возвращение ложь, дубляж имени среди подчиненных
		}
	}
	s_object_name = new_name;                                    // Если дубляжа нет - можно менять имя
	return true;                                                 // Возвращение истина 
}
string cl_base::get_s_object_name()                              // Метод получения имени объекта
{
	return s_object_name;                                        // Возвращение имени объекта
}
cl_base* cl_base::get_p_head_object()                            // Метод получения указателя на головной объект
{
	return p_head_object;                                        // Возвращение указателя на головной объект
}
int cl_base::get_count_subordinate_objects()                     // Метод получения количества подчиненных объектов
{
	return subordinate_objects.size();                           // Возвращение размера контейнера с подчиненными объектами
};
cl_base* cl_base::get_adress_subordinate_object_name(string name)// Метод получения адреса подчиненного объекта по его имени
{
	for (int i = 0; i < subordinate_objects.size(); i++)             // Цикл по подчинным объектам текущего объекта
	{
		if (subordinate_objects[i]->s_object_name == name)       // Нашелся подчинный объект с таким именем
		{
			return subordinate_objects[i];                       // Возвращение адреса подчиненного объекта
		}
	}
	return nullptr;                                              // Вовзращение нулевого указателя
};
cl_base* cl_base::get_adress_subordinate_object_index(int index) // Метод получения адреса подчиненного объекта по индексу
{
	if (index < 1 || index > subordinate_objects.size())         // Если индекс выходит на пределы размера контейнера с подчиненными объектами
	{
		return nullptr;                                          // Возвращение нулевого указателя
	}
	return subordinate_objects[index - 1];                        // Возвращение адреса подчиненного объекта по индексу
};
cl_base::~cl_base()                                              // Деструктор базового класса
{
	for (int i = 0; i < subordinate_objects.size(); i++)           // Цикл по подчиненным объектам текущего объекта
	{
		delete subordinate_objects[i];                           // Удаление объекта в памяти по адресу
	}
};
cl_base* cl_base::search_object_branch_name(string name)         // Метод поиска объекта по ветви от текущего объекта по имени
{
	vector<cl_base*> objects;                                    // Контейнер для обхода 
	objects.push_back(this);                                     // Добавление текущего объекта в контейнер
	cl_base* result = nullptr;                                    // Указатель на объект класса result c нулевым указателем
	int count = 0;                                               // Переменная для подсчета
	while (!objects.empty())                                      // Пока контейнер для обхода не пуст
	{
		cl_base* current = objects.back();                        // Берем последний указатель на объект из контейнера
		objects.pop_back();                                      // Удаление этого последнего указателя на объекта
		if (current->s_object_name == name)                       // Если имя совпало
		{
			count++;                                            // Увеличение счётчика
			result = current;                                    // Запоминание адреса на этот объект
		}
		for (int i = 0; i < current->subordinate_objects.size(); i++)// Прохождение по подчиненным объектам последнего взятого указателя на объект
		{
			objects.push_back(current->subordinate_objects[i]);  // Добавление подчиненных в контейнер для обхода
		}
	}
	if (count == 1)                                              // Если нашелся только один такой объект
	{
		return result;                                           // Возвращение адреса на этот единственный объект
	}
	return nullptr;                                              // Возвращение нулевого указателя 
};
cl_base* cl_base::search_object_all_three_name(string name)      // Метод поиска объекта по имени по всему дереву
{
	cl_base* root = this;                                         // Начало с текущего объекта
	while (root->p_head_object != nullptr)                         // Пока головной объект текущего объекта не порневой
	{
		root = root->p_head_object;                              // Переход к головному объекту текущего объекта
	}
	return root->search_object_branch_name(name);                // Поиск объекта во всем дереве начиная от корневого объекта
};
void cl_base::print_tree(int level)                              // Метод печати дерева от текущего объекта
{
	for (int i = 0; i < level; i++)                                // Цикл для понимания сколько нужно отступов
	{
		cout << "    ";                                          // Печать отступов
	}
	cout << s_object_name << endl;                               // Вывод имени текущего объекта
	for (int i = 0; i < subordinate_objects.size(); i++)              // Цикл по подчинным объектам
	{
		subordinate_objects[i]->print_tree(level + 1);             // Рекурсивный вызов метода для каждого подчиненного объекта
	}
};
void cl_base::print_tree_status(int level)                       // Метод печати дерева со статусом готовности
{
	for (int i = 0; i < level; i++)                                // Цикл для понимания сколько нужно отступов
	{
		cout << "    ";                                          // Печать отступов
	}
	cout << s_object_name;                                       // Вывод имени текущего объекта
	if (i_state != 0)                                               // Если готовность отлична от 0
	{
		cout << " is ready";                                     // Вывод строки о готовности
	}
	else                                                         // Иначе
	{
		cout << " is not ready";                                 // Вывод строки о не готовности
	}
	cout << endl;                                                // Переход на следующую строку
	for (int i = 0; i < subordinate_objects.size(); i++)              // Цикл по подчиненным объектам текущего объекта
	{
		subordinate_objects[i]->print_tree_status(level + 1);      // Рекурсивный вызов метода для каждого подчиненного объекта
	}
}
void cl_base::set_ready(int state)                               // Установка состояния объекта
{
	if (p_head_object == nullptr || p_head_object->i_state != 0)  // Если корень или головной объект готовы к включению
	{
		i_state = state;                                         // Установка готовности для текущего объекта
	}
	if (state == 0)                                               // Если выключение объекта
	{
		i_state = state;                                         // Установка статуса о не готовности для текущего объекта 
		for (int i = 0; i < subordinate_objects.size(); i++)       // Цикл по подчиненным объектам для текущего объекта
		{
			subordinate_objects[i]->set_ready(state);            // Рекурсивное выключение подчиненных объектов
		}
	}
};
bool cl_base::redefine_head_obj(cl_base* new_head_p)             // Метод переопредения головного объекта 
{
	if (this->get_p_head_object() == new_head_p)                  // Если текущий объект и так подчинен этому объекту
	{
		return true;                                             // Возвращение истины
	}
	if (this->get_p_head_object() == nullptr || new_head_p == nullptr)// Текущий объект корень или новый указатель не задан
	{
		return false;                                            // Возвращение ложь
	}
	// проверка дубляжа имени среди подчиненных у нового объекта
	if (new_head_p->get_adress_subordinate_object_name(this->get_s_object_name()) != nullptr)
	{
		return false;                                            // Возвращение ложь
	}
	stack<cl_base*> st;                                          // Для обхода дерева используется стек
	st.push(this);                                               // Добавление в стек текущего объекта
	while (!st.empty())                                           // Пока стек не пуст
	{
		cl_base* current_node_ptr = st.top();                    // Берется последний верхний элемент стека
		st.pop();                                                // Удаление последнего элемента из стека
		if (current_node_ptr == new_head_p)                       // Если объект по новому указателю находится в подчиненных текущего объекта
		{
			return false;                                        // Возвращение ложь
		}
		for (int i = 0; i < current_node_ptr->subordinate_objects.size(); i++)// Цикл по подчиненным объектам для последнего объекта из стека
		{
			st.push(current_node_ptr->subordinate_objects[i]);               // Добавление в стек подчиненных объектов для последнего объекта из стека
		}
	}
	vector <cl_base*>& v = this->get_p_head_object()->subordinate_objects;  // Ссылка на контейнер с подчиненными объектами для головного объекта текущего объекта
	for (int i = 0; i < v.size(); i++)                                        // Цикл по объектам из контейнера
	{
		if (v[i]->get_s_object_name() == this->get_s_object_name())           // Нашелся объект по имени текущего объекта
		{
			v.erase(v.begin() + i);                                          // Удаление текущего объекта из контейнера
			new_head_p->subordinate_objects.push_back(this);                 // Добавление текущего объекта в подчиненные нового головного объекта
			this->p_head_object = new_head_p;                                // Обновление нового головного объекта
			return true;                                                     // Переподчинение выполнено
		}
	}
	return false;                                                            // Возвращение ложь
};

void cl_base::del_sub_obj(string name)                            // Метод удаления подчиненного объекта по имени
{
	vector <cl_base*>& sub = this->subordinate_objects;          // Ссылка на контейнер с подчиненными объектами для текущего объекта
	for (int i = 0; i < sub.size(); i++)                            // Цикл по контейнеру с подчиненными объектами
	{
		if (sub[i]->get_s_object_name() == name)                   // Найден нужный подчиненный объект
		{
			delete sub[i];                                        // Удаление объекта по адресу из памяти
			sub.erase(sub.begin() + i);                           // Удаление элемента из контейнера
			return;                                               // Выход из метода
		}
	}
};

cl_base* cl_base::get_pointer_by_path(string path)                // Метод получения указателя на объект по координате
{
	if (path.empty())                                              // Путь пустой
	{
		return nullptr;                                           // Возвращение нулевого указателя
	}
	if (path == ".")                                              // В координате только "."
	{
		return this;                                              // Возвращение указателя на текущий объект
	}
	if (path[0] == '.')                                            // 1-й элемент координаты "."
	{
		return this->search_object_branch_name(path.substr(1));   // Поиск по имени по ветви от текущего объекта
	}
	if (path.substr(0, 2) == "//")                                  // В координате первые 2 элемента "//"
	{
		return this->search_object_all_three_name(path.substr(2));// Поиск по всему дереву после "//"
	}
	if (path[0] != '/')                                            // Если координата не начинается с "/"
	{
		size_t index_slash = path.find('/');                      // Поиск "/" в координате 
		cl_base* sub_ptr = this->get_adress_subordinate_object_name(path.substr(0, index_slash));// Поиск адреса подчиненного объекта до "/"
		if (sub_ptr == nullptr || index_slash == string::npos)           // Если адрес подчиненного объекта не найден или "/" нет в пути
		{
			return sub_ptr;												// Возвращение найденного подчиненного или нулевого указателя
		}
		return sub_ptr->get_pointer_by_path(path.substr(index_slash + 1));// Рекурсивный поиск оставшегося пути у найденного подчиненного
	}
	cl_base* root_ptr = this;                                           // Начало обхода дерева с текущего объекта
	while (root_ptr->get_p_head_object() != nullptr)                     // Пока головной объект не корневой
	{
		root_ptr = root_ptr->get_p_head_object();                       // Переход к головному объекту
	}
	if (path == "/")                                                    // Вся координата равна "/"
	{
		return root_ptr;                                                // Возвращение указателя на корень
	}
	return root_ptr->get_pointer_by_path(path.substr(1));               // Поиск по координате относительно корневого объекта
};

void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler)// Метод для установки связи
{
	o_sh* p_value;                                                                         // Объявление на объект структуры
	for (unsigned int i = 0; i < connects.size(); i++)                                       // Цикл по связям
	{
		// Если связь сигнал + объект + обработчик уже существует
		if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object && connects[i]->p_handler == p_ob_handler)
		{
			return;                    // Выход из метода
		}
	}
	p_value = new o_sh();              // Инициализация динамической структуры связи

	p_value->p_signal = p_signal;      // Присвоение указателя на метод сигнала
	p_value->p_cl_base = p_object;     // Присвоение указателя на целевой объект
	p_value->p_handler = p_ob_handler; // Присвоение указателя на метод обработчика

	connects.push_back(p_value);       // Добавление связи в контейнер
}

void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_hendler)// Метод удаления связи
{
	for (int i = 0; i < connects.size(); i++)                                                   // Цикл по связям
	{
		// Если такая связь сигнал + объект + обработчик уже существует
		if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base == p_object && connects[i]->p_handler == p_ob_hendler)
		{
			delete connects[i];                                                               // Освобождение памяти из под структуры
			connects.erase(connects.begin() + i);                                               // Удаление элемента из контейнера
		}
	}
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command)// Метод выдачи сигнала и отработки связанных обработчиков
{
	TYPE_HANDLER p_handler;                                        // объявление указателя на метод обработчика
	cl_base* p_object;                                             // Объявление указателя на объект класса

	if (i_state == 0)                                               // Если текущий объект не готов
	{
		return;                                                    // Нет выдачи сигнала
	}

	(this->*p_signal)(s_command);                                  // вызов метода сигнала 

	for (unsigned int i = 0; i < connects.size(); i++)               // цикл по всем обработчикам
	{
		if (connects[i]->p_signal == p_signal)                      // определение допустимого обработчика
		{
			p_handler = connects[i]->p_handler;                    // Присвоение указателя на обработчик
			p_object = connects[i]->p_cl_base;                     // Присвоение указателя на целевой объект

			if (p_object->i_state == 0)                             // Если целевой объект не готов
			{
				continue;                                          // Нет вызова обработчика
			}

			(p_object->*p_handler)(s_command);                     // Иначе вызов метод обработчика для целевого объекта
		}
	}
}

string cl_base::get_absolute_path()          // Метод получения абсолютного пути 
{
	if (p_head_object == nullptr)             // Если объект корневой 
	{
		return "/";                          // Возвращение "/"
	}

	string result;                           // Итоговая строка для вывода результата
	stack<string> st;                        // Стек для обхода координаты
	cl_base* p = this;                        // Начало обхода с текущего объекта

	while (p->p_head_object != nullptr)       // Пока обход не дошел до корневого объекта
	{
		st.push(p->s_object_name);           // Добавление в стек имени текущего объекта
		p = p->p_head_object;                // Переход к головному объекту
	}

	while (!st.empty())                       // Пока стек не пустой
	{
		result += "/" + st.top();            // Добавление головных объектов в координату
		st.pop();                            // Удаление добавленных объектов из стека
	}
	return result;                           // Возвращение абсолютного пути до объекта
}

int cl_base::get_number_class()              // Метод получения номера класса
{
	return 0;                                // Возвращение 0
}

void cl_base::set_state_branch(int new_state)// Метод установки состояния готовности объекто для ветви
{
	if (get_p_head_object() != nullptr && get_p_head_object()->i_state == 0)//Если головной объект для текущего объекта есть и он выключен
	{
		return;                                                            //Выход из метода
	}
	set_ready(new_state);                                                  // Иначе установка состояни готовности текущего объекта
	for (int i = 0; i < subordinate_objects.size(); i++)                     // Цикл по подчиненным объектам для текущего объекта
	{
		subordinate_objects[i]->set_state_branch(new_state);               // Рекурсивный вызов этого метода для подчиненных объектов
	}
}