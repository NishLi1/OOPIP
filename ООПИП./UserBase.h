#pragma once
#include "Role.h"
#include "Save.h"
#include <string>

class UserBase {
protected:
    std::string loginHash;
    std::string name;
    int age;
    double salary;
    double WorkExp;
    std::string title;
    static WorkFile save;
public:
    UserBase(const std::string& loginHash = "");
    virtual void showInfo() = 0;
    virtual void addInfo() = 0;
    virtual void editInfo() = 0;
    virtual void deleteInfo() = 0;
    virtual Role getType() = 0;
};