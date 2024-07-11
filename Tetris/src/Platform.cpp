#include "../include/Platform.h"

void Platform::DoPlatform() {
    platform.clear();
    for (int i = 0; i < height; i++) {
        std::string line(width, ' ');
        platform.push_back(line);
    }
}

void Platform::PrintPlatform() {
    std::string border(width + 2, '-');
    std::cout << "\t\t\t\t" << border << std::endl;
    for (std::string& line : platform) {
        std::cout << "\t\t\t\t" << "|" << line << "|" << std::endl;
    }
    std::cout << "\t\t\t\t" << border << std::endl;
}