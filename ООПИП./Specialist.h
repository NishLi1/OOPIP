#pragma once
#include "UserBase.h"
#include <vector>
#include <string>
#include <memory>

class Specialist : public UserBase {
private:
    std::string area;
    std::string education;
    std::unique_ptr<std::string[]> tasks; 
    std::unique_ptr<bool[]> completed;   
    size_t taskCount = 0;
    size_t taskCapacity = 0;

    size_t getVisibleLength(const std::string& str);
    std::string centerTextWithANSISupport(const std::string& text, int width);
    void addTaskInternal(const std::string& task);
    int chooseTaskIndex(const std::string& title);
    void resizeTaskArrays(size_t newCapacity);

public:
    Specialist(const std::string& h);
    ~Specialist(); 
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