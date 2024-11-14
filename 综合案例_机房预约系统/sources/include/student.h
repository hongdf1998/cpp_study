#pragma once
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerRoom.h"
#include "orderFile.h"

class Student : public Identity{
public:
    Student();
    Student(int id, std::string name, std::string passwd);
    virtual void openMenu();
    void applyOrder();
    void showMyOrder();
    void showAllOrder();
    void cancelOrder();

    int m_Id;
    std::vector<ComputerRoom> vCom;
};