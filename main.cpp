#include <windows.h> // SetConsoleCP, SetConsoleOutputCP
#include <iostream>
#include <conio.h> // getch
#include <fstream> // ifstream
#include <regex> // regex, regex_match
#include <string>

enum keys { ESC = 27, UP = 72, DOWN = 80, ENTER = 13 };

const std::string LOGIN_PASS_FILE = "files/input/input.txt";
const std::string CODEWORD_FILE = "files/input/codeword.txt";

struct Inital {
    std::string name, surname, patronymic;
    std::string group;
    std::string phoneNumber;
};

struct Date {
    int day, month, year;
};

struct Data {
    Inital _inital;
    Date _date;
};

bool validatePhoneNumber(std::string phoneNumber);
void DataEntry(Data* (&d), int& n);
void DataReading(Data* (&d), int& n, std::string fileName);
void DataOutput(Data* d, int& n);
void DataChange(Data* (&d), int& n);
void Copy(Data* (&d_n), Data* (&d_o), int n);
void DeleteData(Data* (&d), int& n);
void SaveData(Data* (&d), int& n, std::string fileName);
void GoToXY(short width, short height);
void ConsoleCursorVisible(bool show, short size);
void StartMenu();

std::string Encryption(std::string input);
bool IsGood(const std::string& LOGIN, const std::string& PASS);
void Registration();
bool Entrance();
void RestoreData();
void MenuAuthorization();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MenuAuthorization();

    return 0;
}

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoToXY(short width, short height) {
    SetConsoleCursorPosition(hStdOut, {width, height});
}

void ConsoleCursorVisible(bool show, short size) {
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // change cursor visibility
    structCursorInfo.dwSize = size; // resizable cursor
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

bool validatePhoneNumber(std::string phoneNumber) {
    std::regex regexPattern("\\d{3}-\\d{3}-\\d{4}");
    if (std::regex_match(phoneNumber, regexPattern)) return true;
    else return false;
}

void DataEntry(Data* (&d), int& n) {
    do {
        std::cout << "Enter quantity of data: "; std::cin >> n;
        system("cls");
        if (n <= 0) {
            std::cout << "+-----------------MISTAKE----------------+\n";
            std::cout << "You entered incorrect data, please repeat.\n";
            std::cout << "+----------------------------------------+\n";
            system("pause");
            system("cls");
        }
    } while (n <= 0);

    d = new Data[n];

    for (int i = 0; i < n; i++) {
        std::cout << "Enter student's full nam: ";
        std::cin >> d[i]._inital.name;
        std::cin >> d[i]._inital.surname;
        std::cin >> d[i]._inital.patronymic;

        std::cout << "What group is the student in?: ";
        std::cin >> d[i]._inital.group;

        Stop:
            std::cout << "Enter the student's phone number in the format XXX-XXX-XXXX: ";
            std::cin >> d[i]._inital.phoneNumber;
            system("cls");
            if (!validatePhoneNumber(d[i]._inital.phoneNumber)) {
                std::cout << "+-----------------MISTAKE---------------+\n";
                std::cout << "The phone number was entered incorrectly.\n";
                std::cout << "+---------------------------------------+\n";
                system("pause");
                system("cls");
                goto Stop;
            }

        do {
            std::cout << "Enter DD.MM.YYYY of the student's birth: ";
            std::cin >> d[i]._date.day;
            std::cin >> d[i]._date.month;
            std::cin >> d[i]._date.year;
            system("cls");

            if (d[i]._date.day <= 0 || d[i]._date.day > 31 ||
                d[i]._date.month <= 0 || d[i]._date.month > 12 || d[i]._date.year < 1999) {
                std::cout << "+-----------------MISTAKE----------------+\n";
                std::cout << "You entered incorrect data, please repeat.\n";
                std::cout << "+----------------------------------------+\n";
                system("pause");
                system("cls");
            }
        } while (d[i]._date.day <= 0 || d[i]._date.day > 31 ||
                 d[i]._date.month <= 0 || d[i]._date.month > 12 || d[i]._date.year < 1999);
    }
    system("cls");
    std::cout << "Data added successfully!\n";
    system("pause");
    system("cls");
}

void DataReading(Data* (&d), int& n, std::string fileName) {
    std::ifstream reading(fileName);
    if (reading) {
        reading >> n;

        d = new Data[n];

        for (int i = 0; i < n; i++) {
            reading >> d[i]._inital.name;
            reading >> d[i]._inital.surname;
            reading >> d[i]._inital.patronymic;

            reading >> d[i]._inital.group;

            reading >> d[i]._inital.phoneNumber;
            if (!validatePhoneNumber(d[i]._inital.phoneNumber)) {
                std::cout << "+-----------------WARNING---------------+\n";
                std::cout << "The phone number was entered incorrectly.\n";
                std::cout << "+---------------------------------------+\n";
                system("pause");
                system("cls");
            }

            reading >> d[i]._date.day;
            reading >> d[i]._date.month;
            reading >> d[i]._date.year;
            if (d[i]._date.day <= 0 || d[i]._date.day > 31 ||
                d[i]._date.month <= 0 || d[i]._date.month > 12 || d[i]._date.year <= 1999) {
                std::cout << "+-----------------WARNING----------------+\n";
                std::cout << "You entered incorrect data, please repeat.\n";
                std::cout << "+----------------------------------------+\n";
                system("pause");
                system("cls");
            }
        }
        std::cout << "Data added!\n";
    } else {
        std::cout << "+-----------------------MISTAKE----------------------+\n";
        std::cout << "Error when trying to open a file (" << fileName << ").\n";
        std::cout << "+----------------------------------------------------+\n";
        system("pause");
        system("cls");
    }
    reading.close();
}

void DataOutput(Data* d, int& n) {
    std::cout << "Number of data: " << n << std::endl << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Information about ¹" << i + 1 << std::endl;
        std::cout << "Student's full name: " << d[i]._inital.name << " " << d[i]._inital.surname << " " << d[i]._inital.patronymic << std::endl;
        std::cout << "Group: " << d[i]._inital.group << std::endl;
        std::cout << "Phone number: +7-" << d[i]._inital.phoneNumber << std::endl;
        std::cout << "DD.MM.YYYY of student's birth: " << d[i]._date.day << "." << d[i]._date.month << "." << d[i]._date.year << std::endl;
    }
    system("pause");
    system("cls");
}

