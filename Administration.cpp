#include "Administration.h"
#include <conio.h>
#include <Windows.h>
#include <algorithm>
#include <cmath>

void Administration::generateReport() {
    system("cls");
    printBorder();
    printCenteredInBox("=== ГЕНЕРАЦИЯ ОТЧЕТА ===");
    printEmptyLineInBox();

    printBorder();
    printCenteredInBox("ОТЧЕТ ПО ВСЕМ СОТРУДНИКАМ");
    printCenteredInBox("Дата генерации: " + std::string(__DATE__) + " " + __TIME__);
    printEmptyLineInBox();

    printCenteredInBox("=== БАЗОВЫЙ ПЕРСОНАЛ ===");
    if (b_infos.empty()) {
        printCenteredInBox("Нет записей");
    }
    else {
        for (size_t i = 0; i < b_infos.size(); ++i) {
            std::stringstream ss;
            ss << "Сотрудник №" << (i + 1) << ":";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  ФИО: " << b_infos[i].name;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Возраст: " << b_infos[i].age;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Должность: " << b_infos[i].title;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Стаж: " << b_infos[i].WorkExp << " лет";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Зарплата: " << formatMoney(b_infos[i].salary);
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Место работы: " << b_infos[i].WorkPlace;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Инвентарь: " << b_infos[i].inventory;
            printCenteredInBox(ss.str());

            printEmptyLineInBox();
        }
    }

    printCenteredInBox("=== СПЕЦИАЛИСТЫ ===");
    if (s_infos.empty()) {
        printCenteredInBox("Нет записей");
    }
    else {
        for (size_t i = 0; i < s_infos.size(); ++i) {
            std::stringstream ss;
            ss << "Специалист №" << (i + 1) << ":";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  ФИО: " << s_infos[i].name;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Возраст: " << s_infos[i].age;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Должность: " << s_infos[i].title;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Стаж: " << s_infos[i].WorkExp << " лет";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Зарплата: " << formatMoney(s_infos[i].salary);
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Область специализации: " << s_infos[i].area;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Образование: " << s_infos[i].education;
            printCenteredInBox(ss.str());

            printEmptyLineInBox();
        }
    }

    printCenteredInBox("=== МЕНЕДЖЕРЫ ===");
    if (m_infos.empty()) {
        printCenteredInBox("Нет записей");
    }
    else {
        for (size_t i = 0; i < m_infos.size(); ++i) {
            std::stringstream ss;
            ss << "Менеджер №" << (i + 1) << ":";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  ФИО: " << m_infos[i].name;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Возраст: " << m_infos[i].age;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Должность: " << m_infos[i].title;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Стаж: " << m_infos[i].WorkExp << " лет";
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Зарплата: " << formatMoney(m_infos[i].salary);
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Количество подчиненных: " << m_infos[i].employee;
            printCenteredInBox(ss.str());

            ss.str(""); ss << "  Отдел: " << m_infos[i].department;
            printCenteredInBox(ss.str());

            printEmptyLineInBox();
        }
    }

    printCenteredInBox("=== СТАТИСТИКА ===");
    std::stringstream stats;
    stats << "Всего базового персонала: " << b_infos.size();
    printCenteredInBox(stats.str());

    stats.str(""); stats << "Всего специалистов: " << s_infos.size();
    printCenteredInBox(stats.str());

    stats.str(""); stats << "Всего менеджеров: " << m_infos.size();
    printCenteredInBox(stats.str());

    stats.str(""); stats << "Общее количество сотрудников: " << (b_infos.size() + s_infos.size() + m_infos.size());
    printCenteredInBox(stats.str());

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

        std::stringstream fileReport;
        fileReport << "ОТЧЕТ ПО ВСЕМ СОТРУДНИКАМ\n";
        fileReport << "Дата генерации: " << __DATE__ << " " << __TIME__ << "\n\n";

        fileReport << "=== БАЗОВЫЙ ПЕРСОНАЛ ===\n";
        if (b_infos.empty()) {
            fileReport << "Нет записей\n";
        }
        else {
            for (size_t i = 0; i < b_infos.size(); ++i) {
                fileReport << "Сотрудник №" << (i + 1) << ":\n";
                fileReport << "  ФИО: " << b_infos[i].name << "\n";
                fileReport << "  Возраст: " << b_infos[i].age << "\n";
                fileReport << "  Должность: " << b_infos[i].title << "\n";
                fileReport << "  Стаж: " << b_infos[i].WorkExp << " лет\n";
                fileReport << "  Зарплата: " << formatMoney(b_infos[i].salary) << "\n";
                fileReport << "  Место работы: " << b_infos[i].WorkPlace << "\n";
                fileReport << "  Инвентарь: " << b_infos[i].inventory << "\n\n";
            }
        }
        fileReport << "=== СПЕЦИАЛИСТЫ ===\n";
        if (s_infos.empty()) {
            fileReport << "Нет записей\n";
        }
        else {
            for (size_t i = 0; i < s_infos.size(); ++i) {
                fileReport << "Специалист №" << (i + 1) << ":\n";
                fileReport << "  ФИО: " << s_infos[i].name << "\n";
                fileReport << "  Возраст: " << s_infos[i].age << "\n";
                fileReport << "  Должность: " << s_infos[i].title << "\n";
                fileReport << "  Стаж: " << s_infos[i].WorkExp << " лет\n";
                fileReport << "  Зарплата: " << formatMoney(s_infos[i].salary) << "\n";
                fileReport << "  Область специализации: " << s_infos[i].area << "\n";
                fileReport << "  Образование: " << s_infos[i].education << "\n\n";
            }
        }

        fileReport << "=== МЕНЕДЖЕРЫ ===\n";
        if (m_infos.empty()) {
            fileReport << "Нет записей\n";
        }
        else {
            for (size_t i = 0; i < m_infos.size(); ++i) {
                fileReport << "Менеджер №" << (i + 1) << ":\n";
                fileReport << "  ФИО: " << m_infos[i].name << "\n";
                fileReport << "  Возраст: " << m_infos[i].age << "\n";
                fileReport << "  Должность: " << m_infos[i].title << "\n";
                fileReport << "  Стаж: " << m_infos[i].WorkExp << " лет\n";
                fileReport << "  Зарплата: " << formatMoney(m_infos[i].salary) << "\n";
                fileReport << "  Количество подчиненных: " << m_infos[i].employee << "\n";
                fileReport << "  Отдел: " << m_infos[i].department << "\n\n";
            }
        }

        fileReport << "=== СТАТИСТИКА ===\n";
        fileReport << "Всего базового персонала: " << b_infos.size() << "\n";
        fileReport << "Всего специалистов: " << s_infos.size() << "\n";
        fileReport << "Всего менеджеров: " << m_infos.size() << "\n";
        fileReport << "Общее количество сотрудников: " << (b_infos.size() + s_infos.size() + m_infos.size()) << "\n";

        std::ofstream file(filename);
        if (file.is_open()) {
            file << fileReport.str();
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

void Administration::AdminMenu() {
    std::vector<std::string> items = {
        "Просмотреть работников выборочно",
        "Уволить работника",
        "Найти работника по имени",
        "Отсортировать выбранных работников",
        "Вывести сотрудников, у которых стаж больше 5 лет и зарплата выше 2000 BYN",
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
            int count = 1;
            int choice = menu(type_worker, "=== Выберите тип сотрудников ===");
            switch (choice) {
            case 0: {
                system("cls");
                if (b_infos.empty()) {
                    printBorder();
                    printCenteredInBox("=== Ошибка ===");
                    printEmptyLineInBox();
                    printCenteredInBox("Нет базового персонала");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }

                printBorder();
                printCenteredInBox("=== Базовый персонал ===");
                printEmptyLineInBox();

                for (const auto& e : b_infos) {
                    printCenteredInBox(std::string("Сотрудник № ") + std::to_string(count++));
                    std::cout << e;
                }

                printBorder();
                printCentered("Нажмите любую клавишу...");
                _getch();
                break;
            }
            case 1: {
                system("cls");
                if (s_infos.empty()) {
                    printBorder();
                    printCenteredInBox("=== Ошибка ===");
                    printEmptyLineInBox();
                    printCenteredInBox("Нет специалистов");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }

                printBorder();
                printCenteredInBox("=== Специалисты ===");
                printEmptyLineInBox();

                int cnt = 1;
                for (const auto& e : s_infos) {
                    printCenteredInBox(std::string("Специалист № ") + std::to_string(cnt++));
                    std::cout << e;
                }

                printBorder();
                printCentered("Нажмите любую клавишу...");
                _getch();
                break;
            }
            case 2: {
                system("cls");
                if (m_infos.empty()) {
                    printBorder();
                    printCenteredInBox("=== Ошибка ===");
                    printEmptyLineInBox();
                    printCenteredInBox("Нет менеджеров");
                    printEmptyLineInBox();
                    printBorder();
                    printCentered("Нажмите любую клавишу...");
                    _getch();
                    break;
                }

                printBorder();
                printCenteredInBox("=== Менеджеры ===");
                printEmptyLineInBox();

                int cnt = 1;
                for (const auto& e : m_infos) {
                    printCenteredInBox(std::string("Менеджер № ") + std::to_string(cnt++));
                    std::cout << e;
                }

                printBorder();
                printCentered("Нажмите любую клавишу...");
                _getch();
                break;
            }
            case 3:
                break;
            default:
                break;
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

            for (const auto& e : b_infos) {
                if (e.name.find(searchName) != std::string::npos) {
                    found = true;
                    printCenteredInBox("[Базовый персонал] " + e.name + " | " + e.title + " | " + formatMoney(e.salary));
                }
            }

            for (const auto& e : s_infos) {
                if (e.name.find(searchName) != std::string::npos) {
                    found = true;
                    printCenteredInBox("[Специалист] " + e.name + " | " + e.title + " | " + formatMoney(e.salary));
                }
            }

            for (const auto& e : m_infos) {
                if (e.name.find(searchName) != std::string::npos) {
                    found = true;
                    printCenteredInBox("[Менеджер] " + e.name + " | " + e.title + " | " + formatMoney(e.salary));
                }
            }

            if (!found) {
                printCenteredInBox("Работники с именем '" + searchName + "' не найдены.");
            }

            printEmptyLineInBox();
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

            int type_choice = menu(type_options, "=== Сортировка по зарплате (qsort) ===");
            if (type_choice == 3) break;

            switch (type_choice) {
            case 0:
                if (b_infos.empty()) {
                    system("cls");
                    printBorder();
                    printCenteredInBox("Нет базового персонала для сортировки");
                    printEmptyLineInBox();
                    printBorder();
                    break;
                }
                qsort(b_infos.data(), b_infos.size(), sizeof(InfoBasicStaff), [](const void* a, const void* b) {
                    const InfoBasicStaff* ia = (const InfoBasicStaff*)a;
                    const InfoBasicStaff* ib = (const InfoBasicStaff*)b;
                    if (ia->salary < ib->salary) return -1;
                    if (ia->salary > ib->salary) return 1;
                    return 0;
                    });
                break;
            case 1:
                if (s_infos.empty()) {
                    system("cls");
                    printBorder();
                    printCenteredInBox("Нет специалистов для сортировки");
                    printEmptyLineInBox();
                    printBorder();
                    break;
                }
                qsort(s_infos.data(), s_infos.size(), sizeof(InfoSpecialist), [](const void* a, const void* b) {
                    const InfoSpecialist* ia = (const InfoSpecialist*)a;
                    const InfoSpecialist* ib = (const InfoSpecialist*)b;
                    if (ia->salary < ib->salary) return -1;
                    if (ia->salary > ib->salary) return 1;
                    return 0;
                    });
                break;
            case 2:
                if (m_infos.empty()) {
                    system("cls");
                    printBorder();
                    printCenteredInBox("Нет менеджеров для сортировки");
                    printEmptyLineInBox();
                    printBorder();
                    break;
                }
                qsort(m_infos.data(), m_infos.size(), sizeof(InfoManager), [](const void* a, const void* b) {
                    const InfoManager* ia = (const InfoManager*)a;
                    const InfoManager* ib = (const InfoManager*)b;
                    if (ia->salary < ib->salary) return -1;
                    if (ia->salary > ib->salary) return 1;
                    return 0;
                    });
                break;
            }

            WorkFile file;
            switch (type_choice) {
            case 0: file.saveBasicInfos(); break;
            case 1: file.saveSpecialistInfos(); break;
            case 2: file.saveManagerInfos(); break;
            }

            system("cls");
            printBorder();
            printCenteredInBox("Сортировка завершена успешно!");
            printEmptyLineInBox();
            printCenteredInBox("Данные отсортированы по зарплате (возрастание) с помощью qsort");
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            break;
        }
        case 4:
        {
            system("cls");
            printBorder();
            printCenteredInBox("=== Лучшие сотрудники ===");
            printEmptyLineInBox();
            printCenteredInBox("Базовый персонал");
            bool find = false;
            for (const auto& e : b_infos) {
                if (e.WorkExp >= 5.0 && e.salary >= 2000) {
                    std::string line = e.name + " | Стаж: " + std::to_string(e.WorkExp) + " | Зарплата: " + formatMoney(e.salary);
                    printCenteredInBox(line);
                    find = true;
                }
            }
            if (find == false) {
                printCenteredInBox("Нет таких сотрудников");
            }
            printEmptyLineInBox();
            printCenteredInBox("Специалисты");
            find = false;
            for (const auto& e : s_infos) {
                if (e.WorkExp >= 5.0 && e.salary >= 2000) {
                    std::string line = e.name + " | Стаж: " + std::to_string(e.WorkExp) + " | Зарплата: " + formatMoney(e.salary);
                    printCenteredInBox(line);
                    find = true;
                }
            }
            if (find == false) {
                printCenteredInBox("Нет таких сотрудников");
            }
            printEmptyLineInBox();
            printCenteredInBox("Менеджеры");
            find = false;
            for (const auto& e : m_infos) {
                if (e.WorkExp >= 5.0 && e.salary >= 2000) {
                    std::string line = e.name + " | Стаж: " + std::to_string(e.WorkExp) + " | Зарплата: " + formatMoney(e.salary);
                    printCenteredInBox(line);
                    find = true;
                }
            }
            if (find == false) {
                printCenteredInBox("Нет таких сотрудников");
            }
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            break;
        }
        case 5:
            generateReport();
            break;
        case 6:
            return;
        default:
            return;
        }
    }
}