#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss : public Worker{
public:
    Boss(string name, int id, string department);
    virtual void showInfo();
    virtual string getDeptName();
};