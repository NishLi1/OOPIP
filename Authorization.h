#pragma once
#include "Role.h"
#include "Save.h"
#include "Table.h"
#include "BasicStaff.h"
#include "Specialist.h"
#include "Manager.h"
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>

class Authorization {
    WorkFile save_us;

    std::string inputPasswordHidden();
    static std::string getHash(const std::string& input);
    std::string roleToString(Role r);

public:
    void doRegister();
    void doLogin();
};