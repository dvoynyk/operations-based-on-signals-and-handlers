#ifndef CL_DOCUMENT_H
#define CL_DOCUMENT_H
#include "cl_base.h"
class cl_document : public cl_base	// Класс документа, который печатается
{
public:
	cl_document(cl_base* p_head_object, string s_object_name);
	void init(int pc, const string& t, int pages, int tact);	// Инициализация документа
	int get_pc_number();	// Получение номера компьютера
	string get_title();	// Получение названия документа
	int get_pages_left();	// Получение количества страниц документа
	int get_tact_added();	// Получение количества прошедших тактов
	void set_pages_left(int v);	// Установка количества страниц документа
	void clear();	// Удаление установленных значений полей для документа
private:
	int pc_number; 	// Номер ПК
	string title; 	// Название документа
	int pages_left; 	// Количество страниц документа
	int tact_added; // Такт добавления документа
};
#endif    // CL_DOCUMENT_H