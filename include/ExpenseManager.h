#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <vector>

#include "Expense.h"

using namespace std;

class ExpenseManager {
private:
    vector<Expense> expenses;

public:
    void addExpense(const Expense& expense);
    bool removeExpense(int id);
    void showAll() const;
    double calculateTotal() const;
};

#endif
