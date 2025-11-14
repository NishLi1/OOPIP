#pragma once
#include "Role.h"
#include <fstream>

class WorkFile {
    void writeString(std::ofstream& ofs, const std::string& s);
    std::string readString(std::ifstream& ifs);
public:
    void saveUsers();
    void loadUsers();
    void saveBasicInfos();
    void loadBasicInfos();
    void saveSpecialistInfos();
    void loadSpecialistInfos();
    void saveManagerInfos();
    void loadManagerInfos();
    void saveDeptMembers();
    void loadDeptMembers();
};