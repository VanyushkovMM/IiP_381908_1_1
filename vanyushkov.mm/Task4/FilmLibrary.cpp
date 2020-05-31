#include "FilmLibrary.h"

// ��������� 2 ����� �� ���������� �������
bool __comparison(std::string str1, std::string str2)
{
	size_t len = str1.length();
	size_t len1 = str2.length();
	if (len > len1)
		len = len1;
	for (size_t i = 0; i < len; i++)
	{
		if (str1[i] < str2[i])
			return true;
		else
			if (str1[i] > str2[i])
				return false;
	}
	if (str1.length() < str2.length())
		return true;
	return false;
}

// ������� � ����� ������ (���������� ������)
void __bin(std::istream& in)
{
	std::string bin;
	std::getline(in, bin);
}

// �� ���������
FilmLibrary::FilmLibrary()
{
	bufsize = BUF;
	films = new Film[bufsize];
	quantity = 0;
}

// �����������
FilmLibrary::FilmLibrary(const FilmLibrary& library)
{
	*this = library;
}

// ����������
FilmLibrary::~FilmLibrary()
{
	bufsize = 0;
	if (films != nullptr)
		delete[] films;
	quantity = 0;
}

// ����������� ������ ������ ���������� 
FilmLibrary& FilmLibrary::newBuf(const int buf)
{
	bufsize = buf;
	if (films != nullptr && quantity > 0)
		delete[] films;
	films = new Film[bufsize];
	return *this;
}

// ������������
FilmLibrary& FilmLibrary::operator=(const FilmLibrary& library)
{
	if (*this == library)
		return *this;
	if (films == nullptr || quantity < 0 || bufsize <= library.quantity)
		newBuf(library.bufsize);
	quantity = library.quantity;
	for (int i = 0; i < quantity; i++)
		films[i] = library.films[i];
	return *this;
}

// ����� ������ ������� �� �������
bool FilmLibrary::PrintLibrary()
{
	if (quantity == 0)
		return false;
	for (int i = 0; i < quantity; i++)
	{
		films[i].Write();
		std::cout << '\n';
	}
	return true;
}

// ���������� ������ � ����������
bool FilmLibrary::AddFilm()
{
	Film film;
	__bin(std::cin);
	film.Read(); // ���������� ���������� � ������
	return this->AddFilm(film);
}

// ���������� ������ � ����������
bool FilmLibrary::AddFilm(Film& film)
{
	if (quantity >= bufsize)
	{
		FilmLibrary tmp = *this;
		newBuf(bufsize + BUF);
		*this = tmp;
	}
	films[quantity++] = film;
	for (int i = 0; i < quantity - 1; i++)
		if (Name(films[i]) == Name(film))
		{
			int p = i;
			while (Name(films[p]) == Name(film) && Year(films[p]) != Year(film) && p < quantity - 1)
				p++;
			if (Name(films[p]) == Name(film))
			{
				quantity--;
				return false;
			}
			break;
		}
	insert(quantity - 1);
	return true;
}

// ����� ������� ������ ��� �������� ��� ��������� ������
int FilmLibrary::search(const std::string comment, const std::string name)
{
	int f = -1;
	for (int i = 0; i < quantity; i++)
		if (Name(films[i]) == name)
		{
			f = i;
			break;
		}
	if (f == -1) // ���� ����� �� ������
		return f;
	int l = f;
	while (Name(films[l]) == name && l < quantity)
		l++;
	if (l - 1 != f) // ���� ���� ��������� ������� � ���������� ���������
	{
		std::cout << "�������� �����, ������� ������ " << comment << ":\n";
		for (int i = f; i < l - 1; i++)
			std::cout << "\n����� " << i - f + 1 << ":\n" << films[i];
		int x = 0;
		while (x < 1 || x > l - f - 1)
		{
			std::cout << "\n������� �����: ";
			std::cin >> x;
		}
		f += x - 1;
	}
	return f;
}

// �������� ������ ������
bool FilmLibrary::ChangeFilm(const std::string name)
{
	int f = this->search("��������", name);
	if (f == -1)
		return false;
	films[f].Write();
	std::cout << std::endl;
	std::cout << "������� ����� ���������� ��� �������� ������� ������: \n";
	films[f].Read();
	insert(f);
	return true;
}

// ����� ������ 
Film FilmLibrary::SearchFilm(const std::string name, const int year)
{
	for (int i = 0; i < quantity; i++)
		if (Name(films[i]) == name)
		{
			int p = i;
			while (p < quantity && Name(films[p]) == name && Year(films[p]) != year)
				p++;
			if (Name(films[p]) == name)
				return films[p];
			break;
		}
	return Film(); // ���� ����� �� ������, ������������ ������ ����������
}

