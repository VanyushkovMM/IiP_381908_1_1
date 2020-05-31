#include "Bulls_Cows.h"

// Конструктор
Bulls_Cows::Bulls_Cows()
{
	length = 0;
	number = nullptr;
}

// Деструктор
Bulls_Cows::~Bulls_Cows()
{
	if (length > 0)
		delete[] number;
	length = 0;
}

// Новое число (в стандартной игре длина слова 4)
bool Bulls_Cows::newNumber(const int length)
{
	if (length < 1 || length > 10)
		return false;
	number = new int[length];
	this->length = length;
	srand((int)time(0));
	for (int i = 0; i < length; i++)
	{
		number[i] = rand() % 10;
		for (int j = 0; j < i; j++)
			if (number[i] == number[j])
			{
				i--;
				break;
			}
	}
	return true;
}

// Проверка введенного числа пользователем
bool Bulls_Cows::checkCorrect(const std::string num)
{
	if (num.length() != length)
		return false;
	for (int i = 0; i < length - 1; i++)
		for (int j = i + 1; j < length; j++)
			if (num[i] == num[j])
				return false;
	return true;
}

// Проверка на конец игры и возврат количества быков и коров
bool Bulls_Cows::checkBullCow(std::string num, int& bull, int& cow)
{
	cow = bull = 0;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			if (number[i] == num[j] - '0')
				if (i == j)
					bull++;
				else
					cow++;
	if (bull == length)
		return true;
	return false;
}
