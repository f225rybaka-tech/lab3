#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <windows.h>

using namespace std;
class Person {
private:
    string surname;
    string name;
    string patronymic;
    char gender;
    int day, month, year;
public:
    Person() : gender('Ч'), day(1), month(1), year(2000) {}
    void setBirthDate(int d, int m, int y) {
        if (d < 1 || d > 31)
            throw invalid_argument("Невірний день");
        if (m < 1 || m > 12)
            throw invalid_argument("Невірний місяць");
        if (y < 1900 || y > 2025)
            throw out_of_range("Невірний рік");
        day = d;
        month = m;
        year = y;
    }
    void setGender(char g) {
        if (g != 'Ч' && g != 'Ж')
            throw invalid_argument("Стать повинна бути 'Ч' або 'Ж'");
        gender = g;
    }
    friend istream& operator>>(istream& in, Person& p) {
        cout << "Прізвище: ";
        in >> p.surname;
        cout << "Ім’я: ";
        in >> p.name;
        cout << "По батькові: ";
        in >> p.patronymic;
        char g;
        cout << "Стать (Ч/Ж): ";
        in >> g;
        p.setGender(g);  

        int d, m, y;
        cout << "Дата народження (д м р): ";
        in >> d >> m >> y;

        if (in.fail())
            throw runtime_error("Помилка введення числових даних");

        p.setBirthDate(d, m, y);
        return in;
    }
    friend ostream& operator<<(ostream& out, const Person& p) {
        out << "ПІБ: " << p.surname << " " << p.name << " " << p.patronymic << endl;
        out << "Стать: " << p.gender << endl;
        out << "Дата народження: "
            << p.day << "." << p.month << "." << p.year << endl;
        out << "-----------------------------" << endl;
        return out;
    }
    bool bySurname(const string& s) const { return surname == s; }
    bool byName(const string& n) const { return name == n; }
    bool byPatronymic(const string& p) const { return patronymic == p; }
    bool byGender(char g) const { return gender == g; }
    bool byYear(int y) const { return year == y; }
};
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Person> people;
    int choice;
    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Додати особу\n";
        cout << "2. Показати всіх\n";
        cout << "3. Пошук за прізвищем\n";
        cout << "4. Пошук за ім’ям\n";
        cout << "5. Пошук за по батькові\n";
        cout << "6. Пошук за статтю\n";
        cout << "7. Пошук за роком народження\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        try {
            if (choice == 1) {
                Person p;
                cin >> p;
                people.push_back(p);
            }
            else if (choice == 2) {
                for (const auto& p : people)
                    cout << p;
            }
            else if (choice == 3) {
                string s;
                cout << "Прізвище: ";
                cin >> s;
                for (const auto& p : people)
                    if (p.bySurname(s)) cout << p;
            }
            else if (choice == 4) {
                string n;
                cout << "Ім’я: ";
                cin >> n;
                for (const auto& p : people)
                    if (p.byName(n)) cout << p;
            }
            else if (choice == 5) {
                string pat;
                cout << "По батькові: ";
                cin >> pat;
                for (const auto& p : people)
                    if (p.byPatronymic(pat)) cout << p;
            }
            else if (choice == 6) {
                char g;
                cout << "Стать (Ч/Ж): ";
                cin >> g;
                for (const auto& p : people)
                    if (p.byGender(g)) cout << p;
            }
            else if (choice == 7) {
                int y;
                cout << "Рік: ";
                cin >> y;
                if (cin.fail()) throw runtime_error("Рік має бути числом");
                for (const auto& p : people)
                    if (p.byYear(y)) cout << p;
            }
        }
        catch (const invalid_argument& e) {
            cout << "INVALID_ARGUMENT: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "OUT_OF_RANGE: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "RUNTIME_ERROR: " << e.what() << endl;
        }
        catch (...) {
            cout << "Невідома помилка!" << endl;
        }
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 0);
    return 0;
}
