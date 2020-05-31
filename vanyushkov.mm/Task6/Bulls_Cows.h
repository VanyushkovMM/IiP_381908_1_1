#pragma once
#include <string>
#include <ctime>
#include <cstdlib>

class Bulls_Cows
{
	int* number; // Загадываемое число
	int length;  // Количество символов в числе

public:
	Bulls_Cows();  // Конструктор
	~Bulls_Cows(); // Деструктор

	// Новое число (в стандартной игре длина слова 4)
	bool newNumber(const int length = 4); 

	// Проверка введенного числа пользователем
	bool checkCorrect(const std::string num); 

	// Проверка на конец игры и возврат количества быков и коров
	bool checkBullCow(std::string num, int& bull, int& cow); 
};
