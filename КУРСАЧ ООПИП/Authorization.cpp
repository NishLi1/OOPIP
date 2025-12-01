#include "Authorization.h"
#include "Menu.h"
#include <functional>
#include <deque>

using namespace TablePrinter;

WorkFile Authorization::save_us;

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

std::string Authorization::getHash(const std::string& input) {
    const std::string salt = "HR_salt";
    std::string salted = input + salt;
    std::hash<std::string> hasher;
    size_t hv = hasher(salted);
    std::stringstream ss;
    ss << std::hex << hv;
    return ss.str();
}

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
    for (auto& u : g_users) if (u.loginHash == loginHash) {
        system("cls");
        printBorder();
        printCenteredInBox("Такой пользователь уже существует (по хэшу логина).");
        printEmptyLineInBox();
        printBorder();
        printCentered("Нажмите любую клавишу...");
        _getch();
        return;
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
    int r = menu(roles, "Выберите роль:");
    Role role = static_cast<Role>(r);
    UserRecord ur{ loginHash, passHash, role };
    g_users.push_back(ur);
    save_us.saveUsers();
    system("cls");
    printBorder();
    printCenteredInBox("Регистрация успешна.");
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