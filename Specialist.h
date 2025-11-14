#pragma once
#include "UserBase.h"
#include <vector>
#include <string>

class Specialist : public UserBase {
    std::string area;
    std::string education;
    std::vector<std::string> tasks;
    std::vector<bool> completed;

    size_t getVisibleLength(const std::string& str);
    std::string centerTextWithANSISupport(const std::string& text, int width);
    void addTaskInternal(const std::string& task);
    int chooseTaskIndex(const std::string& title);

public:
    Specialist(const std::string& h);
    void showMenu();
    void showInfo() override;
    void addInfo() override;
    void editInfo() override;
    void deleteInfo() override;
    void showAllTasks();
    void addTaskMenu();
    void markCompletedMenu();
    Role getType() override;
};