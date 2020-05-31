#include "RailTicketOffice.h"

void RailTicketOffice::clearTicket()
{
	ticket.~Ticket();
}

void RailTicketOffice::__readTable(const std::string filename)
{
	std::ifstream fin(filename);
	std::string bin;
	for (int j = 0; j < 2; j++)
	{
		fin >> bin;
		for (int i = 0; i < 5; i++)
			fin >> number[j][i] >> time[j][0][i] >> time[j][1][i];
	}
	fin.close();
}

void __info(const int x)
{
	switch (x)
	{
	case 0: case 1: case 2:
		std::cout << "��������\n";
		break;
	case 3:
		std::cout << "���������\n";
		break;
	case 4:
		std::cout << "������\n";
		break;
	}
}

RailTicketOffice::RailTicketOffice(const std::string filename)
{
	for (int i = 0; i < 30; i++)
	{
		railway[0][i] = GorkyRailway();
		railway[1][i] = GorkyRailway();
	}
	__readTable(filename);
}

std::string getDate(int days)
{
	char buffer[6];
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	rawtime += (__int64)days * 3600 * 24;
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 6, "%d.%m", &timeinfo);
	std::string date = buffer;

	return date;
}

int** __newArr(const int n)
{
	int** arr;

	arr = new int* [2];
	for (int i = 0; i < 2; i++)
	{
		arr[i] = new int[n + 1];
		for (int j = 0; j < n + 1; j++)
			arr[i][j] = 0;
	}

	return arr;
}

void __deleteArr(int** arr, const int n)
{
	for (int i = 0; i < n + 1; i++)
		delete[] arr[i];
	delete arr;
}

Ticket RailTicketOffice::newTicket()
{
	ticket.newPassengerInfo();
	int day = -1;
	while (day < 0 || day > 29)
	{
		std::cout << "����� ������� ���� �� ���������� �����(0 - �������, �������� - 29): "; // ����� ��������, ������� ��������� �������
		std::cin >> day;
	}
	std::string date = getDate(day);

	std::cout << "�������� �����������:\n1) ������ - ������ ��������\n2) ������ �������� - ������\n";
	int roate(0);
	while (roate < 1 || roate > 2)
	{
		std::cout << "����: ";
		std::cin >> roate;
	}
	std::cout << '\n';
	roate--;
	__printTable(roate);

	int train, tmp(-1);
	while (tmp == -1)
	{
		std::cout << "�������� ����� ������: ";
		std::cin >> train;
		for (int i = 0; i < 5; i++)
			if (number[roate][i] == train)
			{
				tmp = i;
				break;
			}
	}
	train = tmp;
	int carriage = railway[roate][day].carReservate(train, ticket.people());
	if (carriage == -1)
	{
		std::cout << "��� ���� �� ���� �����\n";
		return Ticket();
	}
	int** seats = __newArr(ticket.people());
	railway[roate][day].typeCar(train, ticket.people(), carriage, seats);
	ticket.cost(railway[roate][day].price(train, carriage, ticket.people()));
	if (!payment())
	{
		__deleteArr(seats, ticket.people());
		return Ticket();
	}
	std::string flight1 = "������ ��������", flight2 = "������";
	if (roate == 0)
	{
		flight1 = "������";
		flight2 = "������ ��������";
	}
	std::cout << '\n';
	ticket.newSeats(number[roate][train], time[roate][0][train], time[roate][1][train], carriage + 1, seats, flight1, flight2, date);
	__deleteArr(seats, ticket.people());
	return ticket;
}

void RailTicketOffice::__printTable(const int route)
{
	if (route == 0)
		std::cout << "����: ������ - ������ ��������\n";
	else
		std::cout << "����: ������ �������� - ������\n";
	for (int i = 0; i < 5; i++)
	{
		std::cout << number[route][i] << ' ' << time[route][0][i] << " - " << time[route][1][i] << ' ';
		__info(i);
	}
	std::cout << '\n';
}
