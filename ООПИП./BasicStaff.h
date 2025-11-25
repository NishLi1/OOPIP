#pragma once
#include "UserBase.h"

class BasicStaff : public UserBase {
    std::string WorkPlace;
    std::string inventory;
public:
    BasicStaff(const std::string& h);
    void showMenu();
    void showInfo() override;
    void addInfo() override;
    void editInfo() override;
    void deleteInfo() override;
    Role getType() override;
};