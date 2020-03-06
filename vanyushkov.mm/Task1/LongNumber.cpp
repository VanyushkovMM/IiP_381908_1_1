#include "LongNumber.h"

typedef unsigned int uint; // Беззнаковое целое (int)

// Конструктор по умолчанию
LongNumber::LongNumber()
{
	number = 0;
	high_part = 0;
	low_part = 0;
	sign = 1;
}

// Конструктор копирования
LongNumber::LongNumber(const LongNumber& num)
{
	number = 0;
	high_part = num.high_part;
	low_part = num.low_part;
	sign = num.sign;
}

// Конструктор преобразования типа
LongNumber::LongNumber(const long long& num)
{
	number = 0;
	if (num < 0) // Проверка на знак числа
	{
		low_part = (num * (-1)) & 0xffffffff;
		sign = -1;
	}
	else
	{
		low_part = num & 0xffffffff;
		sign = 1;
	}
	high_part = (uint)(num / 0x100000000); // num / 2^32
}

// Деструктор
LongNumber::~LongNumber()
{
	number = 0;
	high_part = 0;
	low_part = 0;
	sign = 1;
}

// Модуль числа
void LongNumber::Abs(const LongNumber& num)
{
	if (num.high_part < 0) // Проверка старшей части на знак числа
	{
		high_part = -1 * num.high_part;
	}
	else
		high_part = num.high_part;
	sign = 1;
	low_part = num.low_part;
}

// Сложение 2 положительных чисел
LongNumber LongNumber::Add(const LongNumber& num)
{
	LongNumber Result;
	int flag = 0; // Флаг перехода числа из младшей части в старшую
	Result.low_part = (low_part + num.low_part) & 0xffffffff;
	if (0xffffffff - low_part < num.low_part)
		flag++;
	Result.high_part = (high_part + num.high_part + sign * flag) & 0xffffffff;
	Result.sign = sign;

	return Result;
}

// Разность 2 положительных чисел
LongNumber LongNumber::Sub(const LongNumber& num)
{
	LongNumber Result;
	int flag = 0; // Флаг перехода числа из старшей части в младшую
	if (low_part < num.low_part)
		flag = (int)((low_part - num.low_part + 0x100000000) / 0x100000000);
	Result.low_part = (low_part - num.low_part + 0x100000000) & 0xffffffff;
	Result.high_part = high_part - num.high_part - flag;

	return Result;
}

// Произведение 2 положительных чисел
LongNumber LongNumber::Mul(const LongNumber& num)
{
	LongNumber Result, _num(num), tmp(*this); // _num = num, tmp = *this
	// Произведение проводится по типу: 12 * 34 = (12 * 4) + (12 * 30) = (12 * 4) + (120 * 3)
	int x = _num.low_part % 10; // Последняя (младшая) цифра числа _num (x)
	while (_num.high_part || (_num.low_part / 10)) // Пока не осталась одна цифра от числа
	{
		int flag = 0; // Флаг перехода числа из старшей части в младшую (и наоборот)
		// Произведение числа tmp на x
		for (int i = 0; i < x; i++)
		{
			if (0xffffffff - tmp.low_part < Result.low_part)
				flag++;
			Result.low_part = (Result.low_part + tmp.low_part) & 0xffffffff;
		}
		Result.high_part = (Result.high_part + tmp.high_part * x + flag) & 0xffffffff;
		// Деление числа _num на 10
		flag = _num.high_part % 10;
		_num.high_part /= 10;
		_num.low_part = (uint)((_num.low_part + flag * 0x100000000) / 10);
		// Произведение числа tmp на 10
		flag = 0;
		uint _low = tmp.low_part;
		for (int i = 1; i < 10; i++)
		{
			if (0xffffffff - tmp.low_part < _low)
				flag++;
			tmp.low_part = (tmp.low_part + _low) & 0xffffffff;
		}
		tmp.high_part = (tmp.high_part * 10 + flag) & 0xffffffff;
		x = _num.low_part % 10; // Новая младшая цифра числа _num
	}
	// Произведение числа tmp на оставшуюся цифру числа _num
	int flag = 0; // Флаг перехода числа из старшей части в младшую (и наоборот)
	for (int i = 0; i < x; i++)
	{
		if (0xffffffff - tmp.low_part < Result.low_part)
			flag++;
		Result.low_part = (Result.low_part + tmp.low_part) & 0xffffffff;
	}
	Result.high_part = (Result.high_part + tmp.high_part * x + flag) & 0xffffffff;

	return Result;
}

// Частное 2 положительных чисел
LongNumber LongNumber::Div(const LongNumber& num)
{
	LongNumber Result;
	Result.high_part = (int)(((high_part * 0x100000000 + low_part) / (num.high_part * 0x100000000 + num.low_part)) / 0x100000000);
	Result.low_part = ((high_part * 0x100000000 + low_part) / (num.high_part * 0x100000000 + num.low_part)) & 0xffffffff;

	return Result;
}

