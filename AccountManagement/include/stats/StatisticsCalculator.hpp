#pragma once
#include <vector>
#include <string>
#include "core/Transaction.hpp"

class StatisticsCalculator {
public:
    virtual ~StatisticsCalculator() = default;
    virtual void calculate(const std::vector<Transaction>& transactions,
                         const std::string& start_date,
                         const std::string& end_date) = 0;
    
    double getTotalIncome() const { return total_income_; }
    double getTotalExpense() const { return total_expense_; }
    double getBalance() const { return balance_; }
    
protected:
    double total_income_{0.0};
    double total_expense_{0.0};
    double balance_{0.0};
    
    bool isInRange(const std::string& date,
                  const std::string& start,
                  const std::string& end) const;
};