void DataChange(Data* (&d), int& n) {
    int _n;
    std::cout << "Enter the number of the element to be changed (from 1 to " << n << "): "; std::cin >> _n;
    _n--;

    system("cls");

    if (_n >= 0 && _n < n) {
        std::cout << "Enter student's full nam: ";
        std::cin >> d[_n]._inital.name;
        std::cin >> d[_n]._inital.surname;
        std::cin >> d[_n]._inital.patronymic;

        std::cout << "What group is the student in?: ";
        std::cin >> d[_n]._inital.group;

        Stop:
            std::cout << "Enter the student's phone number in the format XXX-XXX-XXXX: ";
            std::cin >> d[_n]._inital.phoneNumber;
            system("cls");
            if (!validatePhoneNumber(d[_n]._inital.phoneNumber)) {
                std::cout << "+-----------------MISTAKE---------------+\n";
                std::cout << "The phone number was entered incorrectly.\n";
                std::cout << "+---------------------------------------+\n";
                system("pause");
                system("cls");
                goto Stop;
            }

        do {
            std::cout << "Enter DD.MM.YYYY of the student's birth: ";
            std::cin >> d[_n]._date.day;
            std::cin >> d[_n]._date.month;
            std::cin >> d[_n]._date.year;
            system("cls");

            if (d[_n]._date.day <= 0 || d[_n]._date.day > 31 ||
                d[_n]._date.month <= 0 || d[_n]._date.month > 12 || d[_n]._date.year < 1999) {
                std::cout << "+-----------------MISTAKE----------------+\n";
                std::cout << "You entered incorrect data, please repeat.\n";
                std::cout << "+----------------------------------------+\n";
                system("pause");
                system("cls");
            }
        } while (d[_n]._date.day <= 0 || d[_n]._date.day > 31 ||
                 d[_n]._date.month <= 0 || d[_n]._date.month > 12 || d[_n]._date.year < 1999);

        std::cout << "Data changed!\n";
        system("pause");
        system("cls");
    } else {
        std::cout << "+--------WARNING-------+\n";
        std::cout << "The number is incorrect.\n";
        std::cout << "+----------------------+\n";
        system("pause");
        system("cls");
    }
}

