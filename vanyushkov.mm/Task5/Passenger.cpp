#include "Passenger.h"

Passenger::Passenger(const std::string surname, const std::string name, const std::string patronymic)
{
	this->surname = surname;
	this->name = name;
	this->patronymic = patronymic;
}

Passenger::Passenger(const Passenger& passenger)
{
	*this = passenger;
}

Passenger& Passenger::operator=(const Passenger& passenger)
{
	surname = passenger.surname;
	name = passenger.name;
	patronymic = passenger.patronymic;
	date = passenger.date;
	depTime = passenger.depTime;
	arrTime = passenger.arrTime;
	train = passenger.train;
	typeCar = passenger.typeCar;
	carriage = passenger.carriage;
	seat = passenger.seat;
	departure = passenger.departure;
	arrival = passenger.arrival;
	return *this;
}

bool Passenger::operator==(const Passenger& passenger)
{
	if (surname == passenger.surname && name == passenger.name && patronymic == passenger.patronymic
		&& depTime == passenger.depTime && arrTime == passenger.arrTime && date == passenger.date
		&& train == passenger.train && typeCar == passenger.typeCar && carriage == passenger.carriage
		&& seat == passenger.seat && departure == passenger.departure && arrival == passenger.arrival)
		return true;
	return false;
}

void Passenger::newSeatInfo(const int train, const std::string depTime, const std::string arrTime, const int carriage, 
	const int typeCar, const int seat, const std::string departure, const std::string arrival, const std::string date)
{
	this->train = train;
	this->depTime = depTime;
	this->arrTime = arrTime;
	this->carriage = carriage;
	this->typeCar = typeCar;
	this->seat = seat;
	this->departure = departure;
	this->arrival = arrival;
	this->date = date;
}

std::istream& operator>>(std::istream& stream, Passenger& passenger)
{
	std::cout << "Фамилия: ";
	stream >> passenger.surname;
	std::cout << "Имя: ";
	stream >> passenger.name;
	std::cout << "Отчество: ";
	stream >> passenger.patronymic;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Passenger& passenger)
{
	stream << "ФИО: " << passenger.surname << ' ' << passenger.name << ' ' << passenger.patronymic << '\n';
	stream << "Рейс: " << passenger.departure << " - " << passenger.arrival << '\n';
	stream << "Дата отправления: " << passenger.date << '\n';
	stream << "Время отправления: " << passenger.depTime << '\n';
	stream << "Время прибытия: " << passenger.arrTime << '\n';
	stream << "Поезд номер: " << passenger.train << '\n';
	stream << "Вагон: " << passenger.carriage << '\n';
	stream << "Место: " << passenger.seat;
	if (passenger.typeCar == 0)
		stream << " нижнее\n";
	else
		stream << "Верхнее\n";
	return stream;
}
