#include "Ticket.h"

Ticket::Ticket(const int quantity, const Passenger* passenger)
{
	this->quantity = quantity;
	if (quantity == 0 || passenger == nullptr)
		return;
	this->passenger = new Passenger[quantity];
	for (int i = 0; i < quantity; i++)
		this->passenger[i] = passenger[i];
}

Ticket::Ticket(const Ticket& ticket)
{
	*this = ticket;
}

Ticket::~Ticket()
{
	if (passenger == nullptr)
		return;
	if (quantity > 0 && passenger != nullptr)
		delete[] passenger;
	quantity = 0;
	price = 0;
}

Ticket& Ticket::operator=(const Ticket& ticket)
{
	if (*this == ticket)
		return *this;
	quantity = ticket.quantity;
	if (quantity > 0)
	{
		passenger = new Passenger[quantity];
		for (int i = 0; i < quantity; i++)
			passenger[i] = ticket.passenger[i];
	}
	price = ticket.price;
	return *this;
}

void Ticket::newPassengerInfo()
{
	quantity = 0;
	while (quantity <= 0)
	{
		std::cout << "Введите количество пассажиров: ";
		std::cin >> quantity;
	}

	passenger = new Passenger[quantity];
	for (int i = 0; i < this->quantity; i++)
		std::cin >> this->passenger[i];
	this->price = 0;
}

void Ticket::newSeats(const int train, const std::string depTime, const std::string arrTime, const int carriage,
	int** seats, const std::string departure, const std::string arrival, const std::string date)
{
	int k = 0;
	for (int i = 0; seats[0][i] != 0; i++)
		passenger[k++].newSeatInfo(train, depTime, arrTime, carriage, 0, seats[0][i], departure, arrival, date);
	for (int i = 0; seats[1][i] != 0; i++)
		passenger[k++].newSeatInfo(train, depTime, arrTime, carriage, 1, seats[1][i], departure, arrival, date);
}

bool Ticket::saveTicket(const std::string filename)
{
	if (quantity == 0)
		return false;
	std::ofstream fout(filename);
	fout << quantity << '\n';
	for (int i = 0; i < quantity; i++)
		fout << passenger[i];
	fout.close();
	return true;
}

float Ticket::cost(const float price)
{
	if (price != 0)
		this->price = price;
	return this->price;
}

bool Ticket::Print()
{
	if (quantity == 0)
		return false;
	std::cout << "Количество билетов: " << quantity << '\n';
	for (int i = 0; i < quantity; i++)
		std::cout << passenger[i];
	std::cout << "Общая цена билетов: " << price << "р.\n";
	return true;
}

bool Ticket::operator==(const Ticket& ticket)
{
	if (quantity != ticket.quantity || price != ticket.price)
		return false;
	for (int i = 0; i < quantity; i++)
		if (!(passenger[i] == ticket.passenger[i]))
			return false;
	return true;
}
