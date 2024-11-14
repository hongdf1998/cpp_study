#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include "globalFile.h"

class OrderFile{
public:
    OrderFile();
    void updateOrder();
    std::map<int, std::map<std::string, std::string>> m_OrderData;
    int m_Size;
};