// Остаток от деления 2 положительных чисел
LongNumber LongNumber::Mod(const LongNumber& num)
{
	LongNumber Result = (*this) / num;
	Result = Result * num;
	if (Result.high_part == 0 && Result.low_part == 0)
		return *this;

	Result = (*this) - Result;

	return Result;
}

// Перегрузка операций ------------------------------------------

// Оператор присваивания
LongNumber& LongNumber::operator= (const LongNumber& num)
{
	low_part = num.low_part;
	high_part = num.high_part;
	sign = num.sign;

	return *this;
}

// Оператор сложения
LongNumber LongNumber::operator+ (const LongNumber& num)
{
	if (sign == num.sign) // Проверка равенства знаков
	{
		LongNumber* tmp = new LongNumber(this->Add(num));
		return *tmp;
	}
	else if (sign == 1) // Проверка положительного знака *this
	{
		LongNumber _num;
		_num.Abs(num);
		LongNumber* tmp = new LongNumber(this->Sub(_num));

		if (tmp->high_part < 0) // Проверка на отрицательные малые числа
		{
			tmp->high_part++;
			tmp->low_part = (uint)0x100000000 - tmp->low_part;
			tmp->sign = -1;
		}

		return *tmp;
	}
	else
	{
		LongNumber* _num = new LongNumber(*this);
		_num->Abs(*_num);
		LongNumber* x = new LongNumber(num);
		LongNumber* tmp = new LongNumber(_num->Sub(*x));
		tmp->sign = -1;
		tmp->high_part *= -1;
		return *tmp;
	}
}

// Оператор разности
LongNumber LongNumber::operator- (const LongNumber& num)
{
	if (sign == 1) // Проверка положительного знака числа *this
	{
		if (sign == num.sign) // Проверка равенства знаков
		{
			LongNumber* tmp = new LongNumber(this->Sub(num));
			return *tmp;
		}
		else
		{
			LongNumber _num;
			_num.Abs(num);
			LongNumber* tmp = new LongNumber(this->Add(_num));
			return *tmp;
		}
	}
	else
	{
		if (num.sign == 1) // Проверка положительного знака числа num
		{
			LongNumber _num;
			_num.Abs(*this);
			LongNumber* tmp = new LongNumber(_num.Add(num));
			return *tmp;
		}
		else
		{
			LongNumber x;
			x.Abs(*this);
			LongNumber _num;
			_num.Abs(num);

			LongNumber* tmp = new LongNumber(_num.Sub(x));
			if (tmp->high_part < 0)
				tmp->sign = -1;
			if (tmp->low_part > 0)
			{
				tmp->high_part++;
				tmp->low_part = (uint)0x100000000 - tmp->low_part;
			}
			return *tmp;
		}
	}
}

// Оператор умножения
LongNumber LongNumber::operator* (const LongNumber& num)
{
	LongNumber x, y;
	x.Abs(*this);
	y.Abs(num);
	LongNumber* tmp;
	// Произведение положительных чисел
	if (x.high_part == 0 && y.high_part != 0)
		tmp = new LongNumber(y.Mul(x));
	else
		tmp = new LongNumber(x.Mul(y));

	(*tmp).sign = (*this).sign * num.sign;
	if ((*tmp).sign == -1) // Определение знака числа
		(*tmp).high_part *= -1;
	return *tmp;
}

// Оператор деления
LongNumber LongNumber::operator/ (const LongNumber& num)
{
	if (num.high_part == 0 && num.low_part == 0)
	{
		std::cout << "Error! Division by zero attempt! Number assigned value " << *this << std::endl;
		return *this;
	}
	else
	{
		LongNumber x, y;
		x.Abs(*this);
		y.Abs(num);
		LongNumber* tmp = new LongNumber(x.Div(y)); // Частное положительных чисел
		(*tmp).sign = (*this).sign * num.sign;
		if ((*tmp).sign == -1) // Определение знака числа
			(*tmp).high_part *= -1;
		return *tmp;
	}
}

// Оператор остатка от деления
LongNumber LongNumber::operator% (const LongNumber& num)
{
	LongNumber x, _num;
	x.Abs(*this);
	_num.Abs(num);

	LongNumber* tmp = new LongNumber(x.Mod(_num));
	tmp->sign = sign * num.sign;

	return *tmp;
}

// Оператор сложения с присваиванием
LongNumber& LongNumber::operator+= (const LongNumber& num)
{
	*this = *this + num;
	return *this;
}

// Оператор разности с присваиванием
LongNumber& LongNumber::operator-= (const LongNumber& num)
{
	*this = *this - num;
	return *this;
}

// Оператор умножения с присваиванием
LongNumber& LongNumber::operator*= (const LongNumber& num)
{
	*this = *this * num;
	return *this;
}

// Оператор деления с присваиванием
LongNumber& LongNumber::operator/= (const LongNumber& num)
{
	*this = *this / num;
	return *this;
}

// Оператор остатка от деления с присваиванием
LongNumber& LongNumber::operator%= (const LongNumber& num)
{
	*this = *this % num;
	return *this;
}

