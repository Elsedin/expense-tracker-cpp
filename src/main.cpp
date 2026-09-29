#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Expense.h"
#include "ExpenseManager.h"

using namespace std;

string readLine(const string& prompt) {
    cout << prompt;

    string line;
    if (!getline(cin, line)) {
        cout << endl << "Input closed. Exiting." << endl;
        exit(0);
    }

    return line;
}

bool parseInt(const string& text, int& value) {
    istringstream stream(text);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

bool parseDouble(const string& text, double& value) {
    istringstream stream(text);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

int readInt(const string& prompt) {
    int value;
    while (!parseInt(readLine(prompt), value)) {
        cout << "Please enter a whole number." << endl;
    }
    return value;
}

double readAmount(const string& prompt) {
    double value;
    while (!parseDouble(readLine(prompt), value) || value <= 0) {
        cout << "Please enter a positive number." << endl;
    }
    return value;
}

string readNonEmptyLine(const string& prompt) {
    string line = readLine(prompt);
    while (line.empty()) {
        cout << "This field cannot be empty." << endl;
        line = readLine(prompt);
    }
    return line;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int year, int month) {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12) {
        return false;
    }

    return day >= 1 && day <= daysInMonth(year, month);
}

string readDate(const string& prompt) {
    string date = readLine(prompt);
    while (!isValidDate(date)) {
        cout << "Invalid date. Please use YYYY-MM-DD." << endl;
        date = readLine(prompt);
    }
    return date;
}

void showMenu() {
    cout << endl;
    cout << "================================" << endl;
    cout << "         EXPENSE TRACKER" << endl;
    cout << "================================" << endl;
    cout << endl;
    cout << "1. Add expense" << endl;
    cout << "2. Remove expense" << endl;
    cout << "3. Show all expenses" << endl;
    cout << "4. Calculate total" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
}

void addExpense(ExpenseManager& manager) {
    int id = readInt("ID: ");
    string date = readDate("Date (YYYY-MM-DD): ");
    string category = readNonEmptyLine("Category: ");
    string description = readNonEmptyLine("Description: ");
    double amount = readAmount("Amount: ");

    while (!manager.addExpense(Expense(id, date, category, description, amount))) {
        cout << "An expense with this ID already exists. Please use a different ID." << endl;
        id = readInt("ID: ");
    }

    cout << "Expense added successfully." << endl;
}

void removeExpense(ExpenseManager& manager) {
    int id = readInt("Enter the ID of the expense to remove: ");

    if (manager.removeExpense(id)) {
        cout << "Expense removed successfully." << endl;
    } else {
        cout << "Expense not found." << endl;
    }
}

void showTotal(const ExpenseManager& manager) {
    cout << fixed << setprecision(2);
    cout << "Total: " << manager.calculateTotal() << " KM" << endl;
}

int main() {
    ExpenseManager manager;
    bool running = true;

    while (running) {
        showMenu();

        int choice;
        if (!parseInt(readLine("Choose an option: "), choice)) {
            choice = -1;
        }

        cout << endl;

        switch (choice) {
            case 1:
                addExpense(manager);
                break;
            case 2:
                removeExpense(manager);
                break;
            case 3:
                manager.showAll();
                break;
            case 4:
                showTotal(manager);
                break;
            case 0:
                cout << "Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}
