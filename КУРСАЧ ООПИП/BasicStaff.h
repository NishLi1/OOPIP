#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include <type_traits>
#include "UserBase.h"
#include "Table.h"

class BasicStaff : public UserBase {
    std::string WorkPlace;
    std::string inventory;

    template<typename T>
    class Task {
        std::vector<T> listTask;
    public:
        void add(const T& value) { listTask.push_back(value); }

        void show() const {
            using namespace TablePrinter;
            if (listTask.empty()) {
                printBorder();
                printCenteredInBox("=== Задач нет ===");
                printEmptyLineInBox();
                printBorder();
                return;
            }

            std::string header;
            if constexpr (std::is_same_v<T, std::string>) header = "Задачи на сегодня";
            else if constexpr (std::is_same_v<T, int>) header = "Количество оставшегося инвентаря";
            else if constexpr (std::is_same_v<T, double>) header = "Часы для каждой задачи";
            else header = std::string("Тип: ") + typeid(T).name();

            printBorder();
            printCenteredInBox("=== " + header + " ===");
            printEmptyLineInBox();

            for (size_t i = 0; i < listTask.size(); ++i) {
                std::ostringstream oss;
                if constexpr (std::is_same_v<T, std::string>) {
                    oss << listTask[i];
                }
                else {
                    oss << listTask[i];
                }
                printCenteredInBox(std::to_string(i + 1) + ") " + oss.str());
                printEmptyLineInBox();
            }
        }

        size_t size() const { return listTask.size(); }
    };

    Task<int> tasksInt;
    Task<std::string> tasksStr;
    Task<double> tasksDouble;

public:
    BasicStaff(const std::string& h);
    void showMenu() override;
    void showInfo() override;
    void addInfo() override;
    void editInfo() override;
    void deleteInfo() override;
    Role getType() override;
    void addTask();
    void showTask();
};
