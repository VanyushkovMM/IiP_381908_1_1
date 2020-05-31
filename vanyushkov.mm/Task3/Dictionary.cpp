#include "Dictionary.h"

// Преобразование в строчные буквы слова (sym = 26 - Eng, sym = 32 - Rus)
void check(std::string& str, int sym)
{
	int i = 0;
	char cB = 'А', cS = 'а'; // Русские символы
	if (sym == 26)
	{
		// Английские символы
		cB = 'A';
		cS = 'a';
	}
	while (str[i] != 0)
	{
		if (str[i] >= cB && str[i] < cB + sym)
			str[i] = str[i] - cB + cS;
		// Ё не входит в диапазон А..Я
		if (str[i] == 'Ё')
			str[i] = 'ё';
		i++;
	}
}

// Преобразование в строчные буквы слова и его перевода
void check(std::string& strE, std::string& strR)
{
	check(strE, 26);
	check(strR, 32);
}

// Сравнение двух строк на алфавитный порядок
bool comparison_less(std::string str1, std::string str2)
{
	size_t len = str1.length();
	size_t len1 = str2.length();
	if (len > len1)
		len = len1;
	for (size_t i = 0; i < len; i++)
		if (str1[i] < str2[i])
			return true;
		else
			if (str1[i] > str2[i])
				return false;
	return false; // Если строки равны на длине len
}

// По умолчанию
Words::Words()
{
	english = "";
	ruswords = 0;
	russian = new std::string[MAXRUSW];
}

// Копирование
Words::Words(const Words& word)
{
	*this = word;
}

// Деструктор
Words::~Words()
{
	english = "";
	ruswords = 0;
	delete[] russian;
}

// Присваивание (копирование)
Words& Words::operator=(const Words& word)
{
	english = word.english;
	if (ruswords < 1)
		russian = new std::string[MAXRUSW];
	ruswords = word.ruswords;
	for (int i = 0; i < ruswords; i++)
		russian[i] = word.russian[i];
	return *this;
}

// Слияние переводов слова (исправлено)
Words Words::operator+(const Words& word)
{
	Words result = *this;
	for (int i = 0; i < word.ruswords; i++)
	{
		bool flag = false;
		for (int j = 0; j < result.ruswords && j < MAXRUSW; j++)
			if (word.russian[i] == result.russian[j])
			{
				flag = true;
				break;
			}
		if (!flag)
			result.russian[result.ruswords++] = word.russian[i];
	}
	return result;
}

// Выстроение в алфавитном порядке (вставка слова)
void Dictionary::sort()
{
	int i = words - 1;
	while (i > 0 && comparison_less(dictionary[i].english, dictionary[i - 1].english))
	{
		Words tmp = dictionary[i];
		dictionary[i] = dictionary[i - 1];
		dictionary[--i] = tmp;
	}
}

// Поиск позиции слова в словаре
int Dictionary::searchPosition(const std::string& strE)
{
	int p = -1;
	for (int i = 0; i < words; i++)
		if (strE == dictionary[i].english)
		{
			p = i;
			break;
		}
	return p;
}

// По умолчанию
Dictionary::Dictionary()
{
	dictionary = new Words[MAXWORDS];
	words = 0;
}

// Копирование
Dictionary::Dictionary(const Dictionary& dict)
{
	*this = dict;
}

// Деструктор
Dictionary::~Dictionary()
{
	delete[] dictionary; // Вызывает деструкторы ~Words();
	words = 0;
}

// Присваивание словарей (копирование) (исправлено)
Dictionary& Dictionary::operator= (const Dictionary& dict)
{
	if (dictionary == NULL || words < 0)
		dictionary = new Words[MAXWORDS];
	words = dict.words;
	for (int i = 0; i < words; i++)
		dictionary[i] = dict.dictionary[i];
	return *this;
}

// Добавить слово в словарь (исправлено)
void Dictionary::AddWord(const std::string& strE, const std::string& strR)
{
	std::string strEng = strE;
	std::string strRus = strR;
	check(strEng, strRus);
	int p = this->searchPosition(strE);
	// убран add(std::string& strE, std::string& strR)
	if (p == -1)
	{
		dictionary[words].english = strE;
		dictionary[words].ruswords = 1;
		dictionary[words].russian[0] = strR;
		words++;
		this->sort();
	}
	else
	{
		int n = dictionary[p].ruswords;
		for (int i = 0; i < n; i++)
			if (dictionary[p].russian[i] == strRus)
				return;
		dictionary[p].russian[dictionary[p].ruswords++] = strRus;
	}
}

