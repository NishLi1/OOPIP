#include "Role.h"
#include "Table.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <algorithm>

using namespace TablePrinter;

std::deque<UserRecord> g_users;
std::vector<InfoBasicStaff> b_infos;
std::vector<InfoSpecialist> s_infos;
std::vector<InfoManager> m_infos;
std::unordered_map<std::string, std::vector<std::string>> dept_members;

std::ostream& operator<<(std::ostream& os, const InfoBasicStaff& info) {
    const int col1 = 20;
    const int col2 = 30;

    printBorder();
    printCenteredInBox("=== ИНФОРМАЦИЯ О БАЗОВОМ ПЕРСОНАЛЕ ===");
    printEmptyLineInBox();

    std::stringstream ss;
    ss << "| " << centerCell("ФИО:", col1) << " | " << centerCell(info.name, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Возраст:", col1) << " | " << centerCell(std::to_string(info.age), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Должность:", col1) << " | " << centerCell(info.title, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Стаж (лет):", col1) << " | " << centerCell(std::to_string(info.WorkExp), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Зарплата:", col1) << " | " << centerCell(formatMoney(info.salary), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Место работы:", col1) << " | " << centerCell(info.WorkPlace, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Инвентарь:", col1) << " | " << centerCell(info.inventory, col2) << " |";
    printCenteredInBox(ss.str());

    printEmptyLineInBox();
    printBorder();
    return os;
}

std::istream& operator>>(std::istream& is, InfoBasicStaff& info) {
    system("cls");
    printBorder();
    printCenteredInBox("=== ДОБАВЛЕНИЕ ИНФОРМАЦИИ ===");
    printEmptyLineInBox();
    printBorder();

    printCentered("ФИО: ");
    std::string name;
    getline(is >> std::ws, name);
    info.name = name;

    while (true) {
        try {
            printCentered("Возраст: ");
            std::string ageStr;
            getline(std::cin, ageStr);
            std::cin.ignore();
            info.age = std::stoi(ageStr);
            if (info.age < 0 || info.age > 150) throw std::out_of_range("Недопустимый возраст");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный возраст (0-150)");
        }
    }

    while (true) {
        try {
            printCentered("Зарплата: ");
            std::string salaryStr;
            getline(std::cin, salaryStr);
            info.salary = std::stod(salaryStr);
            if (info.salary < 0) throw std::out_of_range("Зарплата не может быть отрицательной");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректную зарплату");
        }
    }

    while (true) {
        try {
            printCentered("Стаж (лет): ");
            std::string expStr;
            getline(std::cin, expStr);
            info.WorkExp = std::stod(expStr);
            if (info.WorkExp < 0) throw std::out_of_range("Стаж не может быть отрицательным");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный стаж");
        }
    }

    printCentered("Должность/Титул: ");
    std::string title;
    getline(is, title);
    info.title = title;

    printCentered("Место работы: ");
    std::string workPlace;
    getline(is, workPlace);
    info.WorkPlace = workPlace;

    printCentered("Инвентарь (через запятую или строкой): ");
    std::string inventory;
    getline(is, inventory);
    info.inventory = inventory;

    return is;
}

std::ostream& operator<<(std::ostream& os, const InfoSpecialist& info) {
    const int col1 = 20;
    const int col2 = 30;

    printBorder();
    printCenteredInBox("=== ИНФОРМАЦИЯ О СПЕЦИАЛИСТЕ ===");
    printEmptyLineInBox();

    std::stringstream ss;
    ss << "| " << centerCell("ФИО:", col1) << " | " << centerCell(info.name, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Возраст:", col1) << " | " << centerCell(std::to_string(info.age), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Должность:", col1) << " | " << centerCell(info.title, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Стаж (лет):", col1) << " | " << centerCell(std::to_string(info.WorkExp), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Зарплата:", col1) << " | " << centerCell(formatMoney(info.salary), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Область специализации:", col1) << " | " << centerCell(info.area, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Образование:", col1) << " | " << centerCell(info.education, col2) << " |";
    printCenteredInBox(ss.str());

    printEmptyLineInBox();
    printBorder();
    return os;
}

