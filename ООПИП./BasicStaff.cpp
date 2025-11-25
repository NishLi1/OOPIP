#include "BasicStaff.h"
#include "Table.h"
#include "Menu.h"
#include <conio.h>
#include <Windows.h>
#include <algorithm>

using namespace TablePrinter;

BasicStaff::BasicStaff(const std::string& h) : UserBase(h) {}

void BasicStaff::showMenu() {
    std::vector<std::string> items = {
        "Посмотреть общую информацию",
        "Добавить общую информацию",
        "Редактировать общую информацию",
        "Удалить общую информацию",
        "Выйти"
    };
    while (true) {
        int ch = menu(items, "=== Меню: Базовый персонал ===");
        switch (ch) {
        case 0: showInfo(); break;
        case 1: addInfo(); break;
        case 2: editInfo(); break;
        case 3: deleteInfo(); break;
        case 4: return;
        }
    }
}

void BasicStaff::showInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Ваша информация ===");
    printEmptyLineInBox();

    bool found = false;
    for (const auto& e : b_infos) {
        if (e.loginHash == loginHash) {
            found = true;
            std::cout << e;
            break;
        }
    }

    if (!found) {
        printCenteredInBox("(Информация отсутствует)");
        printEmptyLineInBox();
        printBorder();
    }

    printCentered("Нажмите любую клавишу...");
    _getch();
}

void BasicStaff::addInfo()  {
    for (const auto& e : b_infos) {
        if (e.loginHash == loginHash) {
            system("cls");
            printBorder();
            printCenteredInBox("=== Ошибка ===");
            printEmptyLineInBox();
            printCenteredInBox("Информация уже добавлена. Нельзя добавить повторно.");
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            return;
        }
    }

    InfoBasicStaff e;
    e.loginHash = loginHash;
    std::cin >> e;

    b_infos.push_back(e);
    save.saveBasicInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно сохранена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void BasicStaff::editInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Редактирование информации ===");
    printEmptyLineInBox();

    int idx = -1;
    for (size_t i = 0; i < b_infos.size(); ++i) {
        if (b_infos[i].loginHash == loginHash) { idx = (int)i; break; }
    }

    if (idx == -1) {
        printCenteredInBox("(Информация для редактирования отсутствует)");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    printCenteredInBox("Оставьте пустым и нажмите Enter, чтобы оставить старое значение.");
    printEmptyLineInBox();

    InfoBasicStaff temp = b_infos[idx];

    std::string tmp;

    printCentered(("ФИО (старое: " + temp.name + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.name = tmp;

    while (true) {
        try {
            printCentered(("Возраст (старое: " + std::to_string(temp.age) + "): "));
            getline(std::cin, tmp);
            if (!tmp.empty()) {
                temp.age = std::stoi(tmp);
                if (temp.age < 0 || temp.age > 150) throw std::out_of_range("Недопустимый возраст");
            }
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный возраст (0-150)");
        }
    }

    printCentered(("Должность (старое: " + temp.title + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.title = tmp;

    while (true) {
        try {
            printCentered(("Стаж (старое: " + std::to_string(temp.WorkExp) + "): "));
            getline(std::cin, tmp);
            if (!tmp.empty()) {
                temp.WorkExp = std::stod(tmp);
                if (temp.WorkExp < 0) throw std::out_of_range("Стаж не может быть отрицательным");
            }
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный стаж");
        }
    }

    while (true) {
        try {
            printCentered(("Зарплата (старое: " + formatMoney(temp.salary) + "): "));
            getline(std::cin, tmp);
            if (!tmp.empty()) {
                temp.salary = std::stod(tmp);
                if (temp.salary < 0) throw std::out_of_range("Зарплата не может быть отрицательной");
            }
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректную зарплату");
        }
    }

    printCentered(("Место работы (старое: " + temp.WorkPlace + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.WorkPlace = tmp;

    printCentered(("Инвентарь (старое: " + temp.inventory + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.inventory = tmp;

    b_infos[idx] = temp;
    save.saveBasicInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно обновлена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void BasicStaff::deleteInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Удаление информации ===");
    printEmptyLineInBox();

    auto it = std::find_if(b_infos.begin(), b_infos.end(),
        [&](const InfoBasicStaff& e) { return e.loginHash == loginHash; });

    if (it == b_infos.end()) {
        printCenteredInBox("(Информация отсутствует)");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    printCenteredInBox("Текущая информация:");
    printEmptyLineInBox();
    std::cout << *it;

    printCenteredInBox("Нажмите 'y' для подтверждения удаления, любая другая клавиша — отмена.");
    printEmptyLineInBox();
    printBorder();

    int key = _getch();
    if (key == 'y' || key == 'Y') {
        b_infos.erase(it);
        save.saveBasicInfos();

        system("cls");
        printBorder();
        printCenteredInBox("Информация удалена.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
    }
    else {
        system("cls");
        printBorder();
        printCenteredInBox("Удаление отменено.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
    }
}

Role BasicStaff::getType()  {
    return Role::basic;
}