#include "data/AccountBook.hpp"
#include "data/FileManager.hpp"
#include <algorithm>

void AccountBook::addTransaction(const Transaction& trans) {
    transactions_.push_back(trans);
}

bool AccountBook::removeTransaction(int id) {
    auto it = std::find_if(transactions_.begin(), transactions_.end(),
                          [id](const Transaction& t) { return t.getId() == id; });
    if (it != transactions_.end()) {
        transactions_.erase(it);
        return true;
    }
    return false;
}

bool AccountBook::modifyTransaction(int id, const Transaction& trans) {
    auto it = std::find_if(transactions_.begin(), transactions_.end(),
                          [id](const Transaction& t) { return t.getId() == id; });
    if (it != transactions_.end()) {
        *it = trans;      
        return true;
    }
    return false;
}

std::vector<Transaction> AccountBook::searchByName(const std::string& name) const {
    std::vector<Transaction> results;
    std::copy_if(transactions_.begin(), transactions_.end(), 
                 std::back_inserter(results),
                 [&name](const Transaction& t) {
                     return t.getName().find(name) != std::string::npos;
                 });
    return results;
}

void AccountBook::sortByDate() {
    std::sort(transactions_.begin(), transactions_.end());
}

void AccountBook::sortByAmount() {
    std::sort(transactions_.begin(), transactions_.end(),
              [](const Transaction& a, const Transaction& b) {
                  return a.getAmount() < b.getAmount();
              });
}

void AccountBook::calculate(std::shared_ptr<StatisticsCalculator> calculator,
                          const std::string& start_date,
                          const std::string& end_date) const {
    calculator->calculate(transactions_, start_date, end_date);
}

void AccountBook::saveToFile(const std::string& filename) const {
    FileManager::saveToFile(filename, transactions_);
}

void AccountBook::loadFromFile(const std::string& filename) {
    transactions_ = FileManager::loadFromFile(filename);
}