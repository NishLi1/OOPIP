#include "Manager.h"
#include "Table.h"
#include "Menu.h"
#include <conio.h>
#include <Windows.h>
#include <algorithm>
#include <cmath>

Manager::Manager(const std::string& h) : UserBase(h) {}

void Manager::showMenu() {
    std::vector<std::string> items = {
        "Посмотреть общую информацию",
        "Добавить общую информацию",
        "Редактировать общую информацию",
        "Удалить общую информацию",
        "Добавить специалиста в отдел",
        "Посмотреть подчинённых",
        "Высчитать зарплату сотрудника в год и отпускные(500 BYN - 1 выходной)",
        "Выйти"
    };
    while (true) {
        int ch = menu(items, "=== Меню: Менеджер ===");
        switch (ch) {
        case 0: showInfo(); break;
        case 1: addInfo(); break;
        case 2: editInfo(); break;
        case 3: deleteInfo(); break;
        case 4: Sdepart(); break;
        case 5: showSpec(); break;
        case 6: Salary(); break;
        case 7: return;
        }
    }
}

void Manager::showInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Ваша информация ===");
    printEmptyLineInBox();

    bool found = false;
    for (const auto& e : m_infos) {
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

void Manager::addInfo()  {
    for (const auto& e : m_infos) {
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

    InfoManager e;
    e.loginHash = loginHash;
    std::cin >> e;

    m_infos.push_back(e);
    save.saveManagerInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно сохранена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Manager::editInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Редактирование информации ===");
    printEmptyLineInBox();

    int idx = -1;
    for (size_t i = 0; i < m_infos.size(); ++i) {
        if (m_infos[i].loginHash == loginHash) { idx = (int)i; break; }
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

    InfoManager temp = m_infos[idx];

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

    while (true) {
        try {
            printCentered(("Количество подчиненных (старое: " + std::to_string(temp.employee) + "): "));
            getline(std::cin, tmp);
            if (!tmp.empty()) {
                temp.employee = std::stoi(tmp);
                if (temp.employee < 0) throw std::out_of_range("Количество подчиненных не может быть отрицательным");
            }
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректное количество подчиненных");
        }
    }

    printCentered(("Отдел (старое: " + temp.department + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.department = tmp;

    m_infos[idx] = temp;
    save.saveManagerInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно обновлена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Manager::deleteInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Удаление информации ===");
    printEmptyLineInBox();

    auto it = std::find_if(m_infos.begin(), m_infos.end(),
        [&](const InfoManager& e) { return e.loginHash == loginHash; });

    if (it == m_infos.end()) {
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
        dept_members.erase(loginHash);
        save.saveDeptMembers();

        m_infos.erase(it);
        save.saveManagerInfos();

        for (auto& mgr : m_infos) {
            auto it2 = dept_members.find(mgr.loginHash);
            if (it2 != dept_members.end()) mgr.employee = (int)it2->second.size();
        }
        save.saveManagerInfos();

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

void Manager::Sdepart() {
    if (s_infos.empty()) {
        system("cls");
        printBorder();
        printCenteredInBox("=== Ошибка ===");
        printEmptyLineInBox();
        printCenteredInBox("Нет доступных специалистов для добавления.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    std::string myDepartment;
    for (const auto& mm : m_infos) {
        if (mm.loginHash == loginHash) { myDepartment = mm.department; break; }
    }

    int idx = 0;
    while (true) {
        system("cls");
        printBorder();
        printCenteredInBox("=== Выберите специалиста для добавления в отдел ===");
        printEmptyLineInBox();
        for (size_t i = 0; i < s_infos.size(); ++i) {
            std::string mark = " ";
            auto it = dept_members.find(loginHash);
            if (it != dept_members.end()) {
                if (std::find(it->second.begin(), it->second.end(), s_infos[i].loginHash) != it->second.end()) {
                    mark = "*";
                }
            }
            else if (!myDepartment.empty()) {
                auto it2 = dept_members.find(myDepartment);
                if (it2 != dept_members.end() && std::find(it2->second.begin(), it2->second.end(), s_infos[i].loginHash) != it2->second.end()) {
                    mark = "*";
                }
            }
            std::string line = std::string(mark) + " " + std::to_string(i + 1) + ". " + s_infos[i].name + " | " + s_infos[i].title;
            if ((int)i == idx) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                printCenteredInBox(line);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else {
                printCenteredInBox(line);
            }
        }
        printEmptyLineInBox();
        printCenteredInBox("Enter - добавить, Esc - выйти. * отмечены уже добавленные.");
        printEmptyLineInBox();
        printBorder();

        int k = _getch();
        if (k == 224) {
            int k2 = _getch();
            if (k2 == 72) { if (idx > 0) --idx; }
            else if (k2 == 80) { if (idx + 1 < (int)s_infos.size()) ++idx; }
        }
        else if (k == 13) {
            std::string specHash = s_infos[idx].loginHash;

            auto& vecLogin = dept_members[loginHash];
            if (std::find(vecLogin.begin(), vecLogin.end(), specHash) != vecLogin.end()) {
                system("cls");
                printBorder();
                printCenteredInBox("Специалист уже находится в вашем отделе.");
                printEmptyLineInBox();
                printBorder();
                printCentered("Нажмите любую клавишу...");
                _getch();
                return;
            }

            vecLogin.push_back(specHash);

            if (!myDepartment.empty()) {
                auto& vecDep = dept_members[myDepartment];
                if (std::find(vecDep.begin(), vecDep.end(), specHash) == vecDep.end()) {
                    vecDep.push_back(specHash);
                }
            }

            for (auto& mm : m_infos) {
                if (mm.loginHash == loginHash) {
                    mm.employee = (int)dept_members[loginHash].size();
                    break;
                }
            }

            save.saveDeptMembers();
            save.saveManagerInfos();

            system("cls");
            printBorder();
            printCenteredInBox("Специалист добавлен в отдел.");
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            return;
        }
        else if (k == 27) {
            return;
        }
    }
}

void Manager::showSpec() {
    system("cls");
    printBorder();
    printCenteredInBox("Подчинённые (список специалистов в отделе):");
    printEmptyLineInBox();

    std::vector<std::string> members;
    auto itLogin = dept_members.find(loginHash);
    if (itLogin != dept_members.end()) members = itLogin->second;

    if (members.empty()) {
        std::string myDepartment;
        for (const auto& mm : m_infos) {
            if (mm.loginHash == loginHash) { myDepartment = mm.department; break; }
        }
        if (!myDepartment.empty()) {
            auto itDep = dept_members.find(myDepartment);
            if (itDep != dept_members.end()) members = itDep->second;
        }
    }

    if (members.empty()) {
        printCenteredInBox("(В вашем отделе нет специалистов)");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    int cnt = 1;
    for (const auto& specHash : members) {
        auto sit = std::find_if(s_infos.begin(), s_infos.end(), [&](const InfoSpecialist& si) { return si.loginHash == specHash; });
        if (sit != s_infos.end()) {
            printCenteredInBox("Специалист № " + std::to_string(cnt++));
            printCenteredInBox("ФИО: " + sit->name + " | Должность: " + sit->title + " | Зарплата: " + formatMoney(sit->salary));
            printEmptyLineInBox();
        }
        else {
            printCenteredInBox("Специалист № " + std::to_string(cnt++) + " (удалён или не найден)");
            printEmptyLineInBox();
        }
    }
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Manager::Salary() {
    system("cls");
    printBorder();
    printCenteredInBox("=== Расчёт зарплаты и отпускных (оценочно) ===");
    printEmptyLineInBox();

    if (s_infos.empty() && b_infos.empty() && m_infos.empty()) {
        printCenteredInBox("(Нет сотрудников для расчёта)");
    }
    else {
        if (!b_infos.empty()) {
            printCenteredInBox("--- Базовый персонал ---");
            for (const auto& e : b_infos) {
                double yearly = e.salary * 12.0;
                int paidDays = static_cast<int>(std::floor(yearly / 500.0));
                std::string line1 = e.name + " | Ставка: " + formatMoney(e.salary) + " | Годовой доход: " + formatMoney(yearly);
                std::string line2 = "Стаж: " + std::to_string(e.WorkExp) + " лет | Оценочно оплачиваемые выходные: " + std::to_string(paidDays);
                printCenteredInBox(line1);
                printCenteredInBox(line2);
                printEmptyLineInBox();
            }
        }
        if (!s_infos.empty()) {
            printCenteredInBox("--- Специалисты ---");
            for (const auto& e : s_infos) {
                double yearly = e.salary * 12.0;
                int paidDays = static_cast<int>(std::floor(yearly / 500.0));
                std::string line1 = e.name + " | Ставка: " + formatMoney(e.salary) + " | Годовой доход: " + formatMoney(yearly);
                std::string line2 = "Стаж: " + std::to_string(e.WorkExp) + " лет | Оценочно оплачиваемые выходные: " + std::to_string(paidDays);
                printCenteredInBox(line1);
                printCenteredInBox(line2);
                printEmptyLineInBox();
            }
        }
        if (!m_infos.empty()) {
            printCenteredInBox("--- Менеджеры ---");
            for (const auto& e : m_infos) {
                double yearly = e.salary * 12.0;
                int paidDays = static_cast<int>(std::floor(yearly / 500.0));
                std::string line1 = e.name + " | Ставка: " + formatMoney(e.salary) + " | Годовой доход: " + formatMoney(yearly);
                std::string line2 = "Стаж: " + std::to_string(e.WorkExp) + " лет | Оценочно оплачиваемые выходные: " + std::to_string(paidDays);
                printCenteredInBox(line1);
                printCenteredInBox(line2);
                printEmptyLineInBox();
            }
        }
    }

    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

Role Manager::getType()  {
    return Role::manager;
}