// ����� ������ ������� �� ��������� ��� ����
FilmLibrary FilmLibrary::__listfilms(const std::string producer, const int year)
{
	FilmLibrary library;
	for (int i = 0; i < quantity; i++)
		if ((Producer(films[i]) == producer && producer != "") || (Year(films[i]) == year && year != 0))
			library.AddFilm(films[i]);
	return library;
}

// ����� ������� ���������� ���������
FilmLibrary FilmLibrary::ProducerFilms(const std::string producer)
{
	return __listfilms(producer, 0);
}

// ����� ������� �� ����
FilmLibrary FilmLibrary::YearFilms(const int year)
{
	return __listfilms("", year);
}

// ���������� �������, ��������������� �� ������
FilmLibrary& FilmLibrary::sortAndAdd(const FilmLibrary& library, ll* mas, const int _size, const int numbers)
{
	library.fundsort(mas, 0, _size - 1);
	int n = min(numbers, _size);
	if (bufsize <= n)
		newBuf((n / BUF + 1) * BUF);
	for (int i = 0; i < n; i++)
		films[i] = library.films[mas[i]];
	quantity = n;
	return *this;
}

// ������ ����� �������� �������
FilmLibrary FilmLibrary::FundFilms(const int numbers)
{
	FilmLibrary library;
	ll* mas = new ll[quantity];
	for (int i = 0; i < quantity; i++)
		mas[i] = i;

	return library.sortAndAdd(*this, mas, quantity, numbers);
}

// ������ ����� �������� ������� �� ��������� ���
FilmLibrary FilmLibrary::FundYearFilms(const int numbers, const int year)
{
	FilmLibrary library;
	ll* mas = new ll[quantity];
	int j = 0;
	for (int i = 0; i < quantity; i++)
		if (Year(films[i]) == year)
			mas[j++] = i;
	if (j > 0)
		library.sortAndAdd(*this, mas, j, numbers);
	return library;
}

// ������� ���������� ������� � ����������
int FilmLibrary::CountFilms()
{
	return quantity;
}

// �������� ������
bool FilmLibrary::DeleteFilm(const std::string name)
{
	int f = this->search("�������", name);
	if (f == -1)
		return false;
	for (int i = f; i < quantity - 1; i++)
		films[i] = films[i + 1];
	quantity--;
	return true;
}

// ���������� ���������� � �����
void ReadFilms(FilmLibrary& library, const std::string str)
{
	std::ifstream fin(str);
	fin >> library.quantity;

	if (library.bufsize <= library.quantity)
		library.newBuf((library.quantity / BUF + 1) * BUF);
	for (int i = 0; i < library.quantity; i++)
	{
		__bin(fin);
		fin >> library.films[i];
	}
	fin.close();
}

// ������ ���������� � ����
void SaveFilms(const FilmLibrary& library, const std::string str)
{
	std::ofstream fout(str);
	fout << library.quantity << std::endl;
	for (int i = 0; i < library.quantity; i++)
		fout << library.films[i];
	fout.close();
}

// ������������ ������� � ���������� �������
void FilmLibrary::insert(int p)
{
	while (p > 0 && (__comparison(Name(films[p]), Name(films[p - 1])) 
		|| Name(films[p]) == Name(films[p - 1]) && Year(films[p]) < Year(films[p - 1])))
	{
		swap(films[p], films[p - 1]);
		p--;
	}
	while (p < quantity - 1 && (__comparison(Name(films[p + 1]), Name(films[p]))
		|| Name(films[p]) == Name(films[p + 1]) && Year(films[p]) > Year(films[p + 1])))
	{
		swap(films[p], films[p + 1]);
		p++;
	}
}

bool FilmLibrary::operator==(const FilmLibrary& library)
{
	if (quantity != library.quantity)
		return false;
	for (int i = 0; i < quantity; i++)
		if (films[i] != library.films[i])
			return false;
	return true;
}

// ���������� �� �������� ������
void FilmLibrary::fundsort(ll* mas, int first, int last) const
{
	int l = first, r = last;
	ll mid = Fund(films[mas[(first + last) / 2]]);
	do
	{
		while (Fund(films[mas[l]]) > mid)
			l++;
		while (Fund(films[mas[r]]) < mid)
			r--;
		if (l <= r)
		{
			if (l != r)
				std::swap(mas[l], mas[r]);
			l++;
			r--;
		}
	} while (l <= r);
	if (l < last)
		fundsort(mas, l, last);
	if (first < r)
		fundsort(mas, first, r);
	return;
}
