#include "Film.h"

// �� ���������
Film::Film()
{
	name = "";
	producer = "";
	screenwriter = "";
	composer = "";
	day = mount = year = 0;
	fundraising = 0;
}

// �����������
Film::Film(const Film& film)
{
	*this = film;
}

// ����������
Film::~Film()
{
	name = "";
	producer = "";
	screenwriter = "";
	composer = "";
	day = mount = year = 0;
	fundraising = 0;
}

// ������������
Film& Film::operator=(const Film& film)
{
	name = film.name;
	producer = film.producer;
	screenwriter = film.screenwriter;
	composer = film.composer;
	day = film.day;
	mount = film.mount;
	year = film.year;
	fundraising = film.fundraising;
	return *this;
}

// ���������� ���������� � ������
void Film::NewFilm(const std::string _name, const std::string _producer, const std::string _screenwriter, 
	const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising)
{
	name = _name;
	producer = _producer;
	screenwriter = _screenwriter;
	composer = _composer;
	day = _day;
	mount = _mount;
	year = _year;
	fundraising = _fundraising;
}

// �������������
Film::Film(const std::string _name, const std::string _producer, const std::string _screenwriter, 
	const std::string _composer, const int _day, const int _mount, const int _year, const ll _fundraising)
{
	this->NewFilm(_name, _producer, _screenwriter, _composer, _day, _mount, _year, _fundraising);
}

// ���������� ������
std::string readString(const std::string comment)
{
	std::string str;
	std::cout << comment << ": ";
	std::getline(std::cin, str);
	return str;
}

// ��������� �������� ���������� � ������ (���� ������ �� �����)
ll newNumber(const ll num, const std::string comment)
{
	std::string str = readString(comment);
	if (str != "")
		return std::stoll(str);
	return num;
}

// ��������� ��������� ���������� � ������ (���� ������ �� �����)
std::string newString(const std::string str, const std::string comment)
{
	std::string newStr = readString(comment);
	if (newStr != "")
		return newStr;
	return str;
}

// ���������� ���������� � ������ � �������
Film& Film::Read()
{
	name = newString(name, "��������");
	producer = newString(producer, "�������");
	screenwriter = newString(screenwriter, "���������");
	composer = newString(composer, "����������");
	day = (int)newNumber(day, "���� ������");
	mount = (int)newNumber(mount, "����� ������");
	year = (int)newNumber(year, "��� ������");
	fundraising = newNumber(fundraising, "�����");
	return *this;
}

// ����� ���������� � ������ � �������
bool Film::Write()
{
	if (name == "")
		return false;
	std::cout << "��������:    " << name << "\n��������:    " << producer
		<< "\n���������:   " << screenwriter << "\n����������:  " << composer
		<< "\n���� ������: " << day << "." << mount << "." << year
		<< "\n�����:       " << fundraising << "�.\n";
	return true;
}

bool Film::operator!=(const Film& film)
{
	if (name == film.name || producer == film.producer || screenwriter == film.screenwriter || composer == film.composer 
		|| day == film.day || mount == film.mount || year == film.year || fundraising == film.fundraising) return false;
	return true;
}

// swap �������
void swap(Film& f1, Film& f2)
{
	Film tmp = f1;
	f1 = f2;
	f2 = tmp;
}

// ���������� ���������� � ������ � �����
std::istream& operator>> (std::istream& stream, Film& film)
{
	std::getline(stream, film.name);
	std::getline(stream, film.producer);
	std::getline(stream, film.screenwriter);
	std::getline(stream, film.composer);
	stream >> film.day >> film.mount >> film.year >> film.fundraising;
	return stream;
}

// ����� ���������� � ������ � ����
std::ostream& operator<< (std::ostream& stream, const Film& film)
{
	stream << film.name << std::endl << film.producer
		<< std::endl << film.screenwriter << std::endl << film.composer
		<< std::endl << film.day << ' ' << film.mount << ' ' << film.year
		<< ' ' << film.fundraising << std::endl;
	return stream;
}
