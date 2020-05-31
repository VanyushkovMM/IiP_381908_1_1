#pragma once
#include "Film.h"

constexpr int BUF = 50;

class FilmLibrary
{
	Film* films;  // Фильмы
	int quantity; // Количество фильмов
	int bufsize;  // Буфер

public:
	FilmLibrary();                           // По умолчанию
	FilmLibrary(const FilmLibrary& library); // Копирования
	~FilmLibrary();                          // Деструктор
	FilmLibrary& operator= (const FilmLibrary& library); // Присваивания

	bool PrintLibrary();
	bool AddFilm();
	bool AddFilm(Film& film);
	bool ChangeFilm(const std::string name);
	Film SearchFilm(const std::string name, const int year);
	FilmLibrary ProducerFilms(const std::string producer);
	FilmLibrary YearFilms(const int year);
	FilmLibrary FundFilms(const int numbers);
	FilmLibrary FundYearFilms(const int numbers, const int year);
	int CountFilms();
	bool DeleteFilm(const std::string name);

	friend void ReadFilms(FilmLibrary& library, const std::string str);
	friend void SaveFilms(const FilmLibrary& library, const std::string str);

private:
	FilmLibrary& newBuf(const int buf);
	FilmLibrary __listfilms(const std::string producer, const int year);
	int search(const std::string comment, const std::string name);
	void fundsort(ll* mas, int first, int last) const; // Сортировка фильмов по сборам
	FilmLibrary& sortAndAdd(const FilmLibrary& library, ll* mas, const int _size, const int numbers);
	void insert(int position);
	bool operator== (const FilmLibrary& library);
};
