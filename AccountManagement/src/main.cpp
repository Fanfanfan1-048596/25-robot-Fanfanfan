#include "ui/Menu.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Menu menu;
        menu.run();
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}