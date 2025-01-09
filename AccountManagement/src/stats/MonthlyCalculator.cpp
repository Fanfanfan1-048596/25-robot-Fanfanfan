#include "stats/MonthlyCalculator.hpp"

void MonthlyCalculator::calculate(const std::vector<Transaction>& transactions,
                                const std::string& start_date,
                                const std::string& end_date) {
    monthly_stats_.clear();
    total_income_ = total_expense_ = balance_ = 0.0;
    
    for (const auto& trans : transactions) {
        if (!isInRange(trans.getDate(), start_date, end_date)) continue;
        
        std::string month = extractMonth(trans.getDate());
        double amount = trans.getAmount();
        monthly_stats_[month] += amount;
        
        if (amount > 0) {
            total_income_ += amount;
        } else {
            total_expense_ += amount;
        }
    }
    balance_ = total_income_ + total_expense_;
}

std::string MonthlyCalculator::extractMonth(const std::string& date) const {
    return date.substr(0, 7); // YYYY-MM
}