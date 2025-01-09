#include "stats/YearlyCalculator.hpp"

void YearlyCalculator::calculate(const std::vector<Transaction>& transactions,
                               const std::string& start_date,
                               const std::string& end_date) {
    yearly_stats_.clear();
    total_income_ = total_expense_ = balance_ = 0.0;
    
    for (const auto& trans : transactions) {
        if (!isInRange(trans.getDate(), start_date, end_date)) continue;
        
        std::string year = extractYear(trans.getDate());
        double amount = trans.getAmount();
        yearly_stats_[year] += amount;
        
        if (amount > 0) {
            total_income_ += amount;
        } else {
            total_expense_ += amount;
        }
    }
    balance_ = total_income_ + total_expense_;
}

std::string YearlyCalculator::extractYear(const std::string& date) const {
    return date.substr(0, 4); // YYYY
}