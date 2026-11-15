#include "Console.h"
#include <charconv>
#include <iostream>
#include <sstream>
#include <string>
#include "exceptions.h"

// ---------- ââîä ----------

int readNumber(std::string_view prompt) {
    std::string line;
    int val;
    char tail;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return 0;   // êîíåö ââîäà: âûõîäèì èç ïðîãðàììû
        if (std::stringstream ss(line); ss >> val && !(ss >> tail)) return val;
        std::cout << "Íåâåðíûé ââîä! Ââåäèòå öåëîå ÷èñëî.\n";
    }
}

std::string readText(std::string_view prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) throw InputAbortedException("ïîòîê ââîäà çàêðûò!");
    return line;
}

int readInteger(std::string_view prompt) {
    const std::string line = readText(prompt);
    const auto first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) throw InvalidDataException("íóæíî ââåñòè öåëîå ÷èñëî, à ââåäåíà ïóñòàÿ ñòðîêà!");
    const auto last = line.find_last_not_of(" \t\r\n");
    const std::string_view text = std::string_view(line).substr(first, last - first + 1);

    int value = 0;
    const auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (ec != std::errc{} || ptr != text.data() + text.size()) {
        throw InvalidDataException("íóæíî ââåñòè öåëîå ÷èñëî, ïîëó÷åíî \"" + std::string(text) + "\"!");
    }
    return value;
}

// ---------- îôîðìëåíèå âûâîäà ----------

void section(std::string_view title) {
    std::cout << "\n==================================================\n"
        << title << "\n"
        << "==================================================\n";
}

void step(std::string_view text) {
    std::cout << "\n>> " << text << "\n";
}