// Префикс суммы
LongNumber& LongNumber::operator++ ()
{
	*this = *this + 1;
	return *this;
}

// Постфикс суммы
LongNumber& LongNumber::operator++ (int)
{
	*this = *this + 1;
	return *this;
}

// Префикс разности
LongNumber& LongNumber::operator-- ()
{
	*this = *this - 1;
	return *this;
}

// Постфикс разности
LongNumber& LongNumber::operator-- (int)
{
	*this = *this - 1;
	return *this;
}

// Унарный минус
LongNumber LongNumber::operator- ()
{
	LongNumber tmp = *this;
	tmp = tmp * (-1);
	return tmp;
}

// Оператор не
bool LongNumber::operator! ()
{
	if (low_part == 0 && high_part == 0)
		return true;
	return false;
}

// Оператор равенства
bool LongNumber::operator== (const LongNumber& num)
{
	return low_part == num.low_part && high_part == num.high_part && sign == num.sign;
}

// Оператор неравенства
bool LongNumber::operator!= (const LongNumber& num)
{
	return low_part != num.low_part || high_part != num.high_part || sign != num.sign;
}

// Оператор больше
bool LongNumber::operator> (const LongNumber& num)
{
	if (high_part > num.high_part) // Проверка старшей части
		return true;
	else if (high_part == num.high_part)
		if (sign == num.sign) // Проверка равенства знаков
			if (sign == 1) // Проверка положительного знака
				return low_part > num.low_part;
			else
				return low_part < num.low_part;
		else
			if (sign == 1) // Проверка положительного знака
				return true;
			else
				return false;
	return false;
}

// Оператор больше или равно
bool LongNumber::operator>= (const LongNumber& num)
{
	return *this > num || *this == num;
}

// Оператор меньше
bool LongNumber::operator< (const LongNumber& num)
{
	if (high_part < num.high_part) // Проверка старшей части
		return true;
	else if (high_part == num.high_part)
		if (sign == num.sign) // Проверка равенства знаков
			if (sign == 1) // Проверка положительного знака
				return low_part < num.low_part;
			else
				return low_part > num.low_part;
		else
			if (sign == 1) // Проверка положительного знака
				return false;
			else
				return true;
	return false;
}

// Оператор меньше или равно
bool LongNumber::operator<= (const LongNumber& num)
{
	return *this < num || *this == num;
}

// Вывод на консоль через std::cout <<
std::ostream& operator<< (std::ostream& stream, const LongNumber& num)
{
	if (num.sign > 0) // Проверка на знак числа
		stream << num.high_part * 0x100000000 + num.low_part;
	else
		stream << num.high_part * 0x100000000 - num.low_part;
	return stream;
}

// Ввод числа через консоль через std::cin >>
std::istream& operator>> (std::istream& stream, LongNumber& num)
{
	num.number = new char[50]; // Строка для ввода числа с консоли
	stream >> num.number;
	// Проверка правильности введенного числа ---------------------------
	bool Err, Num;
	Err = false; // Проверка на ошибки
	Num = true;	 // Проверка на отсутствие чисел

	int tmp = 0;
	if (num.number[0] == '-') // Проверка на наличие знака числа
		tmp++;
	for (int i = tmp; num.number[i] != 0; i++)
	{
		if (num.number[i] < '0' || num.number[i] > '9') // Проверка на другие символы
			Err = true;
		else
			Num = false;
	}
	if (Err || Num) // Проверка на наличие ошибок в числе ---------------
		std::cout << "Wrong! Number assigned value 0!" << std::endl;
	// Преобразование в число, если отсутствуют ошибки ------------------
	else
	{
		num.sign = 1;
		num.high_part = 0;
		num.low_part = 0;
		int _num[50] = { 0 }; // Массив перевода из строки в число
		int n = 0; // Количество разрядов
		for (int i = 0; num.number[i] != 0; i++, n++)
			if (num.number[i] == '-') // Проверка на знак
				_num[i] = -1;
			else
				_num[i] = num.number[i] - '0';
		delete(num.number);
		num.number = 0;

		int tmp = 0;
		if (_num[0] == -1) // Проверка на знак
		{
			tmp++;
			num.sign = -1;
		}

		num.low_part = _num[tmp]; // Добавление первой цифры числа
		for (int i = tmp + 1; i < n; i++)
		{
			uint tmp = num.low_part;
			uint flag = 0;
			// Умножение числа на 10
			for (int j = 1; j < 10; j++)
			{
				if (0xffffffff - tmp < num.low_part)
					flag++;
				num.low_part = (num.low_part + tmp) & 0xffffffff;
			}
			num.high_part = (num.high_part * 10 + flag) & 0xffffffff;
			// Добавление в конец числа
			flag = 0;
			if (0xffffffff - _num[i] < num.low_part)
				flag++;
			num.low_part = (num.low_part + _num[i]) & 0xffffffff;
			num.high_part = (num.high_part + flag) & 0xffffffff;
		}
		num.high_part = num.high_part * num.sign; // Знак числа
	}

	return stream;
}