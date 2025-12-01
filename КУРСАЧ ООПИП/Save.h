#pragma once
#include "Role.h"
#include <fstream>

class WorkFile {
    static void writeString(std::ofstream& ofs, const std::string& s);
    static std::string readString(std::ifstream& ifs);
public:
    static void saveUsers();
    static void loadUsers();
    static void saveBasicInfos();
    static void loadBasicInfos();
    static void saveSpecialistInfos();
    static void loadSpecialistInfos();
    static void saveManagerInfos();
    static void loadManagerInfos();
    static void saveDeptMembers();
    static void loadDeptMembers();
};