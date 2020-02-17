#include <iostream>
#include <clocale>

//Определение косинуса угла
int sign_cos(double x, double y, double z)
{
	double res;
	res = (y * y + z * z - x * x) / (2 * y * z);
	if (res < 0)
		return -1; //Угол тупой
	else if (res == 0)
		return 0; //Угол прямой
	else
		return 1; //Угол острый
}

//Проверка на существование треугольника
int check(double x, double y, double z)
{
	if ((x < y + z) && (y < x + z) && (z < x + y))
		return 1; //Подверждение существования треугольника
	else
	{
		std::cout << std::endl << "Такого треугольника не существует!" << std::endl;
		return 0;
	}
}

//Вывод информации о треугольнике
void print(int x, int y, int z)
{
	std::cout << "Треугольник ";
	if ((x < 0) || (y < 0) || (z < 0))
		std::cout << "тупоугольный";
	else  if (!x || !y || !z)
		std::cout << "прямоугольный";
	else 
		std::cout << "остроугольный";
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_CTYPE, "rus"); //Добавление кириллицы
	double a, b, c; //Сторона треугольника
	int aa, bb, cc; //Угол противолежащей стороны

	//Ввод сторон треугольника
	do
	{
		std::cout << "Введите стороны треугольника: ";
		std::cin >> a >> b >> c;
	} while (!check(a, b, c));

	//Определение косинуса угла
	aa = sign_cos(a, b, c);
	bb = sign_cos(b, a, c);
	cc = sign_cos(c, a, b);

	//Вывод информации о треугольнике
	print(aa, bb, cc);

	return 0;
}