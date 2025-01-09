#pragma once
#include "StatisticsCalculator.hpp"
#include <map>

class DailyCalculator : public StatisticsCalculator {
public:
    void calculate(const std::vector<Transaction>& transactions,
                  const std::string& start_date,
                  const std::string& end_date) override;
    
    const std::map<std::string, double>& getDailyStats() const { return daily_stats_; }

private:
    std::map<std::string, double> daily_stats_;
};