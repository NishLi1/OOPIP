#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace TablePrinter {
    static const int WIDTH = 120;
    void printBorder();
    void printEmptyLineInBox();
    void printCenteredInBox(const std::string& text);
    void printCenteredLine(const std::string& text);
    void printCentered(const std::string& text);
    std::string formatMoney(double value);
    std::string centerCell(const std::string& text, int width);
}