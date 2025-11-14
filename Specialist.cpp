#include "Specialist.h"
#include "Table.h"
#include "Menu.h"
#include <conio.h>
#include <Windows.h>
#include <algorithm>

Specialist::Specialist(const std::string& h) : UserBase(h) {}

size_t Specialist::getVisibleLength(const std::string& str) {
    size_t len = 0;
    bool inEscape = false;
    for (char c : str) {
        if (c == '\033') { inEscape = true; continue; }
        if (inEscape && c == 'm') { inEscape = false; continue; }
        if (!inEscape) ++len;
    }
    return len;
}

std::string Specialist::centerTextWithANSISupport(const std::string& text, int width) {
    size_t visibleLen = getVisibleLength(text);
    int totalPadding = width - (int)visibleLen;
    if (totalPadding <= 0) return text;
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

void Specialist::addTaskInternal(const std::string& task) {
    tasks.push_back(task);
    completed.push_back(false);
}

int Specialist::chooseTaskIndex(const std::string& title) {
    if (tasks.empty()) return -1;
    int idx = 0;
    while (true) {
        system("cls");
        printBorder();
        printCenteredInBox("=== " + title + " ===");
        printEmptyLineInBox();

        for (size_t i = 0; i < tasks.size(); ++i) {
            std::string text = std::to_string(i + 1) + ". " + tasks[i];
            if (completed[i]) {
                text = std::to_string(i + 1) + ". " + "\033[9m" + tasks[i] + "\033[0m";
            }
            std::string centered = centerTextWithANSISupport(text, WIDTH - 4);

            if ((int)i == idx) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                std::cout << "| " << centered << " |" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else {
                std::cout << "| " << centered << " |" << std::endl;
            }
        }

        printEmptyLineInBox();
        printBorder();

        int k = _getch();
        if (k == 224) {
            int k2 = _getch();
            if (k2 == 72) { if (idx > 0) --idx; }
            else if (k2 == 80) { if (idx + 1 < (int)tasks.size()) ++idx; }
        }
        else if (k == 13) {
            return idx;
        }
        else if (k == 27) {
            return -1;
        }
    }
}

void Specialist::showMenu() {
    std::vector<std::string> items = {
        "Посмотреть общую информацию",
        "Добавить общую информацию",
        "Редактировать общую информацию",
        "Удалить общую информацию",
        "Добавить задачу на доску",
        "Посмотреть задачи на доске",
        "Отметить задачу как выполненную / снять отметку",
        "Выйти"
    };
    while (true) {
        int ch = menu(items, "=== Меню: Специалист ===");
        switch (ch) {
        case 0: showInfo(); break;
        case 1: addInfo(); break;
        case 2: editInfo(); break;
        case 3: deleteInfo(); break;
        case 4: addTaskMenu(); break;
        case 5: showAllTasks(); break;
        case 6: markCompletedMenu(); break;
        case 7: return;
        }
    }
}

void Specialist::showInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Ваша информация ===");
    printEmptyLineInBox();

    bool found = false;
    for (const auto& e : s_infos) {
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

void Specialist::addInfo() {
    for (const auto& e : s_infos) {
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

    InfoSpecialist e;
    e.loginHash = loginHash;
    std::cin >> e;

    s_infos.push_back(e);
    save.saveSpecialistInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно сохранена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Specialist::editInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Редактирование информации ===");
    printEmptyLineInBox();

    int idx = -1;
    for (size_t i = 0; i < s_infos.size(); ++i) {
        if (s_infos[i].loginHash == loginHash) { idx = (int)i; break; }
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

    InfoSpecialist temp = s_infos[idx];

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
            printCentered(("Зарплата (старое: " + std::to_string(temp.salary) + "): "));
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

    printCentered(("Область специализации (старое: " + temp.area + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.area = tmp;

    printCentered(("Образование (старое: " + temp.education + "): "));
    getline(std::cin, tmp);
    if (!tmp.empty()) temp.education = tmp;

    s_infos[idx] = temp;
    save.saveSpecialistInfos();

    system("cls");
    printBorder();
    printCenteredInBox("Информация успешно обновлена.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Specialist::deleteInfo()  {
    system("cls");
    printBorder();
    printCenteredInBox("=== Удаление информации ===");
    printEmptyLineInBox();

    auto it = std::find_if(s_infos.begin(), s_infos.end(),
        [&](const InfoSpecialist& e) { return e.loginHash == loginHash; });

    if (it == s_infos.end()) {
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
        std::string specHash = it->loginHash;
        s_infos.erase(it);
        save.saveSpecialistInfos();
        for (auto& p : dept_members) {
            auto& vec = p.second;
            auto jt = std::find(vec.begin(), vec.end(), specHash);
            if (jt != vec.end()) {
                vec.erase(jt);
            }
        }
        save.saveDeptMembers();
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

void Specialist::showAllTasks() {
    system("cls");
    printBorder();
    printCenteredInBox("=== Список задач ===");
    printEmptyLineInBox();

    if (tasks.empty()) {
        printCenteredInBox("(Задачи отсутствуют)");
    }
    else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::string taskText = std::to_string(i + 1) + ". " + tasks[i];
            if (completed[i]) {
                taskText = std::to_string(i + 1) + ". " + "\033[9m" + tasks[i] + "\033[0m";
            }
            std::string centeredLine = centerTextWithANSISupport(taskText, WIDTH - 4);
            std::cout << "| " << centeredLine << " |" << std::endl;
        }
    }

    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Specialist::addTaskMenu() {
    system("cls");
    printBorder();
    printCenteredInBox("=== Добавление задачи ===");
    printEmptyLineInBox();
    printBorder();

    printCentered("Введите задачу: ");
    std::string task;
    getline(std::cin >> std::ws, task);

    if (!task.empty()) {
        addTaskInternal(task);

        system("cls");
        printBorder();
        printCenteredInBox("=== Успех ===");
        printEmptyLineInBox();
        printCenteredInBox("Задача добавлена ");
        printEmptyLineInBox();
        printBorder();
    }
    else {
        system("cls");
        printBorder();
        printCenteredInBox("=== Ошибка ===");
        printEmptyLineInBox();
        printCenteredInBox("Задача не может быть пустой!");
        printEmptyLineInBox();
        printBorder();
    }

    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Specialist::markCompletedMenu() {
    if (tasks.empty()) {
        system("cls");
        printBorder();
        printCenteredInBox("=== Ошибка ===");
        printEmptyLineInBox();
        printCenteredInBox("Нет задач для отметки!");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    int sel = chooseTaskIndex("Отметить задачу как выполненную / снять отметку");
    if (sel == -1) {
        system("cls");
        printBorder();
        printCenteredInBox("Отмена.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    if (sel >= 0 && sel < (int)tasks.size()) {
        completed[sel] = !completed[sel];

        system("cls");
        printBorder();
        if (completed[sel]) printCenteredInBox("Задача отмечена как выполненная.");
        else printCenteredInBox("Отметка снята. Задача снова активна.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
    }
}

Role Specialist::getType()  {
    return Role::specialist;
}