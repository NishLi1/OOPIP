#include "Authorization.h"
#include "Menu.h"
#include <deque>

using namespace TablePrinter;

WorkFile Authorization::save_us;
// Функция ввода пароля 
std::string Authorization::inputPasswordHidden() {
    std::string pass;
    while (true) {
        int k = _getch();
        if (k == 13) break;
        if (k == 8) {
            if (!pass.empty()) {
                pass.pop_back();
                std::cout << "\b \b";
            }
            continue;
        }
        if (k == 0 || k == 224) { _getch(); continue; }
        char src[2] = { static_cast<char>(k), '\0' };
        char dst[2] = { 0, '\0' };
        OemToCharA(src, dst);
        pass.push_back(dst[0]);
        std::cout << '*';
    }
    std::cout << '\n';
    return pass;
}
// Функция хеширование
std::string Authorization::getHash(const std::string& input) {
    const std::string salt = "HR_salt";
    std::string salted = input + salt;
    std::hash<std::string> hasher;
    size_t hv = hasher(salted);
    std::stringstream ss;
    ss << std::hex << hv;
    return ss.str();
}
// Функция определения роли через enum
std::string Authorization::roleToString(Role r) {
    switch (r) {
    case basic: return "Базовый персонал";
    case specialist: return "Специалист";
    case manager: return "Менеджер";
    default: return "Неизвестно";
    }
}

void Authorization::doRegister() {
    system("cls");
    printBorder();
    printCenteredInBox("=== Регистрация ===");
    printEmptyLineInBox();
    printBorder();

    std::string login;
    while (true) {
        printCentered("Логин: ");
        getline(std::cin >> std::ws, login);
        if (login.empty()) {
            system("cls");
            printBorder();
            printCenteredInBox("Логин не может быть пустым. Повторите ввод.");
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            system("cls");
            printBorder();
            printCenteredInBox("=== Регистрация ===");
            printEmptyLineInBox();
            printBorder();
            continue;
        }
        break;
    }

    std::string loginHash = getHash(login);


    for (auto& u : g_users) {
        if (u.loginHash == loginHash) {
            system("cls");
            printBorder();
            printCenteredInBox("Пользователь с таким логином уже существует.");
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();
            return;
        }
    }

    printCentered("Пароль: ");
    std::string pass = inputPasswordHidden();
    if (pass.empty()) {
        system("cls");
        printBorder();
        printCenteredInBox("Пароль не может быть пустым. Отмена регистрации.");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
    }

    std::string passHash = getHash(pass);

    std::vector<std::string> roles = { "Базовый персонал", "Специалист", "Менеджер" };
    int r = menu(roles, "Выберите должность:");
    Role role = static_cast<Role>(r);

    system("cls");
    printBorder();
    printCenteredInBox("=== Дополнительная информация ===");
    printEmptyLineInBox();
    printBorder();

    printCentered("ФИО: ");
    std::string name;
    getline(std::cin >> std::ws, name);

    printCentered("Образование: ");
    std::string education;
    getline(std::cin, education);

    double experience = 0;
    while (true) {
        try {
            printCentered("Опыт работы (лет): ");
            std::string expStr;
            getline(std::cin, expStr);
            experience = std::stod(expStr);
            if (experience < 0) throw std::out_of_range("Опыт не может быть отрицательным");
            break;
        }
        catch (const std::exception& e) {
            printCentered("Ошибка: введите корректный опыт работы");
            std::cin.ignore();
        }
    }

    UserRecord newUser;
    newUser.loginHash = loginHash;
    newUser.passHash = passHash;
    newUser.role = role;
    newUser.approved = (role == manager);
    newUser.name = name;
    newUser.education = education;
    newUser.experience = experience;

    g_users.push_back(newUser);
    save_us.saveUsers();

    system("cls");
    printBorder();

    if (role == manager) {
        printCenteredInBox("Регистрация менеджера успешно завершена!");
        printEmptyLineInBox();
        printCenteredInBox("Вы можете войти в систему сразу.");
    }
    else {
        printCenteredInBox("Заявка отправлена на рассмотрение.");
        printEmptyLineInBox();
        printCenteredInBox("Ожидайте одобрения менеджером.");
    }

    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}

void Authorization::doLogin() {
    system("cls");
    printBorder();
    printCenteredInBox("=== Вход ===");
    printEmptyLineInBox();
    printBorder();
    printCentered("Логин: ");
    std::string login;
    getline(std::cin >> std::ws, login);
    printCentered("Пароль: ");
    std::string pass = inputPasswordHidden();

    std::string loginHash = getHash(login);
    std::string passHash = getHash(pass);

    for (auto& u : g_users) {
        if (u.loginHash == loginHash && u.passHash == passHash) {
            if (!u.approved) {
                system("cls");
                printBorder();
                printCenteredInBox("Ваша заявка на рассмотрении.");
                printEmptyLineInBox();
                printCenteredInBox("Ожидайте ответа менеджера.");
                printEmptyLineInBox();
                printBorder();
                printCentered("Нажмите любую клавишу...");
                _getch();
                return;
            }

            system("cls");
            printBorder();
            printCenteredInBox("Успешный вход. Роль: " + roleToString(u.role));
            printEmptyLineInBox();
            printBorder();
            printCentered("Нажмите любую клавишу...");
            _getch();

            if (u.role == basic) {
                BasicStaff bs(loginHash);
                bs.showMenu();
            }
            else if (u.role == specialist) {
                Specialist sp(loginHash);
                sp.showMenu();
            }
            else if (u.role == manager) {
                Manager mg(loginHash);
                mg.showMenu();
            }
            return;
        }
    }

    system("cls");
    printBorder();
    printCenteredInBox("Неверный логин или пароль.");
    printEmptyLineInBox();
    printBorder();
    printCentered("Нажмите любую клавишу...");
    _getch();
}