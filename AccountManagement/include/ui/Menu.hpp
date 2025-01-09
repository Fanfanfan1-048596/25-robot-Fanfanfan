#pragma once
#include <memory>
#include <iostream>
#include <limits>
#include "data/AccountBook.hpp"
#include "stats/DailyCalculator.hpp"
#include "stats/MonthlyCalculator.hpp"
#include "stats/YearlyCalculator.hpp"

class Menu {
public:
    Menu();
    void run();

private:
    AccountBook book_;
    void showMainMenu() const;
    void handleInput();
    
    void addTransaction();
    void removeTransaction();
    void modifyTransaction();
    void searchTransactions();
    void showAllTransactions() const;
    void sortTransactions();
    void showStatistics();
    
    static bool isValidDate(const std::string& date);
    static void clearInputBuffer();
    static std::string getValidDate(const std::string& prompt);
};