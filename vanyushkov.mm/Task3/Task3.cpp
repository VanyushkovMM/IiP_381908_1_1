#include "Dictionary.h"

// Информация по работе с инструментами
void info()
{
    std::cout << "    /add - добавление слова и перевода\n    /change - изменение перевода слова\n";
    std::cout << "    /translate - перевод слова\n    /check - проверка наличия слова в словаре\n";
    std::cout << "    /count - количество слов в словаре\n    /marge - слияние двух словарей\n";
    std::cout << "    /print - вывод словаря на консоль\n    /clear - очистка экрана\n";
    std::cout << "    /help - помощь\n    /exit - выход\n";
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

int main()
{
    // Добавление кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Подготовка к работе... ";

    std::string command, filename1, filename2;
    Dictionary dict1, dict2;
    filename1 = "Словарь1.txt";
    filename2 = "Словарь2.txt";

    readDict(dict1, filename1);
    readDict(dict2, filename2);

    clrscr();
    std::cout << "/help - помощь\nВведите команду: ";
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
            std::string strEng, strRus;
            std::cout << "    Введите слово и его перевод: ";
            std::cin >> strEng >> strRus;
            dict1.AddWord(strEng, strRus);
            std::cout << "    Готово!\n";
        }
        else if (command == "/change")
        {
            std::string strEng;
            std::cout << "    Введите слово: ";
            std::cin >> strEng;
            dict1.ChangeWord(strEng);
            std::cout << "    Готово!\n";
        }
        else if (command == "/translate")
        {
            std::string strEng, strRus;
            std::cout << "    Введите слово для поиска перевода: ";
            std::cin >> strEng;
            if (dict1.TranslateWord(strEng, strRus))
                std::cout << "    Перевод: " << strRus << std::endl;
            else
                std::cout << "    Слово не найдено!\n";
        }
        else if (command == "/check")
        {
            std::string strEng;
            std::cout << "    Введите слово: ";
            std::cin >> strEng;
            if (dict1.CheckWord(strEng))
                std::cout << "    Слово есть в словаре\n";
            else
                std::cout << "    Данного слова нет!\n";
        }
        else if (command == "/count")
            std::cout << "    Количестов слов: " << dict1.CountWords() << std::endl;
        else if (command == "/marge")
        {
            std::cout << "    Слияние... ";
            dict2 = Marge(dict1, dict2);
            std::cout << "Готово!\n";
        }
        else if (command == "/print")
            dict1.printDict();
        else
            std::cout << "Данной команды нет!\n";

        std::cout << "Введите команду: ";
        std::cin >> command;
        check(command);
    }


    clrscr();
    std::cout << "Завершение работы...\n";
    saveDict(dict1, filename1);
    saveDict(dict2, filename2);

    return 0;
}