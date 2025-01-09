#include "stats/StatisticsCalculator.hpp"

bool StatisticsCalculator::isInRange(const std::string& date,
                                   const std::string& start,
                                   const std::string& end) const {
    return date >= start && date <= end;
}