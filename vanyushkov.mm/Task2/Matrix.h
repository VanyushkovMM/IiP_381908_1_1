#pragma once
#include <iostream>
#include <fstream>
#include <cstdarg>
#include "Array.h" // подключение класса Массив

// Класс Матрица (зависим от класса Массив)
class Matrix
{
	Array* mtrx; // Матрица
	int size;    // Размер матрицы

public:
	Matrix();					  // По умолчанию
	Matrix(const Matrix& matrix); // Конструктор копирования
	Matrix(int _size, ...);		  // Конструктор инициализации
	~Matrix();					  // Деструктор
	// Перегрузка операций ------------------------------------
	// Оператор присваивания
	Matrix& operator= (const Matrix& matrix);

	// Оператор суммирования
	Matrix operator+ (const Matrix& matrix);
	// Оператор суммирования с присваиванием
	Matrix& operator+= (const Matrix& matrix);

	// Оператор умножения
	Matrix operator* (const Matrix& matrix);
	// Оператор умножения с присваиванием
	Matrix& operator*= (const Matrix& matrix);

	// Оператор умножения матрицы на скаляр
	Matrix operator* (const int num);
	// Оператор умножение скаляра на матрицу
	friend Matrix operator* (const int num, Matrix& matrix);
	// Оператор умножения на скаляр с присваиванием
	Matrix& operator*= (const int num);

	// Оператор индексации строк
	Array& operator[] (const int index);
	const Array& operator[] (const int index) const;

	// Транспонирование
	void Transpose();

	// Изменение размера матрицы с сохранением элементов и заполнением нулями нового пустого пространства
	void ChangeSize(const int _size);

	// Единичная матрица размера _size
	void Unix(const int _size);
	
	// Заполнение матрицы размера _size одинаковыми значениями elem
	void Fill(const int _size, int elem);
	
	// Возвращение размера матрицы
	friend int Size(const Matrix& matrix);
	
	// Проверка матрицы на диагональное преобладание
	bool DiagonallyDominant();

	// Вывод матрицы
	friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);

	// Ввод размера матрицы и её элементов
	friend std::istream& operator>> (std::istream& stream, Matrix& matrix);
};

int Abs(int num); // Модуль числа