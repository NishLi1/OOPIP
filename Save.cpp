#include "Save.h"
#include <fstream>

void WorkFile::writeString(std::ofstream& ofs, const std::string& s) {
    size_t n = s.size();
    ofs.write((char*)&n, sizeof(n));
    if (n) ofs.write(s.data(), n);
}

std::string WorkFile::readString(std::ifstream& ifs) {
    size_t n = 0;
    ifs.read((char*)&n, sizeof(n));
    std::string s;
    if (n) {
        s.resize(n);
        ifs.read(&s[0], n);
    }
    return s;
}

void WorkFile::saveUsers() {
    std::ofstream ofs("users.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) return;
    size_t count = g_users.size();
    ofs.write((char*)&count, sizeof(count));
    for (auto& u : g_users) {
        writeString(ofs, u.loginHash);
        writeString(ofs, u.passHash);
        ofs.write((char*)&u.role, sizeof(u.role));
    }
}

void WorkFile::loadUsers() {
    g_users.clear();
    std::ifstream ifs("users.dat", std::ios::binary);
    if (!ifs) return;
    size_t count = 0;
    ifs.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        UserRecord u;
        u.loginHash = readString(ifs);
        u.passHash = readString(ifs);
        ifs.read((char*)&u.role, sizeof(u.role));
        g_users.push_back(u);
    }
}

void WorkFile::saveBasicInfos() {
    std::ofstream ofs("basic_info.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) return;
    size_t count = b_infos.size();
    ofs.write((char*)&count, sizeof(count));
    for (auto& e : b_infos) {
        writeString(ofs, e.loginHash);
        writeString(ofs, e.name);
        ofs.write((char*)&e.age, sizeof(e.age));
        ofs.write((char*)&e.salary, sizeof(e.salary));
        ofs.write((char*)&e.WorkExp, sizeof(e.WorkExp));
        writeString(ofs, e.title);
        writeString(ofs, e.WorkPlace);
        writeString(ofs, e.inventory);
    }
}

void WorkFile::loadBasicInfos() {
    b_infos.clear();
    std::ifstream ifs("basic_info.dat", std::ios::binary);
    if (!ifs) return;
    size_t count = 0;
    ifs.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        InfoBasicStaff e;
        e.loginHash = readString(ifs);
        e.name = readString(ifs);
        ifs.read((char*)&e.age, sizeof(e.age));
        ifs.read((char*)&e.salary, sizeof(e.salary));
        ifs.read((char*)&e.WorkExp, sizeof(e.WorkExp));
        e.title = readString(ifs);
        e.WorkPlace = readString(ifs);
        e.inventory = readString(ifs);
        b_infos.push_back(e);
    }
}

void WorkFile::saveSpecialistInfos() {
    std::ofstream ofs("specialist_info.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) return;
    size_t count = s_infos.size();
    ofs.write((char*)&count, sizeof(count));
    for (auto& e : s_infos) {
        writeString(ofs, e.loginHash);
        writeString(ofs, e.name);
        ofs.write((char*)&e.age, sizeof(e.age));
        ofs.write((char*)&e.salary, sizeof(e.salary));
        ofs.write((char*)&e.WorkExp, sizeof(e.WorkExp));
        writeString(ofs, e.title);
        writeString(ofs, e.area);
        writeString(ofs, e.education);
    }
}

void WorkFile::loadSpecialistInfos() {
    s_infos.clear();
    std::ifstream ifs("specialist_info.dat", std::ios::binary);
    if (!ifs) return;
    size_t count = 0;
    ifs.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        InfoSpecialist e;
        e.loginHash = readString(ifs);
        e.name = readString(ifs);
        ifs.read((char*)&e.age, sizeof(e.age));
        ifs.read((char*)&e.salary, sizeof(e.salary));
        ifs.read((char*)&e.WorkExp, sizeof(e.WorkExp));
        e.title = readString(ifs);
        e.area = readString(ifs);
        e.education = readString(ifs);
        s_infos.push_back(e);
    }
}

void WorkFile::saveManagerInfos() {
    std::ofstream ofs("manager_info.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) return;
    size_t count = m_infos.size();
    ofs.write((char*)&count, sizeof(count));
    for (auto& e : m_infos) {
        writeString(ofs, e.loginHash);
        writeString(ofs, e.name);
        ofs.write((char*)&e.age, sizeof(e.age));
        ofs.write((char*)&e.salary, sizeof(e.salary));
        ofs.write((char*)&e.WorkExp, sizeof(e.WorkExp));
        writeString(ofs, e.title);
        ofs.write((char*)&e.employee, sizeof(e.employee));
        writeString(ofs, e.department);
    }
}

void WorkFile::loadManagerInfos() {
    m_infos.clear();
    std::ifstream ifs("manager_info.dat", std::ios::binary);
    if (!ifs) return;
    size_t count = 0;
    ifs.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        InfoManager e;
        e.loginHash = readString(ifs);
        e.name = readString(ifs);
        ifs.read((char*)&e.age, sizeof(e.age));
        ifs.read((char*)&e.salary, sizeof(e.salary));
        ifs.read((char*)&e.WorkExp, sizeof(e.WorkExp));
        e.title = readString(ifs);
        ifs.read((char*)&e.employee, sizeof(e.employee));
        e.department = readString(ifs);
        m_infos.push_back(e);
    }
}

void WorkFile::saveDeptMembers() {
    std::ofstream ofs("dept_members.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) return;
    size_t mapCount = dept_members.size();
    ofs.write((char*)&mapCount, sizeof(mapCount));
    for (auto& p : dept_members) {
        writeString(ofs, p.first);
        size_t cnt = p.second.size();
        ofs.write((char*)&cnt, sizeof(cnt));
        for (auto& mem : p.second) writeString(ofs, mem);
    }
}

void WorkFile::loadDeptMembers() {
    dept_members.clear();
    std::ifstream ifs("dept_members.dat", std::ios::binary);
    if (!ifs) return;
    size_t mapCount = 0;
    ifs.read((char*)&mapCount, sizeof(mapCount));
    for (size_t i = 0; i < mapCount; ++i) {
        std::string key = readString(ifs);
        size_t cnt = 0;
        ifs.read((char*)&cnt, sizeof(cnt));
        std::vector<std::string> vec;
        for (size_t j = 0; j < cnt; ++j) vec.push_back(readString(ifs));
        dept_members[key] = vec;
    }
}