void Copy(Data* (&d_n), Data* (&d_o), int n) {
    for (int i = 0; i < n; i++) {
        d_n[i] = d_o[i];
    }
}

void DeleteData(Data* (&d), int& n) {
    int _n;
    std::cout << "Enter the number of the element to be changed (from 1 to " << n << "): "; std::cin >> _n;
    _n--;

    system("cls");

    if (_n >= 0 && _n < n) {
        Data* buf = new Data[n];

        Copy(buf, d, n);
        --n;

        d = new Data[n];
        int q = 0;
        for (int i = 0; i <= n; i++) {
            if (i != _n) {
                d[q] = buf[i];
                ++q;
            }
        }

        delete[]buf;

        std::cout << "Data deleted!\n";
        system("pause");
        system("cls");
    } else {
        std::cout << "+--------WARNING-------+\n";
        std::cout << "The number is incorrect.\n";
        std::cout << "+----------------------+\n";
        system("pause");
        system("cls");
    }
}

void SaveData(Data* (&d), int& n, std::string fileName) {
    std::ofstream record(fileName, std::ios::out);

    if (record) {
        record << n << std::endl;

        for (int i = 0; i < n; i++) {
            record << d[i]._inital.name << std::endl;
            record << d[i]._inital.surname << std::endl;
            record << d[i]._inital.patronymic << std::endl;

            record << d[i]._inital.group << std::endl;

            record << d[i]._inital.phoneNumber << std::endl;
            if (!validatePhoneNumber(d[i]._inital.phoneNumber)) {
                std::cout << "+-----------------WARNING---------------+\n";
                std::cout << "The phone number was entered incorrectly.\n";
                std::cout << "+---------------------------------------+\n";
                system("pause");
                system("cls");
            }

            record << d[i]._date.day << std::endl;
            record << d[i]._date.month << std::endl;
            record << d[i]._date.year << std::endl;
            if (d[i]._date.day <= 0 || d[i]._date.day > 31 ||
                d[i]._date.month <= 0 || d[i]._date.month > 12 || d[i]._date.year <= 1999) {
                std::cout << "+-----------------WARNING----------------+\n";
                std::cout << "You entered incorrect data, please repeat.\n";
                std::cout << "+----------------------------------------+\n";
                system("pause");
                system("cls");
            }
        }
        std::cout << "Data saved!\n";
        system("pause");
        system("cls");
    } else {
        std::cout << "+----------------------WARNING-----------------------+\n";
        std::cout << "Error when trying to open a file (" << fileName << ").\n";
        std::cout << "+----------------------------------------------------+\n";
        system("pause");
        system("cls");
    }
}

