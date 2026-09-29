#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

#include "Expense.h"

using namespace std;

class FileManager {
public:
    bool saveExpenses(const vector<Expense>& expenses, const string& filename) const;
    vector<Expense> loadExpenses(const string& filename) const;
};

#endif
