#include "Expense.h"

#include <iomanip>
#include <iostream>

Expense::Expense(int id, const string& date, const string& category,
                 const string& description, double amount)
    : id(id),
      date(date),
      category(category),
      description(description),
      amount(amount) {}

int Expense::getId() const {
    return id;
}

string Expense::getDate() const {
    return date;
}

string Expense::getCategory() const {
    return category;
}

string Expense::getDescription() const {
    return description;
}

double Expense::getAmount() const {
    return amount;
}

void Expense::print() const {
    cout << fixed << setprecision(2);
    cout << "[" << id << "] " << date << " | " << category << " | "
         << description << " | " << amount << " KM" << endl;
}