void StartMenu() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string Menu[]{ "Data input", "Data output", "Changing data", "Deleting data", "Saving data", "Eixt" };
    int activeMenu = 0;
    int amountOfData = 0;
    char ch;

    Data* d = new Data[amountOfData];

    while (1) {
        ConsoleCursorVisible(false, 100);
        int x = 50, y = 13;
        GoToXY(x, y);
        for (int i = 0; i < (sizeof(Menu) / sizeof(*Menu)); i++) {
            if (i == activeMenu) SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            else SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            GoToXY(x, y++);
            std::cout << Menu[i] << std::endl;
        }

        ch = getch();
        switch (ch)
        {
        case ESC:
            exit(0);
            break;
        ////////////
        case UP:
            if (activeMenu > 0) --activeMenu;
            break;
        ////////////
        case DOWN:
            if (activeMenu < (sizeof(Menu) / sizeof(*Menu)) - 1) ++activeMenu;
            break;
        ////////////
        case ENTER:
            system("cls");
            ConsoleCursorVisible(true, 100);
            switch (activeMenu)
            {
            case 0:
                int action;
                Stop:
                    std::cout << "+---------- MENU ----------+\n"
                              << "(0) Return\n"
                              << "(1) Manual data entry\n"
                              << "(2) Reading data from a file\n"
                              << "+--------------------------+\n"
                              << "Your choice: "; std::cin >> action;
                    system("cls");
                    if (action < 0 || action > 2) {
                        std::cout << "+-----------------MISTAKE----------------+\n";
                        std::cout << "You entered incorrect data, please repeat.\n";
                        std::cout << "+----------------------------------------+\n";
                        system("pause");
                        system("cls");
                        goto Stop;
                    }
                        if (action == 1) DataEntry(d, amountOfData);
                            if (action == 2) {
                                std::string fileName;
                                std::cout << "Enter the full path to the file: "; std::cin >> fileName;
                                system("cls");
                                DataReading(d, amountOfData, fileName);
                            }
                break;
            ////////////
            case 1:
                if (amountOfData != 0) {
                    DataOutput(d, amountOfData);
                } else {
                    std::cout << "+--- WARNING ---+\n";
                    std::cout << "Data is empty.\n";
                    std::cout << "+---------------+\n";
                    system("pause");
                    system("cls");
                }
                break;
            ////////////
            case 2:
                if (amountOfData != 0) {
                    DataChange(d, amountOfData);
                } else {
                    std::cout << "+--- WARNING ---+\n";
                    std::cout << "Data is empty.\n";
                    std::cout << "+---------------+\n";
                    system("pause");
                    system("cls");
                }
                break;
            ////////////
            case 3:
                if (amountOfData != 0) {
                    DeleteData(d, amountOfData);
                } else {
                    std::cout << "+--- WARNING ---+\n";
                    std::cout << "Data is empty.\n";
                    std::cout << "+---------------+\n";
                    system("pause");
                    system("cls");
                }
                break;
            ////////////
            case 4:
                if (amountOfData != 0) {
                    std::string fileName;
                    std::cout << "Come up with a name for the file (test.txt): "; std::cin >> fileName;
                    system("cls");
                    SaveData(d, amountOfData, fileName);
                } else {
                    std::cout << "+--- WARNING ---+\n";
                    std::cout << "Data is empty.\n";
                    std::cout << "+---------------+\n";
                    system("pause");
                    system("cls");
                }
                break;
            ////////////
            case 5:
                exit(0);
                break;
            ////////////
            }
            break;
        }
    }
}

std::string Encryption(std::string input) {
    std::vector<char> word(input.begin(), input.end());
    std::string alphabet = "ZzYyXxWwVvUuTtSsRrQqPpOoNnMmLlKkJjIiHhGgFfEeDdCcBbAa";
    for (int i = 0; i < (int)input.length(); i++) {
        for (int j = 0; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet[j]) {
                word[i] = alphabet[(j+3) % 52];
                break;
            }
        }
    }
    std::string str(word.begin(), word.end());
    return str;
}

bool IsGood(const std::string& LOGIN, const std::string& PASS) {
    if (LOGIN.size() < 8) {
        std::cout << "+-------------------ERROR-------------------+\n";
        std::cout << "The login must contain at least 8 characters.\n";
        std::cout << "+-------------------------------------------+\n";
        return false;
    }
        if (PASS.size() < 8) {
            std::cout << "+---------------------ERROR--------------------+\n";
            std::cout << "The password must contain at least 8 characters.\n";
            std::cout << "+----------------------------------------------+\n";
            return false;
        }

    int upper = 0, lower = 0, digit = 0, other = 0;
    for (auto it : LOGIN) {
        if ('A' <= it && it <= 'Z') upper = 1;
        else if ('a' <= it && it <= 'z') lower = 1;
        else if ('0' <= it && it <= '9') digit = 1;
        else other = 1;
    }
    return upper + lower + digit + other >= 3;
}

void Registration() {
    std::string login, pass, codeword;

    std::ifstream read(LOGIN_PASS_FILE);
    getline(read, login);

    if (login == "") {
        std::cout << "+--- REGISTRATION ---+\n";
        std::cout << "Create a username: "; std::cin >> login;
        std::cout << "Create a password: "; std::cin >> pass;
        std::cout << "Come up with a code word: "; std::cin >> codeword;
        system("cls");
        if (IsGood(login, pass)) {
            login = Encryption(login);
            pass = Encryption(pass);
            codeword = Encryption(codeword);

            std::ofstream file;
            file.open(LOGIN_PASS_FILE);
            file << login << std::endl << pass;
            file.close();

            file.open(CODEWORD_FILE);
            file << codeword;
            file.close();

            std::cout << "Registration completed successfully!\n";
            system("pause");
            system("cls");
        } else {
            system("pause");
            system("cls");
        }
    } else {
        std::cout << "+----------MISTAKE---------+\n";
        std::cout << "You already have an account!\n";
        std::cout << "+--------------------------+\n";
        system("pause");
        system("cls");
    }
    read.close();
}

