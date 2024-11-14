#pragma once
#include <vector>
#include <algorithm>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"


class Manager : public Identity{
public:
    Manager();
    Manager(std::string name, std::string passwd);
    virtual void openMenu();
    void addPerson();
    void showPerson();
    void showComputer();
    void cleanFile();

    bool checkRepeat(int id, int type);
    void initVector();
    std::vector<Student> vStu;
    std::vector<Teacher> vTea;

    std::vector<ComputerRoom> vCom;
};