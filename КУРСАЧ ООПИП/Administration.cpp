#include "Administration.h"
#include <conio.h>
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <memory>
#include <deque>

using namespace TablePrinter;

template<typename Container>
void Administration::displayEmployeesByType(const Container& employees, const std::string& typeName) {
    system("cls");
    printBorder();
    printCenteredInBox("=== " + typeName + " ===");
    printEmptyLineInBox();

    if (employees.empty()) {
        printCenteredInBox("(Нет записей)");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    int count = 1;
    for (const auto& e : employees) {
        printCenteredInBox(typeName + " № " + std::to_string(count++));
        std::cout << e;
    }

    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

template<typename Container>
void Administration::searchInContainer(const Container& container, const std::string& searchName, const std::string& typeName) {
    bool found = false;

    for (const auto& e : container) {
        if (containsName(e, searchName)) {
            if (!found) {
                found = true;
            }
            std::string line = "[" + typeName + "] " + e.name + " | " + e.title + " | " + formatMoney(e.salary);
            printCenteredInBox(line);
        }
    }
}

template<typename Container>
void Administration::filterExperiencedEmployees(const Container& container, const std::string& typeName) {
    bool found = false;

    for (const auto& e : container) {
        if (isExperiencedEmployee(e)) {
            if (!found) {
                found = true;
            }
            std::string line = e.name + " | Стаж: " + std::to_string(e.WorkExp) + " | Зарплата: " + formatMoney(e.salary);
            printCenteredInBox(line);
        }
    }

    if (!found) {
        printCenteredInBox("(Нет таких сотрудников)");
    }
}

template<typename Container>
void Administration::sortContainerBySalary(Container& container, const std::string& typeName) {
    if (container.empty()) {
        system("cls");
        printBorder();
        printCenteredInBox("Нет " + typeName + " для сортировки");
        printEmptyLineInBox();
        printBorder();
        return;
    }

    sort(container.begin(), container.end(), [this](const auto& a, const auto& b) {
        return compareBySalary(a, b);
        });

    system("cls");
    printBorder();
    printCenteredInBox("Сортировка завершена успешно!");
    printEmptyLineInBox();
    printCenteredInBox(typeName + " отсортированы по зарплате (возрастание)");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Administration::generateReport() {
    system("cls");
    printBorder();
    printCenteredInBox("=== ГЕНЕРАЦИЯ ОТЧЕТА ===");
    printEmptyLineInBox();

    printBorder();
    printCenteredInBox("ОТЧЕТ ПО ВСЕМ СОТРУДНИКАМ");
    printCenteredInBox("Дата генерации: " + std::string(__DATE__) + " " + __TIME__);
    printEmptyLineInBox();

    std::vector<std::string> reportLines;

    if (!b_infos.empty()) {
        reportLines.push_back("=== БАЗОВЫЙ ПЕРСОНАЛ ===");
        for (size_t i = 0; i < b_infos.size(); ++i) {
            reportLines.push_back("Сотрудник №" + std::to_string(i + 1) + ":");
            reportLines.push_back("  ФИО: " + b_infos[i].name);
            reportLines.push_back("  Возраст: " + std::to_string(b_infos[i].age));
            reportLines.push_back("  Должность: " + b_infos[i].title);
            reportLines.push_back("  Стаж: " + std::to_string(b_infos[i].WorkExp) + " лет");
            reportLines.push_back("  Зарплата: " + formatMoney(b_infos[i].salary));
            reportLines.push_back("  Место работы: " + b_infos[i].WorkPlace);
            reportLines.push_back("  Инвентарь: " + b_infos[i].inventory);
            reportLines.push_back("");
        }
    }

    if (!s_infos.empty()) {
        reportLines.push_back("=== СПЕЦИАЛИСТЫ ===");
        for (size_t i = 0; i < s_infos.size(); ++i) {
            reportLines.push_back("Специалист №" + std::to_string(i + 1) + ":");
            reportLines.push_back("  ФИО: " + s_infos[i].name);
            reportLines.push_back("  Возраст: " + std::to_string(s_infos[i].age));
            reportLines.push_back("  Должность: " + s_infos[i].title);
            reportLines.push_back("  Стаж: " + std::to_string(s_infos[i].WorkExp) + " лет");
            reportLines.push_back("  Зарплата: " + formatMoney(s_infos[i].salary));
            reportLines.push_back("  Область специализации: " + s_infos[i].area);
            reportLines.push_back("  Образование: " + s_infos[i].education);
            reportLines.push_back("");
        }
    }

    if (!m_infos.empty()) {
        reportLines.push_back("=== МЕНЕДЖЕРЫ ===");
        for (size_t i = 0; i < m_infos.size(); ++i) {
            reportLines.push_back("Менеджер №" + std::to_string(i + 1) + ":");
            reportLines.push_back("  ФИО: " + m_infos[i].name);
            reportLines.push_back("  Возраст: " + std::to_string(m_infos[i].age));
            reportLines.push_back("  Должность: " + m_infos[i].title);
            reportLines.push_back("  Стаж: " + std::to_string(m_infos[i].WorkExp) + " лет");
            reportLines.push_back("  Зарплата: " + formatMoney(m_infos[i].salary));
            reportLines.push_back("  Количество подчиненных: " + std::to_string(m_infos[i].employee));
            reportLines.push_back("  Отдел: " + m_infos[i].department);
            reportLines.push_back("");
        }
    }

    reportLines.push_back("=== СТАТИСТИКА ===");
    reportLines.push_back("Всего базового персонала: " + std::to_string(b_infos.size()));
    reportLines.push_back("Всего специалистов: " + std::to_string(s_infos.size()));
    reportLines.push_back("Всего менеджеров: " + std::to_string(m_infos.size()));
    reportLines.push_back("Общее количество сотрудников: " + std::to_string(b_infos.size() + s_infos.size() + m_infos.size()));

    lastReportSize = reportLines.size();
    lastReport = std::make_unique<std::string[]>(lastReportSize);

    for (size_t i = 0; i < lastReportSize; ++i) {
        lastReport[i] = reportLines[i];
    }

    for (size_t i = 0; i < lastReportSize; ++i) {
        printCenteredInBox(lastReport[i]);
    }

    printEmptyLineInBox();
    printBorder();

    printCentered("Нажмите любую клавишу для продолжения...");
    _getch();

    system("cls");
    printBorder();
    printCenteredInBox("Сохранить отчет в файл? (y/n)");
    printEmptyLineInBox();
    printBorder();

    char choice = _getch();
    if (choice == 'y' || choice == 'Y') {
        system("cls");
        printBorder();
        printCenteredInBox("Введите имя файла (например: report.txt): ");
        printEmptyLineInBox();
        printBorder();
        printCentered("> ");

        std::string filename;
        getline(std::cin >> std::ws, filename);

        std::ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < lastReportSize; ++i) {
                file << lastReport[i] << "\n";
            }
            file.close();

            system("cls");
            printBorder();
            printCenteredInBox("Отчет успешно сохранен в файл: " + filename);
            printEmptyLineInBox();
            printBorder();
        }
        else {
            system("cls");
            printBorder();
            printCenteredInBox("Ошибка сохранения файла!");
            printEmptyLineInBox();
            printBorder();
        }

        printCentered("Нажмите любую клавишу...");
        _getch();
    }
}

void Administration::clearLastReport() {
    lastReport.reset();
    lastReportSize = 0;
}

void Administration::AdminMenu() {
    std::vector<std::string> items = {
        "Просмотреть работников выборочно",
        "Уволить работника",
        "Найти работника по имени",
        "Отсортировать выбранных работников",
        "Вывести опытных сотрудников",
        "Вывести отчёт",
        "Назад"
    };

    std::vector<std::string> type_worker = {
        "Базовый персонал",
        "Специалист",
        "Менеджер",
        "Назад"
    };

    while (true) {
        int choice = menu(items, "=== Администратор: управление записями ===");
        switch (choice) {
        case 0: {
            int type_choice = menu(type_worker, "=== Выберите тип сотрудников ===");
            switch (type_choice) {
            case 0: displayEmployeesByType(b_infos, "Базовый персонал"); break;
            case 1: displayEmployeesByType(s_infos, "Специалисты"); break;
            case 2: displayEmployeesByType(m_infos, "Менеджеры"); break;
            case 3: break;
            }
            break;
        }
        case 1: {
            std::vector<std::string> type_options = {
                "Базовый персонал",
                "Специалист",
                "Менеджер",
                "Назад"
            };

            int type_choice = menu(type_options, "=== Увольнение работника ===");
            if (type_choice == 3) break;

            system("cls");
            printBorder();
            printCenteredInBox("=== Увольнение работника ===");
            printEmptyLineInBox();

            std::vector<std::string> employees;
            std::vector<std::string> loginHashes;

            switch (type_choice) {
            case 0:
                if (b_infos.empty()) {
                    printCenteredInBox("Нет базового персонала для увольнения");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }
                for (const auto& e : b_infos) {
                    employees.push_back(e.name + " | " + e.title + " | " + formatMoney(e.salary));
                    loginHashes.push_back(e.loginHash);
                }
                break;
            case 1:
                if (s_infos.empty()) {
                    printCenteredInBox("Нет специалистов для увольнения");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }
                for (const auto& e : s_infos) {
                    employees.push_back(e.name + " | " + e.title + " | " + formatMoney(e.salary));
                    loginHashes.push_back(e.loginHash);
                }
                break;
            case 2:
                if (m_infos.empty()) {
                    printCenteredInBox("Нет менеджеров для увольнения");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }
                for (const auto& e : m_infos) {
                    employees.push_back(e.name + " | " + e.title + " | " + formatMoney(e.salary));
                    loginHashes.push_back(e.loginHash);
                }
                break;
            }

            if (!employees.empty()) {
                employees.push_back("Отмена");
                int emp_choice = menu(employees, "Выберите работника для увольнения:");

                if (emp_choice < (int)employees.size() - 1) {
                    std::string loginHashToDelete = loginHashes[emp_choice];

                    system("cls");
                    printBorder();
                    printCenteredInBox("=== Подтверждение увольнения ===");
                    printEmptyLineInBox();
                    printCenteredInBox("Вы уверены, что хотите уволить этого работника? (y/n)");
                    printEmptyLineInBox();
                    printBorder();

                    char confirm = _getch();

                    if (confirm == 'y' || confirm == 'Y') {
                        switch (type_choice) {
                        case 0:
                            b_infos.erase(std::remove_if(b_infos.begin(), b_infos.end(),
                                [&](const InfoBasicStaff& e) { return e.loginHash == loginHashToDelete; }),
                                b_infos.end());
                            break;
                        case 1:
                            s_infos.erase(std::remove_if(s_infos.begin(), s_infos.end(),
                                [&](const InfoSpecialist& e) { return e.loginHash == loginHashToDelete; }),
                                s_infos.end());
                            for (auto& dept : dept_members) {
                                dept.second.erase(std::remove(dept.second.begin(), dept.second.end(), loginHashToDelete),
                                    dept.second.end());
                            }
                            break;
                        case 2:
                            m_infos.erase(std::remove_if(m_infos.begin(), m_infos.end(),
                                [&](const InfoManager& e) { return e.loginHash == loginHashToDelete; }),
                                m_infos.end());
                            dept_members.erase(loginHashToDelete);
                            break;
                        }

                        g_users.erase(std::remove_if(g_users.begin(), g_users.end(),
                            [&](const UserRecord& u) { return u.loginHash == loginHashToDelete; }),
                            g_users.end());

                        WorkFile file;
                        file.saveUsers();
                        file.saveBasicInfos();
                        file.saveSpecialistInfos();
                        file.saveManagerInfos();
                        file.saveDeptMembers();

                        system("cls");
                        printBorder();
                        printCenteredInBox("Работник успешно уволен.");
                        printEmptyLineInBox();
                        printBorder();
                    }
                    else {
                        system("cls");
                        printBorder();
                        printCenteredInBox("Увольнение отменено.");
                        printEmptyLineInBox();
                        printBorder();
                    }
                }
            }
            printCentered("Нажмите любую клавишу...");
            _getch();
            break;
        }
        case 2: {
            system("cls");
            printBorder();
            printCenteredInBox("=== Поиск работника по имени ===");
            printEmptyLineInBox();
            printBorder();

            printCentered("Введите имя для поиска: ");
            std::string searchName;
            getline(std::cin >> std::ws, searchName);

            system("cls");
            printBorder();
            printCenteredInBox("=== Результаты поиска ===");
            printEmptyLineInBox();

            bool found = false;

            searchInContainer(b_infos, searchName, "Базовый персонал");
            searchInContainer(s_infos, searchName, "Специалист");
            searchInContainer(m_infos, searchName, "Менеджер");

            for (const auto& e : b_infos) if (containsName(e, searchName)) { found = true; break; }
            for (const auto& e : s_infos) if (containsName(e, searchName)) { found = true; break; }
            for (const auto& e : m_infos) if (containsName(e, searchName)) { found = true; break; }

            if (!found) {
                printCenteredInBox("Работники с именем '" + searchName + "' не найдены.");
                printEmptyLineInBox();
            }

            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            break;
        }
        case 3: {
            std::vector<std::string> type_options = {
                "Базовый персонал",
                "Специалист",
                "Менеджер",
                "Назад"
            };

            int type_choice = menu(type_options, "=== Сортировка по зарплате ===");
            if (type_choice == 3) break;

            switch (type_choice) {
            case 0:
                sortContainerBySalary(b_infos, "Базовый персонал");
                break;
            case 1:
                sortContainerBySalary(s_infos, "Специалисты");
                break;
            case 2:
                sortContainerBySalary(m_infos, "Менеджеры");
                break;
            }

            WorkFile file;
            switch (type_choice) {
            case 0: file.saveBasicInfos(); break;
            case 1: file.saveSpecialistInfos(); break;
            case 2: file.saveManagerInfos(); break;
            }
            break;
        }
        case 4: {
            system("cls");
            printBorder();
            printCenteredInBox("=== Опытные сотрудники ===");
            printEmptyLineInBox();

            filterExperiencedEmployees(b_infos, "Базовый персонал");
            filterExperiencedEmployees(s_infos, "Специалисты");
            filterExperiencedEmployees(m_infos, "Менеджеры");

            printCentered("Нажмите любую клавишу...");
            _getch();
            break;
        }
        case 5:
            generateReport();
            break;
        case 6:
            clearLastReport(); 
            return;
        }
    }
}