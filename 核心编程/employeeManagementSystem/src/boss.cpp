#include "boss.h"

Boss::Boss(string name, int id, string department){
    m_Name = name;
    m_Id = id;
    m_Department = department;
}

void Boss::showInfo(){
    cout << "姓名：" << m_Name << endl;
    cout << "编号：" << m_Id << endl;
    cout << "岗位：" << m_Department << endl;
    cout << "岗位职责：管理公司所有事物。" << endl;
}

string Boss::getDeptName(){
    return string("老板");
}