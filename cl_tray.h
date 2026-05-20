#ifndef CL_TRAY_H
#define CL_TRAY_H
#include "cl_base.h"
class cl_tray : public cl_base	// Класс лотка бумаги
{
public:
	cl_tray(cl_base* p_head_object, string s_object_name);
	void init(int m);	// Инициализация лотка
	void start_loading();	// Начало загрузки бумаги в лоток
	void do_tact_loading();	// Выполнение одного такта загрузки
	bool is_loading();	// Провека загрузки бумаги в лоток
	void consume(int x);	// Уменьшение количества листов в лотке
	int get_sheets();	// Получение текущего количества листов в лотке
private:
	int capacity; 	// Максимальная вместимость лотка
	int sheets; 	// Текущее количество листов в лотке
	int load_ticks_left; 	// Количество тактов, оставшихся до завершения загрузки
};
#endif    // CL_TRAY_H