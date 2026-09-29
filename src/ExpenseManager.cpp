#include "ExpenseManager.h"

#include <algorithm>
#include <iostream>

void ExpenseManager::addExpense(const Expense& expense) {
    expenses.push_back(expense);
}

bool ExpenseManager::removeExpense(int id) {
    auto it = find_if(expenses.begin(), expenses.end(),
                      [id](const Expense& expense) { return expense.getId() == id; });

    if (it == expenses.end()) {
        return false;
    }

    expenses.erase(it);
    return true;
}

void ExpenseManager::showAll() const {
    if (expenses.empty()) {
        cout << "No expenses found." << endl;
        return;
    }

    for (const Expense& expense : expenses) {
        expense.print();
    }
}

double ExpenseManager::calculateTotal() const {
    double total = 0.0;

    for (const Expense& expense : expenses) {
        total += expense.getAmount();
    }

    return total;
}
