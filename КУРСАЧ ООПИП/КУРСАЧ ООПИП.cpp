#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Table.h" // Файл для вывода данных
#include "Role.h" // Файл для разделения и реализации ролей
#include "Save.h" // Файл для записи и выгрузки данных в файле
#include "Menu.h" // Файл для меню и выбор через стрелочки
#include "Authorization.h" // Файл для входа и регистрации в систему
#include "Administration.h" // Файл с меню руководителя без входа
//Собственное пространстов имён 
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
    file.loadRecommendation();

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