std::istream& operator>>(std::istream& is, InfoSpecialist& info) {
    system("cls");
    printBorder();
    printCenteredInBox("=== ДОБАВЛЕНИЕ ИНФОРМАЦИИ ===");
    printEmptyLineInBox();
    printBorder();

    printCentered("ФИО: ");
    std::string name;
    getline(is >> std::ws, name);
    info.name = name;

    while (true) {
        try {
            printCentered("Возраст: ");
            std::string ageStr;
            getline(std::cin, ageStr);
            info.age = std::stoi(ageStr);
            if (info.age < 0 || info.age > 150) throw std::out_of_range("Недопустимый возраст");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный возраст (0-150)");
        }
    }

    while (true) {
        try {
            printCentered("Зарплата: ");
            std::string salaryStr;
            getline(std::cin, salaryStr);
            info.salary = std::stod(salaryStr);
            if (info.salary < 0) throw std::out_of_range("Зарплата не может быть отрицательной");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректную зарплату");
        }
    }

    while (true) {
        try {
            printCentered("Стаж (лет): ");
            std::string expStr;
            getline(std::cin, expStr);
            info.WorkExp = std::stod(expStr);
            if (info.WorkExp < 0) throw std::out_of_range("Стаж не может быть отрицательным");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный стаж");
        }
    }

    printCentered("Должность/Титул: ");
    std::string title;
    getline(is, title);
    info.title = title;

    printCentered("Область специализации: ");
    std::string area;
    getline(is, area);
    info.area = area;

    printCentered("Образование: ");
    std::string education;
    getline(is, education);
    info.education = education;

    return is;
}

std::ostream& operator<<(std::ostream& os, const InfoManager& info) {
    const int col1 = 25;
    const int col2 = 25;

    printBorder();
    printCenteredInBox("=== ИНФОРМАЦИЯ О МЕНЕДЖЕРЕ ===");
    printEmptyLineInBox();

    std::stringstream ss;
    ss << "| " << centerCell("ФИО:", col1) << " | " << centerCell(info.name, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Возраст:", col1) << " | " << centerCell(std::to_string(info.age), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Должность:", col1) << " | " << centerCell(info.title, col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Стаж (лет):", col1) << " | " << centerCell(std::to_string(info.WorkExp), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Зарплата:", col1) << " | " << centerCell(formatMoney(info.salary), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Количество подчиненных:", col1) << " | " << centerCell(std::to_string(info.employee), col2) << " |";
    printCenteredInBox(ss.str()); ss.str("");

    ss << "| " << centerCell("Отдел:", col1) << " | " << centerCell(info.department, col2) << " |";
    printCenteredInBox(ss.str());

    printEmptyLineInBox();
    printBorder();
    return os;
}

std::istream& operator>>(std::istream& is, InfoManager& info) {
    system("cls");
    printBorder();
    printCenteredInBox("=== ДОБАВЛЕНИЕ ИНФОРМАЦИИ ===");
    printEmptyLineInBox();
    printBorder();

    printCentered("ФИО: ");
    std::string name;
    getline(is >> std::ws, name);
    info.name = name;

    while (true) {
        try {
            printCentered("Возраст: ");
            std::string ageStr;
            getline(std::cin, ageStr);
            info.age = std::stoi(ageStr);
            if (info.age < 0 || info.age > 150) throw std::out_of_range("Недопустимый возраст");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный возраст (0-150)");
        }
    }

    while (true) {
        try {
            printCentered("Зарплата: ");
            std::string salaryStr;
            getline(std::cin, salaryStr);
            info.salary = std::stod(salaryStr);
            if (info.salary < 0) throw std::out_of_range("Зарплата не может быть отрицательной");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректную зарплату");
        }
    }

    while (true) {
        try {
            printCentered("Стаж (лет): ");
            std::string expStr;
            getline(std::cin, expStr);
            info.WorkExp = std::stod(expStr);
            if (info.WorkExp < 0) throw std::out_of_range("Стаж не может быть отрицательным");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный стаж");
        }
    }

    printCentered("Должность/Титул: ");
    std::string title;
    getline(is, title);
    info.title = title;

    while (true) {
        try {
            printCentered("Количество подчиненных: ");
            std::string empStr;
            getline(std::cin, empStr);
            info.employee = std::stoi(empStr);
            if (info.employee < 0) throw std::out_of_range("Количество подчиненных не может быть отрицательным");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректное количество подчиненных");
        }
    }

    printCentered("Отдел: ");
    std::string department;
    getline(is, department);
    info.department = department;

    return is;
}