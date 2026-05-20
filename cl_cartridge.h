#ifndef CL_CARTRIDGE_H
#define CL_CARTRIDGE_H
#include "cl_base.h"
class cl_cartridge : public cl_base	// Класс картриджа
{
public:
	cl_cartridge(cl_base* p_head_object, string s_object_name);
	void init(int k);	// Инициализация количества листов для картриджа
	void start_replacing();	// Начало ожидания загрузки чернил в картридж
	void do_tact_replacing();	// Ожидание загрузки чернил в картридж
	bool is_replacing();	// Проверка загрузки чернил в картридж
	void consume(int x);
	int get_remaining();// Уменьшения количества листов, которые еще можно напечатать
private:
	int capacity = 0; 	// Количество листов, которое можно напечатать с полного картриджа
	int remaining = 0; 	// Количество листов, которые еще можно напечатать
	int replace_ticks_left = 0; 	// Количество тактов, оставшихся до окончания замены
};
#endif    // CL_CARTRIDGE_H