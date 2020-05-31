#include "RailTicketOffice.h"

// ���������� �� ������ � �������������
void info()
{
    std::cout << "    /help - ������\n    /new - �������� ������ ������\n"
        << "    /clear - ������� ������\n    /print - ����� ������\n    /exit - �����\n";
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

int main()
{
	// ���������� ���������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

    RailTicketOffice office;
    Ticket ticket;
    std::string command;

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
        else if (command == "/new")
        {
            office.clearTicket();
            ticket = office.newTicket();
            clrscr();
            if (!(ticket == Ticket()))
                std::cout << "����� �����������!\n";
        }
        else if (command == "/print")
        {
            if (!ticket.Print())
                std::cout << "��� ���������� � �������";
            else
                ticket.saveTicket();
        }
        else
            std::cout << "    ������ ������� ���!\n";
        std::cout << "    ������� �������: ";
        std::cin >> command;
        check(command);
    }
    clrscr();

	return 0;
}