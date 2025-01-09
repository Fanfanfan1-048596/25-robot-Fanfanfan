#include <gtest/gtest.h>
#include "core/Transaction.hpp"
#include "data/AccountBook.hpp"
#include "stats/DailyCalculator.hpp"

class AccountBookTest : public ::testing::Test {
protected:
    AccountBook book;
    
    void SetUp() override {
        book.addTransaction(Transaction("工资", 5000, "2024-01-01"));
        book.addTransaction(Transaction("购物", -1000, "2024-01-02"));
    }
};

TEST_F(AccountBookTest, AddTransaction) {
    auto transactions = book.getAllTransactions();
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0].getName(), "工资");
    EXPECT_EQ(transactions[0].getAmount(), 5000);
}

TEST_F(AccountBookTest, SearchByName) {
    auto results = book.searchByName("工资");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getAmount(), 5000);
}

TEST_F(AccountBookTest, Calculate) {
    auto calculator = std::make_shared<DailyCalculator>();
    book.calculate(calculator, "2024-01-01", "2024-01-31");
    EXPECT_EQ(calculator->getTotalIncome(), 5000);
    EXPECT_EQ(calculator->getTotalExpense(), -1000);
    EXPECT_EQ(calculator->getBalance(), 4000);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}