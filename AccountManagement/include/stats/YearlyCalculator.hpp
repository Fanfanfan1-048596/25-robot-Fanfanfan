#pragma once
#include "StatisticsCalculator.hpp"
#include <map>

class YearlyCalculator : public StatisticsCalculator {
public:
    void calculate(const std::vector<Transaction>& transactions,
                  const std::string& start_date,
                  const std::string& end_date) override;
    
    const std::map<std::string, double>& getYearlyStats() const { return yearly_stats_; }

private:
    std::map<std::string, double> yearly_stats_;
    std::string extractYear(const std::string& date) const;
};