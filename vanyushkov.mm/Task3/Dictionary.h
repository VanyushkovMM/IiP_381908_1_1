#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

constexpr int MAXWORDS = 50000; // Максимальное количество слов в словаре
constexpr int MAXRUSW = 15;     // Максимальное количество переводов одного слова

struct Words
{
	std::string english;  // Английское слова
	int ruswords;         // Количество русских слов
	std::string* russian; // Перевод на русский

	// По умолчанию
	Words();

	// Копирование
	Words(const Words& word); 

	// Деструктор
	~Words();

	// Присваивание (копирование)
	Words& operator= (const Words& word); 

	// Слияние переводов слова
	Words operator+ (const Words& word);
};

class Dictionary
{
	Words* dictionary; // Список слов-переводов
	int words;         // Количество переводов

	// Выстроение в алфавитном порядке (вставка слова)
	void sort();

	// Поиск позиции слова в словаре
	int searchPosition(const std::string& strE); 

public:
	// По умолчанию
	Dictionary();

	// Копирование
	Dictionary(const Dictionary& dict); 

	// Деструктор
	~Dictionary();

	// Присваивание словарей (копирование)
	Dictionary& operator= (const Dictionary& dict); 

	// Добавить слово в словарь
	void AddWord(const std::string& strE, const std::string& strR);    
	
	// Изменить перевод указанного слова
	void ChangeWord(const std::string& strE);

	// Перевод слова
	bool TranslateWord(const std::string& strE, std::string& strR); 

	// Проверить наличие слова
	bool CheckWord(const std::string& strE); 

	// Количество слов в словаре
	int CountWords(); 

	// Слияние двух словарей
	friend Dictionary Marge(const Dictionary& dict1, const Dictionary& dict2); 

	// Считывание словаря из файла
	friend void readDict(Dictionary& dict, std::string str); 

	// Запись словаря в файл
	friend void saveDict(const Dictionary& dict, std::string str); 

	// Вывод словаря на консоль
	void printDict();
};

// Функции теперь используются только внутри Dictionary.cpp