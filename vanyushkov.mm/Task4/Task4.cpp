#include "FilmLibrary.h"

// Информация по работе с инструментами
void info()
{
    std::cout << "    /add - Добавить фильм\n    /change - изменить фильм по названию\n"
        << "    /search - найти фильм по названию и году\n    /producer - выдать фильмы заданного режиссёра\n"
        << "    /year - выдать фильмы за указанный год\n    /fund - выдать указанное количество самых кассовых фильмов\n"
        << "    /fundyear - выдать указанное количество самых кассовых фильмов за указанный год\n"
        << "    /count - выдать количество фильмов в библиотеке\n    /delete - удалить фильм по названию\n"
        << "    /print - вывести весь список фильмов\n    /clear - очистить экран\n    /help - помощь\n    /exit - выход\n";
}

// Очистка экрана
void clrscr()
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int col = Attr;
    int width = buf.dwSize.X;
    int height = buf.dwSize.Y;

    COORD zpos;
    zpos.X = 0;
    zpos.Y = 0;
    SetConsoleCursorPosition(Console, zpos);

    FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
    FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

// Обработка команд
void check(std::string& str)
{
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
        i++;
    }
}

// Переход в новую строку (считывание мусора)
void bin(std::istream& in)
{
    std::string bin;
    std::getline(in, bin);
}

int main()
{
    // Добавление кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Подготовка к работе... ";

    std::string command, filename;
    FilmLibrary library;

    filename = "Фильмы.txt";

    ReadFilms(library, filename);

    clrscr();
    std::cout << "/help - помощь\n    Введите команду: ";
    std::cin >> command;
    check(command);
    while (command != "/exit")
    {
        if (command == "/help")
            info();
        else if (command == "/clear")
            clrscr();
        else if (command == "/add")
        {
            if (library.AddFilm())
                std::cout << "    Готово!\n";
            else
                std::cout << "    Такой фильм уже есть!\n";
        }
        else if (command == "/change")
        {
            std::string name;
            bin(std::cin);
            std::cout << "Введите название: ";
            std::getline(std::cin, name);
            if (library.ChangeFilm(name))
                std::cout << "    Готово!\n";
            else
                std::cout << "    Фильм не найден!\n";
        }
        else if (command == "/search")
        {
            std::string name;
            int year;
            bin(std::cin);
            std::cout << "Введите название фильма: ";
            std::getline(std::cin, name);
            std::cout << "Введите год премьеры фильма: ";
            std::cin >> year;
            if (!library.SearchFilm(name, year).Write())
                std::cout << "Фильм не найден!\n";
        }
        else if (command == "/producer")
        {
            std::string producer;
            bin(std::cin);
            std::cout << "Введите режиссера: ";
            std::getline(std::cin, producer);
            if (!library.ProducerFilms(producer).PrintLibrary())
                std::cout << "Фильмы данного режиссера не найдены!\n";
        }
        else if (command == "/year")
        {
            int year;
            std::cout << "Введите год: ";
            std::cin >> year;
            if (!library.YearFilms(year).PrintLibrary())
                std::cout << "Фильмов за указанный год нет!\n";
        }
        else if (command == "/fund")
        {
            int fund;
            std::cout << "Введите количество фильмов: ";
            std::cin >> fund;
            if (!library.FundFilms(fund).PrintLibrary())
                std::cout << "    Нет фильмов!\n";
        }
        else if (command == "/fundyear")
        {
            int year, fund;
            std::cout << "Введите количество фильмов и год: ";
            std::cin >> fund >> year;
            if (!library.FundYearFilms(fund, year).PrintLibrary())
                std::cout << "Фильмов за указанный год нет!\n";
        }
        else if (command == "/count")
        {
            std::cout << "Количество фильмов: " << library.CountFilms() << std::endl;
        }
        else if (command == "/delete")
        {
            std::string name;
            bin(std::cin);
            std::cout << "Введите название фильма: ";
            std::getline(std::cin, name);
            if (library.DeleteFilm(name))
                std::cout << "    Готово!\n";
            else
                std::cout << "    Фильм для удаления не найден!\n";
        }
        else if (command == "/print")
        {
            if (!library.PrintLibrary())
                std::cout << "    Нет фильмов!\n";
        }
        else
            std::cout << "    Данной команды нет!\n";
        std::cout << "    Введите команду: ";
        std::cin >> command;
        check(command);
    }

    clrscr();
    std::cout << "Завершение работы...\n";
    SaveFilms(library, filename);

    return 0;
}
