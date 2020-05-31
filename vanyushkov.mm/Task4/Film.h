#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

typedef long long ll;

class Film
{
	std::string name;         // ��������
	std::string producer;     // ��������
	std::string screenwriter; // ���������
	std::string composer;     // ����������
	int day, mount, year;     // ���� ������
	ll fundraising;           // �����
	
public:
	Film();                 // �� ���������
	Film(const Film& film); // �����������
	~Film();                // ����������
	Film& operator= (const Film& film); // ������������
	void NewFilm(const std::string _name, const std::string _producer, const std::string _screenwriter, 
		const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising); // ���������� ���������� � ������
	Film(const std::string _name, const std::string _producer, const std::string _screenwriter, 
		const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising); // �������������

	Film& Read(); // ���������� ���������� � ������ � �������
	bool Write(); // ����� ���������� � ������ �� �������
	friend void swap(Film& f1, Film& f2);

	/// ������� ������������ ���������� � ������
	friend std::string Name(const Film& film) { return film.name; }
	friend std::string Producer(const Film& film) { return film.producer; }
	friend std::string Screenwriter(const Film& film) { return film.screenwriter; }
	friend std::string Composer(const Film& film) { return film.composer; }
	friend int Day(const Film& film) { return film.day; }
	friend int Mount(const Film& film) { return film.mount; }
	friend int Year(const Film& film) { return film.year; }
	friend ll Fund(const Film& film) { return film.fundraising; } 

	friend std::istream& operator>> (std::istream& stream, Film& film);       // ���������� � �����
	friend std::ostream& operator<< (std::ostream& stream, const Film& film); // ������ � ����

	bool operator!= (const Film& film);
}; 