bool Entrance() {
    std::ifstream read(LOGIN_PASS_FILE);
    if (!read) {
        std::cout << "+------------------------ERROR--------------------------+\n";
        std::cout << "Error when trying to open a file (files/input/input.txt).\n";
        std::cout << "+-------------------------------------------------------+\n";
        system("pause");
        system("cls");
    } else {
        std::string login, pass;

        std::cout << "+--- ENTRANCE ---+\n";
        std::cout << "Enter login: "; std::cin >> login;
        std::cout << "Enter pass: "; std::cin >> pass;
        system("cls");

        login = Encryption(login);
        pass = Encryption(pass);

        std::string lg, pw;
        std::ifstream reading(LOGIN_PASS_FILE);
        getline(reading, lg);
        getline(reading, pw);

        if (lg == login && pw == pass) {
            std::cout << "Welcome!\n";
            return true;
        } else {
            std::cout << "+--------ERROR---------+\n";
            std::cout << "Wrong login or password.\n";
            std::cout << "+----------------------+\n";
            system("pause");
            system("cls");
        }
    }
    read.close();
}

void RestoreData() {
    std::ifstream read(CODEWORD_FILE);
    if (!read) {
        std::cout << "+-------------------------ERROR----------------------------+\n";
        std::cout << "Error when trying to open a file (files/input/codeword.txt).\n";
        std::cout << "+----------------------------------------------------------+\n";
        system("pause");
        system("cls");
    } else {
        std::string codeword;
        std::cout << "+--- DATA RECOVERY ---+\n";
        std::cout << "Enter code word: "; std::cin >> codeword;
        system("cls");

        codeword = Encryption(codeword);

        std::string cd;
        std::ifstream reading(CODEWORD_FILE);
        getline(reading, cd);

        if (cd == codeword) {
            std::string login, pass;

            std::cout << "Create a new login: "; std::cin >> login;
            std::cout << "Create a new password: "; std::cin >> pass;
            system("cls");

            login = Encryption(login);
            pass = Encryption(pass);

            std::string lg, pw;
            std::ifstream reading_1(LOGIN_PASS_FILE);
            getline(reading_1, lg);
            getline(reading_1, pw);

            if (lg == login && pw == pass) {
                std::cout << "+--------------------WARNING------------------+\n";
                std::cout << "The old login or password must not be the same.\n";
                std::cout << "+---------------------------------------------+\n";
                system("pause");
                system("cls");
            } else {
                if (IsGood(login, pass)) {
                    std::ofstream file(LOGIN_PASS_FILE);
                    file << login << std::endl << pass;
                    file.close();

                    std::cout << "Login or password has been successfully changed.\n";
                    system("pause");
                    system("cls");
                } else {
                    system("pause");
                    system("cls");
                }
            }
            reading_1.close();
        } else {
            std::cout << "+-----ERROR------+\n";
            std::cout << "Invalid code word!\n";
            std::cout << "+----------------+\n";
            system("pause");
            system("cls");
        }
    }
    read.close();
}

void MenuAuthorization() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string Menu[]{ "Entrance", "Registration", "Data recovery", "Eixt" };
    int activeMenu = 0;
    char ch;

    while (1) {
        ConsoleCursorVisible(false, 100);
        int x = 50, y = 13;
        GoToXY(x, y);
        for (int i = 0; i < (sizeof(Menu) / sizeof(*Menu)); i++) {
            if (i == activeMenu) SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
            else SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            GoToXY(x, y++);
            std::cout << Menu[i] << std::endl;
        }

        ch = getch();
        switch (ch)
        {
        case ESC:
            exit(0);
            break;
        ////////////
        case UP:
            if (activeMenu > 0) --activeMenu;
            break;
        ////////////
        case DOWN:
            if (activeMenu < (sizeof(Menu) / sizeof(*Menu)) - 1) ++activeMenu;
            break;
        ////////////
        case ENTER:
            system("cls");
            ConsoleCursorVisible(true, 100);
            switch (activeMenu)
            {
            case 0:
                if (!Entrance()) {
                    continue;
                } else {
                    StartMenu();
                }
                break;
            ////////////
            case 1:
                Registration();
                break;
            ////////////
            case 2:
                RestoreData();
                break;
            ////////////
            case 3:
                exit(0);
                break;
            }
            break;
        }
    }
}
