#include "Matrix.h"

// По умолчанию
Matrix::Matrix()
{
    mtrx = 0;
    size = 0;
}

// Конструктор копирования
Matrix::Matrix(const Matrix& matrix)
{
    *this = matrix;
}

// Конструктор инициализации
Matrix::Matrix(int _size, ...)
{
    va_list list;
    va_start(list, _size);
    this->ChangeSize(_size, 0);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            int tmp = va_arg(list, int);
            if (tmp != -858993460)
                mtrx[i][j] = tmp;
            else
            {
                throw Exception(ExceptionType::fewArguments);
                va_end(list);
                return;
            }
        }
    va_end(list);
}

// Деструктор
Matrix::~Matrix()
{
    delete[] mtrx;
    size = 0;
}

// Оператор присваивания
Matrix& Matrix::operator= (const Matrix& matrix)
{
    // Проверка размера матрицы
    if (size != matrix.size)
    {
        if (size > 0) // Проверка на существование матрицы
            delete[] mtrx; // Очищение матрицы
        // Создание новой матрицы
        size = matrix.size;
        mtrx = new Array[size];
        for (int i = 0; i < size; i++)
        {
            mtrx[i].size = size;
            mtrx[i].array = new int[size];
        }
    }
    // Заполение матрицы элементами
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mtrx[i][j] = matrix.mtrx[i][j];
    return *this;
}

// Оператор суммирования
Matrix Matrix::operator+ (const Matrix& matrix)
{
    Matrix result;
    // Проверка размеров матрицы
    if (size == matrix.size)
    {
        // Суммирование матриц
        result = *this;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                result.mtrx[i][j] += matrix.mtrx[i][j];
    }
    else
        throw Exception(ExceptionType::sizeError); // Вызов ошибки
    return result;
}

// Оператор суммирования с присваиванием
Matrix& Matrix::operator+= (const Matrix& matrix)
{
    *this = *this + matrix;
    return *this;
}

// Оператор умножения
Matrix Matrix::operator* (const Matrix& matrix)
{
    Matrix result;
    // Проверка размеров матрицы
    if (size == matrix.size)
    {
        // Создание новой матрицы
        result.Fill(size, 0);
        // Умножение матриц
        for (int i = 0; i < size; i++)
            for (int k = 0; k < size; k++)
            {
                result.mtrx[k][i] = 0;
                for (int j = 0; j < size; j++)
                    result.mtrx[k][i] += (mtrx[k][j] * matrix.mtrx[j][i]);
            }
    }
    else
        throw Exception(ExceptionType::sizeError); // Вызов ошибки
    return result;
}

// Оператор умножения с присваиванием
Matrix& Matrix::operator*= (const Matrix& matrix)
{
    *this = *this * matrix;
    return *this;
}

// Оператор умножения матрицы на скаляр
Matrix Matrix::operator* (const int num)
{
    return num * (*this);
}

// Оператор умножение скаляра на матрицу
Matrix operator* (const int num, Matrix& matrix)
{
    Matrix result = matrix;
    for (int i = 0; i < result.size; i++)
        for (int j = 0; j < result.size; j++)
            result.mtrx[i][j] *= num;
    return result;
}

// Оператор умножения на скаляр с присваиванием
Matrix& Matrix::operator*= (const int num)
{
    *this = num * (*this);
    return *this;
}

// Оператор индексации строк
Array& Matrix::operator[] (const int index)
{
    // Проверка выхода индекса за границу столбца
    if (index < 0 || index >= size)
        throw Exception(ExceptionType::outOfBoundsArray); // Вызов ошибки
    return mtrx[index];
}

// Оператор индексации строк
const Array& Matrix::operator[] (const int index) const
{
    // Проверка выхода индекса за границу строки
    if (index < 0 || index >= size)
        throw Exception(ExceptionType::outOfBoundsArray); // Вызов ошибки
    return mtrx[index];
}

// Транспонирование
Matrix Matrix::Transpose()
{
    Matrix result;
    result.ChangeSize(size, 0);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result.mtrx[j][i] = mtrx[i][j];
    return result;
}

// Заполнение матрицы размера _size одинаковыми значениями elem
void Matrix::Fill(const int _size, const int elem)
{
    if (size > 0) // Проверка на существование матрицы
        delete[] mtrx;
    // Создание новой матрицы
    size = _size;
    mtrx = new Array[size];
    for (int i = 0; i < size; i++)
    {
        mtrx[i].size = size;
        mtrx[i].array = new int[size];
        // Заполнение числами elem
        for (int j = 0; j < size; j++)
            mtrx[i][j] = elem;
    }
}

// Изменение размера матрицы с сохранением элементов и заполнением elem пустого пространства
void Matrix::ChangeSize(const int _size, const int elem)
{
    Matrix tmp = *this;
    int n = size;
    if (_size < n)
        n = _size;
    this->Fill(_size, elem);
    // Заполнение матрицы старыми элементами
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mtrx[i][j] = tmp.mtrx[i][j];
}

// Изменение размера матрицы с сохранением элементов и заполнением нулями пустого пространства
void Matrix::ChangeSize(const int _size)
{
    this->ChangeSize(_size, 0);
}

// Единичная матрица размера _size
void Matrix::Unix(const int _size)
{
    this->Fill(_size, 0);
    // Заполнение главной диагонали единицами
    for (int i = 0; i < size; i++)
        mtrx[i][i] = 1;
}

// Возвращение размера матрицы
int Size(const Matrix& matrix)
{
    return matrix.size;
}

// Проверка матрицы на диагональное преобладание
bool Matrix::DiagonallyDominant()
{
    int k = 0; // Проверка на строгое неравенство
    for (int i = 0; i < size; i++)
    {
        int tmp = Abs(mtrx[i][i]); // Запоминание диагонального элемента
        int sum = 0;
        // Сумма всех элементов
        for (int j = 0; j < size; j++)
            sum += Abs(mtrx[i][j]);
        if (sum > 2 * tmp)
            return false;
        else
            if (sum == 2 * tmp) // Проверка на равенство
                k++;
    }
    if (k == size) // Отсутствие строгого неравенства
        return false;
    return true;
}

// Вывод матрицы
std::ostream& operator<< (std::ostream& stream, const Matrix& matrix)
{
    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
            stream << matrix.mtrx[i][j] << '\t';
        stream << std::endl;
    }
    return stream;
}

// Ввод размера матрицы и её элементов
std::istream& operator>> (std::istream& stream, Matrix& matrix)
{
    int _size;
    stream >> _size;
    // Создание матрицы
    matrix.ChangeSize(_size, 0);
    for (int i = 0; i < matrix.size; i++)
        for (int j = 0; j < matrix.size; j++)
            stream >> matrix.mtrx[i][j];
    return stream;
}

// Модуль числа
int Abs(int num)
{
    if (num < 0)
        return -num;
    return num;
}