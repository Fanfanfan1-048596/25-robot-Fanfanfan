#include "data/FileManager.hpp"
#include "core/Constants.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

void FileManager::saveToFile(const std::string& filename, 
                           const std::vector<Transaction>& transactions) {
    checkFile(filename, true);
    std::ofstream file(filename);
    // 写入CSV头
    file << "ID,日期,名称,金额\n";
    writeCSV(file, transactions);
}

std::vector<Transaction> FileManager::loadFromFile(const std::string& filename) {
    checkFile(filename);
    std::ifstream file(filename);
    std::string header;
    std::getline(file, header); // 跳过CSV头
    return readCSV(file);
}

void FileManager::writeCSV(std::ofstream& file, 
                          const std::vector<Transaction>& transactions) {
    for (const auto& trans : transactions) {
        file << trans.getId() << ","
             << trans.getDate() << ","
             << trans.getName() << ","
             << trans.getAmount() << "\n";
    }
}

std::vector<Transaction> FileManager::readCSV(std::ifstream& file) {
    std::vector<Transaction> transactions;
    std::string line;
    while (std::getline(file, line)) {
        auto fields = splitCSVLine(line);
        if (fields.size() == 4) {
            Transaction trans(fields[2], 
                           std::stod(fields[3]), 
                           fields[1]);
            transactions.push_back(trans);
        }
    }
    return transactions;
}

std::vector<std::string> FileManager::splitCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

void FileManager::checkFile(const std::string& filename, bool writing) {
    fs::path dataDir = Constants::DATA_DIR;
    if (!fs::exists(dataDir)) {
        fs::create_directories(dataDir);
    }

    if (writing) {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("无法创建文件：" + filename);
        }
    } else {
        std::ifstream file(filename);
        if (!file && writing) {
            throw std::runtime_error("无法打开文件：" + filename);
        }
    }
}