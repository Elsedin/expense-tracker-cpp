#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "DateUtils.h"
#include "Expense.h"
#include "ExpenseManager.h"
#include "FileManager.h"

using namespace std;

#ifdef DATA_FILE_PATH
const string DATA_FILE = DATA_FILE_PATH;
#else
const string DATA_FILE = "data/expenses.txt";
#endif

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

string readTextField(const string& prompt) {
    string text = readNonEmptyLine(prompt);
    while (text.find('|') != string::npos) {
        cout << "This field cannot contain the '|' character." << endl;
        text = readNonEmptyLine(prompt);
    }
    return text;
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
    cout << "5. Search by category" << endl;
    cout << "6. Show category statistics" << endl;
    cout << "0. Exit" << endl;
    cout << endl;
}

void addExpense(ExpenseManager& manager) {
    int id = readInt("ID: ");
    string date = readDate("Date (YYYY-MM-DD): ");
    string category = readTextField("Category: ");
    string description = readTextField("Description: ");
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

void searchByCategory(const ExpenseManager& manager) {
    string category = readNonEmptyLine("Enter category to search: ");
    vector<Expense> matches = manager.searchByCategory(category);

    if (matches.empty()) {
        cout << "No expenses found for this category." << endl;
        return;
    }

    for (const Expense& expense : matches) {
        expense.print();
    }
}

void showCategoryStatistics(const ExpenseManager& manager) {
    map<string, double> totals = manager.calculateCategoryTotals();

    if (totals.empty()) {
        cout << "No expenses found." << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "===== CATEGORY STATISTICS =====" << endl;
    for (const auto& [category, total] : totals) {
        cout << category << ": " << total << " KM" << endl;
    }
    cout << "===============================" << endl;
    cout << "Total: " << manager.calculateTotal() << " KM" << endl;
}

int main() {
    ExpenseManager manager;
    FileManager fileManager;
    manager.setExpenses(fileManager.loadExpenses(DATA_FILE));

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
            case 5:
                searchByCategory(manager);
                break;
            case 6:
                showCategoryStatistics(manager);
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

    if (!fileManager.saveExpenses(manager.getExpenses(), DATA_FILE)) {
        cout << "Failed to save expenses." << endl;
    }

    return 0;
}
