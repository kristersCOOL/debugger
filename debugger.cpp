#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h>

// Define debug levels
enum class DebugLevel {
    INFO,
    WARNING,
    ERROR
};

struct DebugInfo {
    DebugLevel level;
    std::string message;
};

void debug(DebugLevel level, const std::string& message) {
    std::cout << "[";

    // Print the debug level
    switch (level) {
        case DebugLevel::INFO:
            std::cout << "INFO";
            break;
        case DebugLevel::WARNING:
            std::cout << "WARNING";
            break;
        case DebugLevel::ERROR:
            std::cout << "ERROR";
            break;
    }

    std::cout << "] " << message << std::endl;
}

void readDebugInfoFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        DebugLevel level;
        std::string message;

        std::istringstream iss(line);
        std::string levelStr;
        iss >> levelStr;

        if (levelStr == "INFO")
            level = DebugLevel::INFO;
        else if (levelStr == "WARNING")
            level = DebugLevel::WARNING;
        else if (levelStr == "ERROR")
            level = DebugLevel::ERROR;

        std::getline(iss, message);
        debug(level, message);
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <debug_file>" << std::endl;
        return 1;
    }

    readDebugInfoFromFile(argv[1]);

    debug(DebugLevel::INFO, "This is a debugger. Use the javascript to set the application or file.");
    debug(DebugLevel::WARNING, "Warning this can damage or corrupt the application/file.");
    debug(DebugLevel::ERROR, "Failed reading the app/file.");

    return 0;
}
