#include "FilmLibrary.h"

// ���������� �� ������ � �������������
void info()
{
    std::cout << "    /add - �������� �����\n    /change - �������� ����� �� ��������\n"
        << "    /search - ����� ����� �� �������� � ����\n    /producer - ������ ������ ��������� ��������\n"
        << "    /year - ������ ������ �� ��������� ���\n    /fund - ������ ��������� ���������� ����� �������� �������\n"
        << "    /fundyear - ������ ��������� ���������� ����� �������� ������� �� ��������� ���\n"
        << "    /count - ������ ���������� ������� � ����������\n    /delete - ������� ����� �� ��������\n"
        << "    /print - ������� ���� ������ �������\n    /clear - �������� �����\n    /help - ������\n    /exit - �����\n";
}

// ������� ������
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

// ��������� ������
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

// ������� � ����� ������ (���������� ������)
void bin(std::istream& in)
{
    std::string bin;
    std::getline(in, bin);
}

int main()
{
    // ���������� ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "���������� � ������... ";

    std::string command, filename;
    FilmLibrary library;

    filename = "������.txt";

    ReadFilms(library, filename);

    clrscr();
    std::cout << "/help - ������\n    ������� �������: ";
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
                std::cout << "    ������!\n";
            else
                std::cout << "    ����� ����� ��� ����!\n";
        }
        else if (command == "/change")
        {
            std::string name;
            bin(std::cin);
            std::cout << "������� ��������: ";
            std::getline(std::cin, name);
            if (library.ChangeFilm(name))
                std::cout << "    ������!\n";
            else
                std::cout << "    ����� �� ������!\n";
        }
        else if (command == "/search")
        {
            std::string name;
            int year;
            bin(std::cin);
            std::cout << "������� �������� ������: ";
            std::getline(std::cin, name);
            std::cout << "������� ��� �������� ������: ";
            std::cin >> year;
            if (!library.SearchFilm(name, year).Write())
                std::cout << "����� �� ������!\n";
        }
        else if (command == "/producer")
        {
            std::string producer;
            bin(std::cin);
            std::cout << "������� ���������: ";
            std::getline(std::cin, producer);
            if (!library.ProducerFilms(producer).PrintLibrary())
                std::cout << "������ ������� ��������� �� �������!\n";
        }
        else if (command == "/year")
        {
            int year;
            std::cout << "������� ���: ";
            std::cin >> year;
            if (!library.YearFilms(year).PrintLibrary())
                std::cout << "������� �� ��������� ��� ���!\n";
        }
        else if (command == "/fund")
        {
            int fund;
            std::cout << "������� ���������� �������: ";
            std::cin >> fund;
            if (!library.FundFilms(fund).PrintLibrary())
                std::cout << "    ��� �������!\n";
        }
        else if (command == "/fundyear")
        {
            int year, fund;
            std::cout << "������� ���������� ������� � ���: ";
            std::cin >> fund >> year;
            if (!library.FundYearFilms(fund, year).PrintLibrary())
                std::cout << "������� �� ��������� ��� ���!\n";
        }
        else if (command == "/count")
        {
            std::cout << "���������� �������: " << library.CountFilms() << std::endl;
        }
        else if (command == "/delete")
        {
            std::string name;
            bin(std::cin);
            std::cout << "������� �������� ������: ";
            std::getline(std::cin, name);
            if (library.DeleteFilm(name))
                std::cout << "    ������!\n";
            else
                std::cout << "    ����� ��� �������� �� ������!\n";
        }
        else if (command == "/print")
        {
            if (!library.PrintLibrary())
                std::cout << "    ��� �������!\n";
        }
        else
            std::cout << "    ������ ������� ���!\n";
        std::cout << "    ������� �������: ";
        std::cin >> command;
        check(command);
    }

    clrscr();
    std::cout << "���������� ������...\n";
    SaveFilms(library, filename);

    return 0;
}
