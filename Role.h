#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum Role { basic, specialist, manager };

struct UserRecord {
    std::string loginHash;
    std::string passHash;
    Role role;
};

struct InfoBasicStaff {
    std::string loginHash;
    std::string name;
    int age;
    double salary;
    double WorkExp;
    std::string title;
    std::string WorkPlace;
    std::string inventory;

    friend std::ostream& operator<<(std::ostream& os, const InfoBasicStaff& info);
    friend std::istream& operator>>(std::istream& is, InfoBasicStaff& info);
};

struct InfoSpecialist {
    std::string loginHash;
    std::string name;
    int age;
    double salary;
    double WorkExp;
    std::string title;
    std::string area;
    std::string education;

    friend std::ostream& operator<<(std::ostream& os, const InfoSpecialist& info);
    friend std::istream& operator>>(std::istream& is, InfoSpecialist& info);
};

struct InfoManager {
    std::string loginHash;
    std::string name;
    int age;
    double salary;
    double WorkExp;
    std::string title;
    int employee;
    std::string department;

    friend std::ostream& operator<<(std::ostream& os, const InfoManager& info);
    friend std::istream& operator>>(std::istream& is, InfoManager& info);
};

extern std::vector<UserRecord> g_users;
extern std::vector<InfoBasicStaff> b_infos;
extern std::vector<InfoSpecialist> s_infos;
extern std::vector<InfoManager> m_infos;
extern std::unordered_map<std::string, std::vector<std::string>> dept_members;