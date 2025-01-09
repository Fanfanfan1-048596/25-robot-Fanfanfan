#pragma once
#include <vector>
#include <memory>
#include <string>
#include "core/Transaction.hpp"
#include "stats/StatisticsCalculator.hpp"

class AccountBook {
public:
    void addTransaction(const Transaction& trans);
    bool removeTransaction(int id);
    bool modifyTransaction(int id, const Transaction& trans);
    std::vector<Transaction> searchByName(const std::string& name) const;
    std::vector<Transaction> getAllTransactions() const { return transactions_; }
    
    void sortByDate();
    void sortByAmount();
    
    void calculate(std::shared_ptr<StatisticsCalculator> calculator,
                  const std::string& start_date,
                  const std::string& end_date) const;
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

private:
    std::vector<Transaction> transactions_;
};