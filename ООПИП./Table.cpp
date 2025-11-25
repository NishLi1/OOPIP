#include "Table.h"

namespace TablePrinter {

    void printBorder() {
        std::cout << "+" << std::string(WIDTH - 2, '-') << "+" << "\n";
    }

    void printEmptyLineInBox() {
        std::cout << "|" << std::string(WIDTH - 2, ' ') << "|" << "\n";
    }

    void printCenteredInBox(const std::string& text) {
        int inner = WIDTH - 2;
        std::string t = text;
        if ((int)t.size() > inner) {
            t = t.substr(0, inner - 3) + "...";
        }
        int leftPad = (inner - (int)t.size()) / 2;
        int rightPad = inner - leftPad - (int)t.size();
        std::cout << "|" << std::string(leftPad, ' ') << t << std::string(rightPad, ' ') << "|" << "\n";
    }

    void printCenteredLine(const std::string& text) {
        int padding = (WIDTH - static_cast<int>(text.size())) / 2;
        if (padding < 0) padding = 0;
        std::cout << std::string(padding, ' ') << text << "\n";
    }

    void printCentered(const std::string& text) {
        int padding = (WIDTH - static_cast<int>(text.size())) / 2;
        if (padding < 0) padding = 0;
        std::cout << std::string(padding, ' ') << text;
    }

    std::string formatMoney(double value) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << value << " BYN";
        return ss.str();
    }

    std::string centerCell(const std::string& text, int width) {
        if (text.length() >= width) return text.substr(0, width);
        int padding = width - text.length();
        int left = padding / 2;
        int right = padding - left;
        return std::string(left, ' ') + text + std::string(right, ' ');
    }

}