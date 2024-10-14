#include "employee.h"

Employee::Employee(string name, int id, string department){
    m_Name = name;
    m_Id = id;
    m_Department = department;
}

void Employee::showInfo() {
    cout << "姓名：" << m_Name << endl;
    cout << "编号：" << m_Id << endl;
    cout << "岗位：" << m_Department << endl;
    cout << "岗位职责：完成经理交代的任务。" << endl;
}

string Employee::getDeptName() {
    return string("普通员工");
}