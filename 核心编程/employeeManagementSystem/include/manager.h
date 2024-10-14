#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Manager : public Worker{
public:
    Manager(string name, int id, string department);
    virtual void showInfo();
    virtual string getDeptName();
};