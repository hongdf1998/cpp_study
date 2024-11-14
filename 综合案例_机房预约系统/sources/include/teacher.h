#pragma once
#include <vector>
#include "identity.h"
#include "orderFile.h"

class Teacher : public Identity{
public:
    Teacher();
    Teacher(int id, std::string name, std::string passwd);
    virtual void openMenu();
    void showAllOrder();
    void validOrder();

    int m_EmId;
};