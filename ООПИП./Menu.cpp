#include "Menu.h"

using namespace TablePrinter;

int menu(const std::vector<std::string>& items, const std::string& title) {
    int choice = 0;
    while (true) {
        system("cls");
        printBorder();
        if (!title.empty()) {
            printCenteredInBox(title);
            printEmptyLineInBox();
        }
        else {
            printEmptyLineInBox();
        }

        for (size_t i = 0; i < items.size(); ++i) {
            if (static_cast<int>(i) == choice) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                printCenteredInBox(std::string("→ ") + items[i] + " ←");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else {
                printCenteredInBox(items[i]);
            }
        }

        printEmptyLineInBox();
        printBorder();

        int key = _getch();
        if (key == 224) {
            int k = _getch();
            if (k == 72 && choice > 0) --choice;
            else if (k == 80 && choice < static_cast<int>(items.size()) - 1) ++choice;
        }
        else if (key == 13) {
            return choice;
        }
    }
}