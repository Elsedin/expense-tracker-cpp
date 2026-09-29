#include "FileManager.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>

#include "DateUtils.h"

static bool parseInt(const string& text, int& value) {
    istringstream stream(text);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

static bool parseDouble(const string& text, double& value) {
    istringstream stream(text);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

static vector<string> splitLine(const string& line, char separator) {
    vector<string> fields;
    istringstream stream(line);
    string field;

    while (getline(stream, field, separator)) {
        fields.push_back(field);
    }

    return fields;
}

bool FileManager::saveExpenses(const vector<Expense>& expenses, const string& filename) const {
    filesystem::path directory = filesystem::path(filename).parent_path();
    if (!directory.empty()) {
        error_code error;
        filesystem::create_directories(directory, error);
    }

    ofstream file(filename);
    if (!file) {
        return false;
    }

    file << fixed << setprecision(2);
    for (const Expense& expense : expenses) {
        file << expense.getId() << '|'
             << expense.getDate() << '|'
             << expense.getCategory() << '|'
             << expense.getDescription() << '|'
             << expense.getAmount() << '\n';
    }

    file.close();
    return !file.fail();
}

vector<Expense> FileManager::loadExpenses(const string& filename) const {
    vector<Expense> expenses;
    set<int> loadedIds;

    ifstream file(filename);
    if (!file) {
        return expenses;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        vector<string> fields = splitLine(line, '|');
        if (fields.size() != 5) {
            continue;
        }

        int id;
        double amount;
        if (!parseInt(fields[0], id) || !parseDouble(fields[4], amount) || amount <= 0) {
            continue;
        }

        if (!isValidDate(fields[1]) || fields[2].empty() || fields[3].empty()) {
            continue;
        }

        if (!loadedIds.insert(id).second) {
            continue;
        }

        expenses.push_back(Expense(id, fields[1], fields[2], fields[3], amount));
    }

    return expenses;
}
