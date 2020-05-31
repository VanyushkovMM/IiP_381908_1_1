#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

typedef long long ll;

class Film
{
	std::string name;         // Название
	std::string producer;     // Режиссер
	std::string screenwriter; // Сценарист
	std::string composer;     // Композитор
	int day, mount, year;     // Дата выхода
	ll fundraising;           // Сборы
	
public:
	Film();                 // По умолчанию
	Film(const Film& film); // Копирования
	~Film();                // Деструктор
	Film& operator= (const Film& film); // Присваивания
	void NewFilm(const std::string _name, const std::string _producer, const std::string _screenwriter, 
		const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising); // Заполнение информации о фильме
	Film(const std::string _name, const std::string _producer, const std::string _screenwriter, 
		const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising); // Инициализация

	Film& Read(); // Считывание информации о фильме с консоли
	bool Write(); // Вывод информации о фильме на консоль
	friend void swap(Film& f1, Film& f2);

	/// Возврат определенной информации о фильме
	friend std::string Name(const Film& film) { return film.name; }
	friend std::string Producer(const Film& film) { return film.producer; }
	friend std::string Screenwriter(const Film& film) { return film.screenwriter; }
	friend std::string Composer(const Film& film) { return film.composer; }
	friend int Day(const Film& film) { return film.day; }
	friend int Mount(const Film& film) { return film.mount; }
	friend int Year(const Film& film) { return film.year; }
	friend ll Fund(const Film& film) { return film.fundraising; } 

	friend std::istream& operator>> (std::istream& stream, Film& film);       // Считывание с файла
	friend std::ostream& operator<< (std::ostream& stream, const Film& film); // Запись в файл

	bool operator!= (const Film& film);
}; 
