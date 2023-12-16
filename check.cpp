#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

std::string tmToString(const std::tm& timeStruct, const std::string& format) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format.c_str(), &timeStruct);
    return std::string(buffer);
}

int main() {
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a std::tm structure
    std::tm* currentDate = std::localtime(&currentTime);

    if (currentDate != nullptr) {
        // Convert std::tm to std::string with a custom format
        std::string dateString = tmToString(*currentDate, "%Y-%m-%d");

        std::cout << "Current Date as string: " << dateString << std::endl;
    } else {
        std::cerr << "Failed to get current date." << std::endl;
    }

    return 0;
}
