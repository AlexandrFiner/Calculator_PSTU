#include <iostream>
using namespace std;

class Team
{
private:        // атрибуты
    int *number; // номер команды
    char* str;  // имя команды
public:
    Team(); // конструктор по умолчанию
    Team(int x, char s[]); // конструктиор с параметрами
    Team(const Team &obj); // конструктор копий
    ~Team();

    void show(); // метод вывода
    void enter(); // метод ввода информации
};

Team::Team() // конструктор по умолчанию
{
    number = new int; // выделяем память
    *number = 0;      // присваиванем ноль
    str = new char[100]; // выделяем память
    strcpy(str, " ");    // с помощью функции копируем в str пустую строку
}

Team::Team(int x, char s[]) // конструктор с параметрами
{
    number = new int;
    *number = x;
    str = new char[100];
    strcpy(str, s);
}

Team::Team(const Team &obj) // конструктор копии
{
    number = new int;
    *number = *obj.number; // присваиваем значение одного объекта другому
    str = new char[100];
    strcpy(str, obj.str);
}

void Team::enter() // метод ввода информации
{
    cout << "Inter a number team " << endl;
    cin >> *number;
    cout << "Inter a name team " << endl;
    cin >> str;
}

void Team::show() // метод вывода информации
{
    cout << "Name " << str << endl;
    cout << "Number " << *number << endl;
}

Team::~Team() // деструктор
{
    cout << "Object destroy " << endl;
}


int main()
{
    Team t1; // создание объекта без параметров
    t1.enter(); // дальнейшие заполнение полей
    Team t2(2, "Real"); // создание с вызовом конструктора с параметрами
    Team t3(t2); // создание копии на основе имеющегося

    cout << "Object 1) "; // вывод объектов
    t1.show();

    cout << "Object 2) ";
    t2.show();

    cout << "Object 3) ";
    t3.show();

    cout << endl;
}