#include "Array.h"

// Конструктор копирования
Exception::Exception(ExceptionType _error)
{
    error = _error;
}

// По умолчанию
Array::Array()
{
    array = 0;
    size = 0;
}

// Деструктор
Array::~Array()
{
    size = 0;
    delete[] array;
}

// Перегрузка операций индексации столбцов
int& Array::operator[](const int index)
{
    // Проверка выхода индекса за границу строки
    if (index < 0 || index >= size)
        throw Exception(ExceptionType::outOfBoundsArray); // Вызов ошибки
    return array[index];
}

// Перегрузка операций индексации столбцов
const int& Array::operator[] (const int index) const
{
    // Проверка выхода индекса за границу строки
    if (index < 0 || index >= size)
        throw Exception(ExceptionType::outOfBoundsArray); // Вызов ошибки
    return array[index];
}