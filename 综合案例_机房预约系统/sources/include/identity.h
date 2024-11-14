#pragma once
#include<iostream>
#include<fstream>
#include "globalFile.h"


class Identity{
public:
    virtual void openMenu() = 0;  // 纯虚函数

    std::string m_Name;
    std::string m_Passwd;
};