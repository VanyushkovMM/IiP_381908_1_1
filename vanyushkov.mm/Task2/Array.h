#pragma once

enum class ExceptionType { outOfBoundsArray, sizeError, fewArguments };

// Структура ошибок
struct Exception
{
	ExceptionType error;
	Exception(ExceptionType _error);
};

// Класс Массив (независим от класса Матрица)
class Array
{
	int* array; // Массив
	int size;   // Размер массива

public:
	Array(); // По умолчанию
	~Array(); // Деструктор

	// Перегрузка операций индексации столбцов
	int& operator[] (const int index);
	const int& operator[] (const int index) const;

	friend class Matrix;
};