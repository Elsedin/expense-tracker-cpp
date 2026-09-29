#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <string>
#include <vector>

#include "Expense.h"

using namespace std;

class ExpenseManager {
private:
    vector<Expense> expenses;

public:
    bool addExpense(const Expense& expense);
    bool removeExpense(int id);
    void showAll() const;
    double calculateTotal() const;
    vector<Expense> searchByCategory(const string& category) const;
};

#endif
