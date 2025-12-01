#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Table.h"
#include "Role.h"
#include "Save.h"
#include "Menu.h"
#include "Authorization.h"
#include "Administration.h"

using namespace TablePrinter;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::vector<std::string> mainMenu = { "Войти", "Зарегистрироваться", "Вся информация системы (для руководителя, без входа)", "Выход" };
    Authorization auth;
    Administration admin;
    WorkFile file;

    file.loadUsers();
    file.loadBasicInfos();
    file.loadSpecialistInfos();
    file.loadManagerInfos();
    file.loadDeptMembers();

    while (true) {
        int ch = menu(mainMenu, "=== Система управления персоналом ===");
        switch (ch) {
        case 0: auth.doLogin(); break;
        case 1: auth.doRegister(); break;
        case 2: admin.AdminMenu(); break;
        case 3:
            system("cls");
            printBorder();
            printCenteredInBox("Выход");
            printEmptyLineInBox();
            printBorder();
            return 0;
        }
    }
    return 0;
}