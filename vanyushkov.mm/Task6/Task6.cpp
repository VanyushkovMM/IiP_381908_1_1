#include "Bulls_Cows.h"
#include <Windows.h>
#include <clocale>
#include <iostream>

// Очистка экрана
void clrscr()
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int col = Attr;
	int width = buf.dwSize.X;
	int height = buf.dwSize.Y;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;
	SetConsoleCursorPosition(Console, zpos);

	FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
	FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

int main()
{
	setlocale(0, "");
	Bulls_Cows game;
	int len, attempt(0), close;
	do
	{
		do
		{
			std::cout << "Введите длину числа (1-10): ";
			std::cin >> len;
		} while (!game.newNumber(len));
		std::cout << "Число загадано!\n\n";

		int bull(0), cow(0);
		std::string number;
		bool end;

		do
		{
			do
			{
				std::cout << "Введите число: ";
				std::cin >> number;
			} while (!game.checkCorrect(number));

			attempt++;
			end = game.checkBullCow(number, bull, cow);
			std::cout << "Быков: " << bull << "\nКоров: " << cow << '\n';

		} while (!end);

		std::cout << "\n    Вы выиграли!\n    Количество ходов: " << attempt << '\n' << "Новая игра - 0\nВыход - 1\n";
		do
		{
			std::cout << "Команда: ";
			std::cin >> close;
		} while (close < 0 || close > 1);
		clrscr();

	} while (!close);
}