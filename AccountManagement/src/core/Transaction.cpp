#include "core/Transaction.hpp"

int Transaction::next_id_ = 1;

Transaction::Transaction(const std::string& name, double amount, const std::string& date)
    : id_(next_id_++), name_(name), amount_(amount), date_(date) {}

bool Transaction::operator<(const Transaction& other) const {
    return date_ < other.date_;
}

std::ostream& operator<<(std::ostream& os, const Transaction& trans) {
    os << std::setw(4) << trans.id_ << " | "
       << std::setw(10) << trans.date_ << " | "
       << std::setw(20) << trans.name_ << " | "
       << std::setw(10) << std::fixed << std::setprecision(2) << trans.amount_;
    return os;
}