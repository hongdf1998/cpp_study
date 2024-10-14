#pragma once
#include <iostream>
#include "fstream"
#include "worker.h"
#define FILEPATH "empFile.txt"
using namespace std;

class workerManager{
public:
    workerManager();
    void showMenu();  // 展示菜单
    void addEmp(); // 增加职工
    void save();  // 将职工信息保存到文件
    int getEmpNum();
    vod init_Emp();
    void exitSystem(); // 退出系统
    ~workerManager();

    int m_EmpNum;
    Worker ** m_EmpArray;
    bool m_FileIsEmpty;  // 标志文件是否为空
};