#pragma once
#include "UserBase.h"
#include <string>

class Manager : public UserBase {
    int employee;
    std::string department;
public:
    Manager(const std::string& h);
    void showMenu();
    void showInfo() override;
    void addInfo() override;
    void editInfo() override;
    void deleteInfo() override;
    void Sdepart();
    void showSpec();
    void Salary();
    Role getType() override;
};