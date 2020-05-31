#pragma once
#include "GorkyRailway.h"
#include "Ticket.h"
#include <ctime>

class RailTicketOffice
{
	GorkyRailway railway[2][30]; // 0 - Москва-НН, 1 - НН-Москва
	int number[2][5];            // Номер поезда
	std::string time[2][2][5];   // Время отправления-прибытия

	Ticket ticket;
	
public:
	RailTicketOffice(const std::string filename = "TimeTable.txt");
	Ticket newTicket(); // Новый билет
	void clearTicket(); // Отмена

private:
	void __readTable(const std::string filename = "TimeTable.txt");  // Расписание поездов
	void __printTable(const int route);
	bool payment() { return true; }   // Оплата (требует дополнительной банковской системы, сейчас будем учитывать, что оплата проходит всегда)
};

