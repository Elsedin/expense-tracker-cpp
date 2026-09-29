# Expense Tracker

A C++17 console application for tracking personal expenses.

## Features

- Add and remove expenses
- Display, search, and filter expenses
- Calculate total spending
- Show spending statistics by category
- Save and load expenses from a file

## Project structure

```
.
├── include/        # Header files (.h)
├── src/            # Source files (.cpp)
├── data/           # Saved expense data files
├── CMakeLists.txt  # CMake build configuration
├── README.md       # Project documentation
└── .gitignore      # Git ignore rules
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/ExpenseTracker
```

With multi-configuration generators such as Visual Studio, the executable is placed in a configuration subfolder, for example `build/Debug/ExpenseTracker.exe`.

## Data storage

Expenses are loaded from the project's `data/expenses.txt` when the application starts and saved back to it on exit. CMake passes this location to the compiler, so the application finds the file regardless of the directory it is started from. The `data/` directory is created automatically if it is missing. If the project is moved to another folder, re-run the CMake configure step.

Each line stores one expense in the format:

```
id|date|category|description|amount
```
