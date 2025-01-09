#include "data/FileManager.hpp"
#include <fstream>
#include <stdexcept>

void FileManager::saveToFile(const std::string& filename, 
                           const std::vector<Transaction>& transactions) {
    checkFile(filename, true);
    std::ofstream file(filename, std::ios::binary);
    size_t size = transactions.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& trans : transactions) {
        file.write(reinterpret_cast<const char*>(&trans), sizeof(Transaction));
    }
}

std::vector<Transaction> FileManager::loadFromFile(const std::string& filename) {
    checkFile(filename);
    std::ifstream file(filename, std::ios::binary);
    std::vector<Transaction> transactions;
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    transactions.resize(size);
    for (size_t i = 0; i < size; ++i) {
        file.read(reinterpret_cast<char*>(&transactions[i]), sizeof(Transaction));
    }
    return transactions;
}

void FileManager::checkFile(const std::string& filename, bool writing) {
    if (writing) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("无法创建文件：" + filename);
    } else {
        std::ifstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("无法打开文件：" + filename);
    }
}