#include "Matrix.h"
#include <clocale>

int main()
{
	setlocale(LC_CTYPE, "Russian");
	std::ofstream fout("output.txt");
	std::ifstream fin("input.txt");

	try
	{
		Matrix a(3, 1, 2, 3, 4, 5, 6, 7, 8, 9);
		Matrix b, c;
		std::cout << "Размер матрицы a: " << Size(a) << std::endl << a << std::endl;
		fout << Size(a) << std::endl << a << std::endl;

		std::cout << "Введите размер матрицы (желательно N = 3) и её элементы (N * N): \n";
		std::cin >> b;
		std::cout << std::endl << b << std::endl;
		fout << b << std::endl;

		c = a * b;
		std::cout << "a * b: \n";
		for (int i = 0; i < Size(c); i++)
		{
			for (int j = 0; j < Size(c); j++)
			{
				std::cout << c[i][j] << '\t';
				fout << c[i][j] << '\t';
			}
			std::cout << std::endl;
			fout << std::endl;
		}
		std::cout << std::endl;
		fout << std::endl;

		c.Transpose();
		std::cout << "Транспонирование: \n" << c << std::endl;
		fout << c << std::endl;

		c += a; // c = c + a;
		std::cout << "c + a: \n" << c << std::endl;
		fout << c << std::endl;

		b *= 3; // b = 3 * b;
		std::cout << "3 * b: \n" << b << std::endl;
		fout << b << std::endl;

		std::cout << "Считывание с файла двух матрицы для проверки диагонального преобладания: \n";
		for (int i = 0; i < 2; i++)
		{
			fin >> c;
			std::cout << c;
			if (c.DiagonallyDominant())
				std::cout << "Матрица обладает диагональным преобладанием \n";
			else
				std::cout << "Матрица НЕ обладает диагональным преобладанием \n";
			std::cout << std::endl;
		}

		c.ChangeSize(7);
		std::cout << "Изменение размера матрицы с сохранением элементов и заполнением новых числом 0: \n" << c << std::endl;
		fout << c << std::endl;

		c.Fill(3, 100);
		std::cout << "Заполение матрицы размера 3 одинаковыми элементами (100): \n" << c << std::endl;
		fout << c << std::endl;

		c.Unix(4);
		std::cout << "Единичная матрица размера 4: \n" << c << std::endl;
		fout << c << std::endl;
	}
	catch (Exception error)
	{
		switch (error.error)
		{
		case ExceptionType::outOfBoundsArray:
			std::cout << std::endl << "Ошибка! Выход за пределы границ массива! \n";
			fout << "-1 \n";
			break;
		case ExceptionType::sizeError:
			std::cout << std::endl << "Ошибка! Работа с матрицами разного размера! \n";
			fout << "-2 \n";
			break;
		case ExceptionType::fewArguments:
			std::cout << std::endl << "Ошибка! Недостаточно аргументов! \n";
			fout << "-3 \n";
			break;
		}
	}

	fin.close();
	fout.close();

	return 0;
}