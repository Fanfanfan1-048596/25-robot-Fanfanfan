#include "ui/Menu.hpp"
#include <regex>
#include "core/Constants.hpp"

Menu::Menu() {
    try {
        book_.loadFromFile(Constants::DATA_FILE);
    } catch (const std::exception& e) {
        std::cerr << "警告: " << e.what() << std::endl;
    }
}

void Menu::run() {
    while (true) {
        showMainMenu();
        handleInput();
    }
}

void Menu::showMainMenu() const {
    std::cout << "\n=== 个人账本管理系统 ===\n"
              << "1. 添加账务记录\n"
              << "2. 删除账务记录\n"
              << "3. 修改账务记录\n"
              << "4. 查询账务记录\n"
              << "5. 显示所有记录\n"
              << "6. 排序账务记录\n"
              << "7. 统计账务情况\n"
              << "8. 保存并退出\n"
              << "请选择操作 (1-8): ";
}

void Menu::handleInput() {
    int choice;
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
        case 1: addTransaction(); break;
        case 2: removeTransaction(); break;
        case 3: modifyTransaction(); break;
        case 4: searchTransactions(); break;
        case 5: showAllTransactions(); break;
        case 6: sortTransactions(); break;
        case 7: showStatistics(); break;
        case 8: 
            book_.saveToFile(Constants::DATA_FILE);
            std::cout << "数据已保存，程序退出\n";
            exit(0);
        default:
            std::cout << "无效选择，请重试\n";
    }
}

void Menu::addTransaction() {
    std::cout << "\n=== 添加账务记录 ===\n";
    std::string date = getValidDate("请输入日期 (YYYY-MM-DD): ");
    
    std::string name;
    std::cout << "请输入名称: ";
    std::getline(std::cin, name);
    
    double amount;
    std::cout << "请输入金额 (收入为正，支出为负): ";
    std::cin >> amount;
    clearInputBuffer();
    
    book_.addTransaction(Transaction(name, amount, date));
    std::cout << "添加成功!\n";
}

void Menu::removeTransaction() {
    showAllTransactions();
    std::cout << "\n请输入要删除的记录ID: ";
    int id;
    std::cin >> id;
    clearInputBuffer();
    
    if (book_.removeTransaction(id)) {
        std::cout << "删除成功!\n";
    } else {
        std::cout << "未找到ID为 " << id << " 的记录\n";
    }
}

void Menu::modifyTransaction() {
    showAllTransactions();
    std::cout << "\n请输入要修改的记录ID: ";
    int id;
    std::cin >> id;
    clearInputBuffer();
    
    std::string date = getValidDate("请输入新日期 (YYYY-MM-DD): ");
    
    std::string name;
    std::cout << "请输入新名称: ";
    std::getline(std::cin, name);
    
    double amount;
    std::cout << "请输入新金额: ";
    std::cin >> amount;
    clearInputBuffer();
    
    if (book_.modifyTransaction(id, Transaction(name, amount, date))) {
        std::cout << "修改成功!\n";
    } else {
        std::cout << "未找到ID为 " << id << " 的记录\n";
    }
}

void Menu::searchTransactions() {
    std::cout << "\n请输入要搜索的名称: ";
    std::string name;
    std::getline(std::cin, name);
    
    auto results = book_.searchByName(name);
    if (results.empty()) {
        std::cout << "未找到匹配记录\n";
        return;
    }
    
    std::cout << "\n搜索结果:\n";
    std::cout << std::setw(4) << "ID" << " | "
              << std::setw(10) << "日期" << " | "
              << std::setw(20) << "名称" << " | "
              << std::setw(10) << "金额" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& trans : results) {
        std::cout << trans << std::endl;
    }
}

void Menu::showAllTransactions() const {
    auto transactions = book_.getAllTransactions();
    if (transactions.empty()) {
        std::cout << "没有记录\n";
        return;
    }
    
    std::cout << "\n所有记录:\n";
    std::cout << std::setw(4) << "ID" << " | "
              << std::setw(10) << "日期" << " | "
              << std::setw(20) << "名称" << " | "
              << std::setw(10) << "金额" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& trans : transactions) {
        std::cout << trans << std::endl;
    }
}

void Menu::sortTransactions() {
    std::cout << "\n排序方式:\n"
              << "1. 按日期排序\n"
              << "2. 按金额排序\n"
              << "请选择 (1-2): ";
    
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    switch (choice) {
        case 1:
            book_.sortByDate();
            std::cout << "已按日期排序\n";
            break;
        case 2:
            book_.sortByAmount();
            std::cout << "已按金额排序\n";
            break;
        default:
            std::cout << "无效选择\n";
            return;
    }
    
    showAllTransactions();
}

void Menu::showStatistics() {
    std::cout << "\n统计方式:\n"
              << "1. 按日统计\n"
              << "2. 按月统计\n"
              << "3. 按年统计\n"
              << "请选择 (1-3): ";
    
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    
    std::string start_date = getValidDate("请输入起始日期 (YYYY-MM-DD): ");
    std::string end_date = getValidDate("请输入结束日期 (YYYY-MM-DD): ");
    
    std::shared_ptr<StatisticsCalculator> calculator;
    switch (choice) {
        case 1:
            calculator = std::make_shared<DailyCalculator>();
            break;
        case 2:
            calculator = std::make_shared<MonthlyCalculator>();
            break;
        case 3:
            calculator = std::make_shared<YearlyCalculator>();
            break;
        default:
            std::cout << "无效选择\n";
            return;
    }
    
    book_.calculate(calculator, start_date, end_date);
    
    std::cout << "\n统计结果:\n"
              << "总收入: " << calculator->getTotalIncome() << std::endl
              << "总支出: " << calculator->getTotalExpense() << std::endl
              << "结余: " << calculator->getBalance() << std::endl;
}

bool Menu::isValidDate(const std::string& date) {
    std::regex date_pattern("\\d{4}-\\d{2}-\\d{2}");
    return std::regex_match(date, date_pattern);
}

void Menu::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Menu::getValidDate(const std::string& prompt) {
    std::string date;
    do {
        std::cout << prompt;
        std::getline(std::cin, date);
        if (isValidDate(date)) break;
        std::cout << "日期格式无效，请使用YYYY-MM-DD格式\n";
    } while (true);
    return date;
}