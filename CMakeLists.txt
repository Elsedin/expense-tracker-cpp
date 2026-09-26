cmake_minimum_required(VERSION 3.16)
project(ExpenseTracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(ExpenseTracker
    src/main.cpp
    src/Expense.cpp
)
