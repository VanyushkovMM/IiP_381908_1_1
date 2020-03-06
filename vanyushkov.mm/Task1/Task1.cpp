//#include <iostream>
#include "LongNumber.h"
#include <clocale>

// Краткое руководство:
// Число представляется в виде старшей части и младшей
// Старшая часть числа (int) равна (num / 2^32)
// Младшая часть числа (uint) равна (num % 2^32 == num & 0xffffffff)
// Знак числа sign используется для работы с младшей частью числа
// Присутствуют все стандартные арифметические и логические операции, конструкторы и деконструктор, потоковый (ввод с консоли / вывод на консоль)
// Все комментарии ошибок (например деление на 0) выводятся на английском языке
// Добавлена проверка на вывод с файл и считывание из файла

int main()
{
	setlocale(LC_CTYPE, "Rus");
	std::ofstream fout("output.txt");

	LongNumber x, y, z;
	std::cout << "Введите 2 числа: ";
	std::cin >> x >> y;

	z = x + y;
	std::cout << x << " + " << y << " = " << z << std::endl;
	fout << z << std::endl;

	z = x - y;
	std::cout << x << " - " << y << " = " << z << std::endl;
	fout << z << std::endl;

	std::cout << z << " + " << x << " = ";
	z += x;
	std::cout << z << std::endl;
	fout << z << std::endl;

	std::cout << "x++ = ";
	x++;
	std::cout << x << std::endl;
	fout << z << std::endl;

	z = x * 3;
	std::cout << x << " * 3 = " << z << std::endl;
	fout << z << std::endl;

	z = x * y;
	std::cout << x << " * " << y << " = " << z << std::endl;
	fout << z << std::endl;

	z = x / -y;
	std::cout << x << " / " << -y << " = " << z << std::endl;
	fout << z << std::endl;

	z = x % y;
	std::cout << x << " % " << y << " = " << z << std::endl;
	fout << z << std::endl;

	z = x;
	if (x == z)
	{
		std::cout << x << " == " << z << std::endl;
		fout << '1' << std::endl;
	}

	if (x >= z)
	{
		std::cout << x << " >= " << z << std::endl;
		fout << '1' << std::endl;
	}

	if (x >= z - 1)
	{
		std::cout << x << " >= " << z - 1 << std::endl;
		fout << '1' << std::endl;
	}
	else
	{
		std::cout << x << " < " << z - 1 << std::endl;
		fout << '0' << std::endl;
	}

	if (x != y)
	{
		std::cout << x << " != " << y << std::endl;
		fout << '1' << std::endl;
	}

	if (-x < y)
	{
		std::cout << -x << " < " << y << std::endl;
		fout << '1' << std::endl;
	}
	else
	{
		std::cout << -x << " > " << y << std::endl;
		fout << '0' << std::endl;
	}
	
	x = 0;
	if (!x)
	{
		std::cout << "x == 0" << std::endl;
		fout << '1' << std::endl;
	}

	for (LongNumber i = 1; i < 11; i++)
	{
		std::cout << i << ' ';
		fout << i << ' ';
	}
	std::cout << std::endl;
	fout << std::endl;
	fout.close();

	std::ifstream fin("input.txt");
	fin >> x >> y;
	if (x == 1000 && y == -99999999999)
		std::cout << "Считывание с файла сделано без ошибок" << std::endl;
	else
		std::cout << "Ошибка при считывании с файла" << std::endl;
	fin.close();

	return 0;
}