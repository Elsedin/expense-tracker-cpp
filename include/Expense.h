#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

using namespace std;

class Expense {
private:
    int id;
    string date;
    string category;
    string description;
    double amount;

public:
    Expense(int id, const string& date, const string& category,
            const string& description, double amount);

    int getId() const;
    string getDate() const;
    string getCategory() const;
    string getDescription() const;
    double getAmount() const;

    void print() const;
};

#endif
