#pragma once
#include <string>
#include <vector>
#include "core/Transaction.hpp"

class FileManager {
public:
    static void saveToFile(const std::string& filename, 
                          const std::vector<Transaction>& transactions);
    static std::vector<Transaction> loadFromFile(const std::string& filename);

private:
    static void checkFile(const std::string& filename, bool writing = false);
};