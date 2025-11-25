#pragma once
#include "Table.h"
#include "Role.h"
#include "Save.h"
#include "Menu.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <deque>

class Administration {
private:
    std::unique_ptr<std::string[]> lastReport;
    size_t lastReportSize = 0;

    void generateReport();

    template<typename T>
    bool compareBySalary(const T& a, const T& b) {
        return a.salary < b.salary;
    }

    template<typename T>
    bool isExperiencedEmployee(const T& employee) {
        return employee.WorkExp >= 5.0 && employee.salary >= 2000;
    }

    template<typename T>
    bool containsName(const T& employee, const std::string& searchName) {
        return employee.name.find(searchName) != std::string::npos;
    }

    template<typename Container>
    void displayEmployeesByType(const Container& employees, const std::string& typeName);

    template<typename Container>
    void searchInContainer(const Container& container, const std::string& searchName, const std::string& typeName);

    template<typename Container>
    void filterExperiencedEmployees(const Container& container, const std::string& typeName);

    template<typename Container>
    void sortContainerBySalary(Container& container, const std::string& typeName);

public:
    void AdminMenu();
    void clearLastReport();
};