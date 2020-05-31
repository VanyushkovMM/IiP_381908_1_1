#include "GorkyRailway.h"

GorkyRailway::GorkyRailway()
{
	for (int j = 0; j < 8; j++)
		lastochka[0][j] = lastochka[1][j] = lastochka[2][j] = LASTOCHKA;
	firmSV[0] = firmSV[1] = SV;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 2; j++)
			firmCoupe[i][j] = COUPE;
	for (int i = 0; i < 4; i++)
	{
		firmReserved[i][0] = firmReserved[i][1] = RESERVED;
		fastCoupe[i][0] = fastCoupe[i][1] = COUPE;
	}
	for (int i = 0; i < 8; i++)
		fastReserved[i][0] = fastReserved[i][1] = RESERVED;
}

int GorkyRailway::carReservate(const int train, const int passengers)
{
	int carriage = -1;
	if (train < 3)
		for (int i = 0; i < 8; i++)
			if (lastochka[train][i] >= passengers)
				return i;
	if (train == 3)
	{
		int sv(-1), coupe(-1), reserved(-1), tmp(0);
		for (int i = 0; i < 2; i++)
			if (firmSV[i] >= passengers)
			{
				if (tmp == 0)
					std::cout << "Наличие свободных мест:\n";
				tmp++;
				sv = i;
				std::cout << "1 - СВ\n";
				break;
			}
		for (int i = 0; i < 6; i++)
			if (firmCoupe[i][0] + firmCoupe[i][1] >= passengers)
			{
				if (tmp == 0)
					std::cout << "Наличие свободных мест:\n";
				tmp++;
				coupe = i;
				std::cout << "2 - Купе\n";
				break;
			}
		for (int i = 0; i < 4; i++)
			if (firmReserved[i][0] + firmReserved[i][1] >= passengers)
			{
				if (tmp == 0)
					std::cout << "Наличие свободных мест:\n";
				tmp++;
				reserved = i;
				std::cout << "3 - Плацкарт\n";
				break;
			}
		if (tmp != 0)
		{
			while (!(sv != -1 && carriage == 1 || coupe != -1 && carriage == 2 || reserved != -1 && carriage == 3))
			{
				std::cout << "Выберите тип вагона из представленных: ";
				std::cin >> carriage;
			}
			if (carriage == 1)
				return sv;
			if (carriage == 2)
				return coupe + 2;
			return reserved + 8;
		}
	}
	if (train == 4)
	{
		int coupe(-1), reserved(-1), type(0);
		for (int i = 0; i < 4; i++)
			if (fastCoupe[i][0] + fastCoupe[i][1] >= passengers)
			{
				coupe = i;
				type++;
				break;
			}
		for (int i = 0; i < 8; i++)
			if (fastReserved[i][0] + fastReserved[i][1] >= passengers)
			{
				reserved = i;
				type += 2;
				break;
			}
		if (type == 1)
			return coupe;
		if (type == 2)
			return reserved + 4;
		if (type == 3)
		{
			std::cout << "1 - Купе\n2 - Плацкарт\n";
			while (carriage < 1 || carriage > 2)
			{
				std::cout << "Выберите тип вагона: ";
				std::cin >> carriage;
			}
			if (carriage == 1)
				return coupe;
			return reserved + 4;
		}
	}
	return -1;
}

void GorkyRailway::typeCar(const int train, const int passengers, const int carriage, int** seats)
{
	if (train < 3)
	{
		for (int i = 0; i < passengers; i++)
			seats[0][i] = LASTOCHKA - lastochka[train][carriage] + 1 + i;
		lastochka[train][carriage] -= passengers;
	}
	else if (train == 3)
	{
		if (carriage < 2)
		{
			for (int i = 0; i < passengers; i++)
				seats[0][i] = SV - firmSV[carriage] + 1 + i;
			firmSV[carriage] -= passengers;
		}
		else if (carriage < 8)
		{
			std::cout << "Нижние места: " << firmCoupe[carriage][0] << "\nВерхние места: " << firmCoupe[carriage][1] << '\n';
			int down(-1), up;
			while ((down < 0 || down > firmCoupe[carriage][0] || down > passengers) && (firmCoupe[carriage][1] - passengers + down >= 0))
			{
				std::cout << "Выберите количество нижних мест: ";
				std::cin >> down;
			}
			up = passengers - down;
			for (int i = 0; i < down; i++)
				seats[0][i] = COUPE - firmCoupe[carriage][0] + 1 + i;
			firmCoupe[carriage][0] -= down;
			for (int i = 0; i < up; i++)
				seats[1][i] = COUPE - firmCoupe[carriage][1] + 1 + i;
			firmCoupe[carriage][1] -= up;
		}
		else
		{
			std::cout << "Нижние места: " << firmReserved[carriage][0] << "\nВерхние места: " << firmReserved[carriage][1] << '\n';
			int down(-1), up;
			while ((down < 0 || down > firmReserved[carriage][0] || down > passengers) && (firmReserved[carriage][1] - passengers + down >= 0))
			{
				std::cout << "Выберите количество нижних мест: ";
				std::cin >> down;
			}
			up = passengers - down;
			for (int i = 0; i < down; i++)
				seats[0][i] = RESERVED - firmReserved[carriage][0] + 1 + i;
			firmReserved[carriage][0] -= down;
			for (int i = 0; i < up; i++)
				seats[1][i] = RESERVED - firmReserved[carriage][1] + 1 + i;
			firmReserved[carriage][1] -= up;
		}
	}
	else
	{
		if (carriage < 4)
		{
			std::cout << "Нижние места: " << fastCoupe[carriage][0] << "\nВерхние места: " << fastCoupe[carriage][1] << '\n';
			int down(-1), up;
			while ((down < 0 || down > fastCoupe[carriage][0] || down > passengers) && (fastCoupe[carriage][1] - passengers + down >= 0))
			{
				std::cout << "Выберите количество нижних мест: ";
				std::cin >> down;
			}
			up = passengers - down;
			for (int i = 0; i < down; i++)
				seats[0][i] = COUPE - fastCoupe[carriage][0] + 1 + i;
			fastCoupe[carriage][0] -= down;
			for (int i = 0; i < up; i++)
				seats[1][i] = COUPE - fastCoupe[carriage][1] + 1 + i;
			fastCoupe[carriage][1] -= up;
		}
		else
		{
			std::cout << "Нижние места: " << fastReserved[carriage][0] << "\nВерхние места: " << fastReserved[carriage][1] << '\n';
			int down(-1), up;
			while ((down < 0 || down > fastReserved[carriage][0] || down > passengers) && (fastReserved[carriage][1] - passengers + down >= 0))
			{
				std::cout << "Выберите количество нижних мест: ";
				std::cin >> down;
			}
			up = passengers - down;
			for (int i = 0; i < down; i++)
				seats[0][i] = RESERVED - fastReserved[carriage][0] + 1 + i;
			fastReserved[carriage][0] -= down;
			for (int i = 0; i < up; i++)
				seats[1][i] = RESERVED - fastReserved[carriage][1] + 1 + i;
			fastReserved[carriage][1] -= up;
		}
	}
}

float GorkyRailway::price(const int train, const int carriage, const int passengers)
{
	float cost = (float)passengers;
	if (train < 3)
		cost *= priceL;
	else if (train == 3)
		if (carriage < 2)
			cost *= firmS;
		else if (carriage < 8)
			cost *= firmC;
		else
			cost *= firmR;
	else
		if (carriage < 4)
			cost *= fastC;
		else
			cost *= fastR;
	return cost;
}
