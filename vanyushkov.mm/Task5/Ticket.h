#pragma once
#include "Passenger.h"
class Ticket
{
	Passenger* passenger; // Пассажиры
	int quantity;         // Количество
	float price;          // Общая сумма билетов

public:
	Ticket(const int quantity = 0, const Passenger* passenger = nullptr);
	Ticket(const Ticket& ticket);
	~Ticket();

	Ticket& operator= (const Ticket& ticket);
	void newPassengerInfo();
	void newSeats(const int train, const std::string depTime, const std::string arrTime, const int carriage,
		int** seats, const std::string departure, const std::string arrival, const std::string date); // Резервация мест
	bool saveTicket(const std::string filename = "ticket.txt");
	int people() { return quantity; }
	float cost(const float price = 0.0f);
	bool Print(); // Вывод информации на консоль
	bool operator== (const Ticket& ticket);
};