// Изменить перевод указанного слова (исправлено)
void Dictionary::ChangeWord(const std::string& strE)
{
	std::string strEng = strE;
	int p = searchPosition(strEng);
	if (p != -1)
	{
		int n = dictionary[p].ruswords;
		int x = 1;
		if (n > 1)
		{
			for (int i = 0; i < n; i++)
				std::cout << i + 1 << ") " << dictionary[p].russian[i] << std::endl;
			do
			{
				std::cout << "Введите номер слова, которое хотите заменить: ";
				std::cin >> x;
			} while (x < 1 || x > dictionary[p].ruswords);
		}
		std::string strR;
		std::cout << "Введите новое слово: ";
		std::cin >> strR;
		check(strR, 32);
		dictionary[p].russian[x - 1] = strR;
	}
	else
		std::cout << "Слово для замены не найдено!";
}

// Перевод слова (исправлено)
bool Dictionary::TranslateWord(const std::string& strE, std::string& strR)
{
	std::string strEng = strE;
	check(strEng, 26);
	int p = this->searchPosition(strEng);
	if (p != -1)
	{
		strR = "";
		int n = dictionary[p].ruswords;
		for (int i = 0; i < n - 1; i++)
			strR += dictionary[p].russian[i] + ", ";
		strR += dictionary[p].russian[n - 1];
		return true;
	}
	return false;
}

// Проверить наличие слова
bool Dictionary::CheckWord(const std::string& strE)
{
	return (this->searchPosition(strE) > -1);
}

// Количество слов в словаре
int Dictionary::CountWords()
{
	return words;
}

// Слияние двух словарей
Dictionary Marge(const Dictionary& dict1, const Dictionary& dict2)
{
	Dictionary dict;
	int i = 0, j = 0, k = 0;
	while (i < dict1.words && j < dict2.words)
	{
		if (comparison_less(dict1.dictionary[i].english, dict2.dictionary[j].english))
			dict.dictionary[k++] = dict1.dictionary[i++];
		else
			if (dict1.dictionary[i].english == dict2.dictionary[j].english)
				dict.dictionary[k++] = dict1.dictionary[i++] + dict2.dictionary[j++];
			else
				dict.dictionary[k++] = dict2.dictionary[j++];
	}
	while (i < dict1.words)
		dict.dictionary[k++] = dict1.dictionary[i++];
	while (j < dict2.words)
		dict.dictionary[k++] = dict2.dictionary[j++];
	dict.words = k;
	return dict;
}

// Считывание словаря из файла
void readDict(Dictionary& dict, std::string str)
{
	std::ifstream fin(str);
	fin >> dict.words;
	for (int i = 0; i < dict.words; i++)
	{
		fin >> dict.dictionary[i].english >> dict.dictionary[i].ruswords;
		int n = dict.dictionary[i].ruswords;
		for (int j = 0; j < n; j++)
			fin >> dict.dictionary[i].russian[j];
	}
	fin.close();
}

// Запись словаря в файл
void saveDict(const Dictionary& dict, std::string str)
{
	std::ofstream fout(str);
	fout << dict.words << std::endl;
	for (int i = 0; i < dict.words; i++)
	{
		fout << dict.dictionary[i].english << ' ' << dict.dictionary[i].ruswords << ' ';
		int n = dict.dictionary[i].ruswords;
		for (int j = 0; j < n; j++)
			fout << dict.dictionary[i].russian[j] << ' ';
		fout << std::endl;
	}
	fout.close();
}

// Вывод словаря на консоль
void Dictionary::printDict()
{
	for (int i = 0; i < words; i++)
	{
		std::cout << "    " << dictionary[i].english << " - ";
		int n = dictionary[i].ruswords;
		for (int j = 0; j < n - 1; j++)
			std::cout << dictionary[i].russian[j] << ", ";
		std::cout << dictionary[i].russian[n - 1] << std::endl;
	}
}