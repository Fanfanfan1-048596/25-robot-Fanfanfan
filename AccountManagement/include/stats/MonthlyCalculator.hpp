#pragma once
#include "StatisticsCalculator.hpp"
#include <map>

class MonthlyCalculator : public StatisticsCalculator {
public:
    void calculate(const std::vector<Transaction>& transactions,
                  const std::string& start_date,
                  const std::string& end_date) override;
    
    const std::map<std::string, double>& getMonthlyStats() const { return monthly_stats_; }

private:
    std::map<std::string, double> monthly_stats_;
    std::string extractMonth(const std::string& date) const;
};