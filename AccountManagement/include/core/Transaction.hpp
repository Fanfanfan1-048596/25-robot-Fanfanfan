#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Transaction {
public:
    Transaction() = default;
    Transaction(const std::string& name, double amount, const std::string& date);
    
    int getId() const { return id_; }
    const std::string& getName() const { return name_; }
    double getAmount() const { return amount_; }
    const std::string& getDate() const { return date_; }
    
    bool operator<(const Transaction& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Transaction& trans);

private:
    int id_{0};
    std::string name_;
    double amount_{0.0};
    std::string date_;
    static int next_id_;
};