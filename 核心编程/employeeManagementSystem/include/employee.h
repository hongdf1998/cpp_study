#pragma once
#include <iostream>
#include "worker.h"

class Employee : public Worker{
public:
    Employee(string name, int id, string department);
    virtual void showInfo();
    virtual string getDeptName();
};