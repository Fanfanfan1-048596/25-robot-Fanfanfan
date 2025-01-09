#include "stats/DailyCalculator.hpp"

void DailyCalculator::calculate(const std::vector<Transaction>& transactions,
                              const std::string& start_date,
                              const std::string& end_date) {
    daily_stats_.clear();
    total_income_ = total_expense_ = balance_ = 0.0;
    
    for (const auto& trans : transactions) {
        if (!isInRange(trans.getDate(), start_date, end_date)) continue;
        
        double amount = trans.getAmount();
        daily_stats_[trans.getDate()] += amount;
        
        if (amount > 0) {
            total_income_ += amount;
        } else {
            total_expense_ += amount;
        }
    }
    balance_ = total_income_ + total_expense_;
}