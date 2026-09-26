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

Run the executable from the `build` directory after a successful build.
