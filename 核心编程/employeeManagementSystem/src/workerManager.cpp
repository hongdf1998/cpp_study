#include "workerManager.h"
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

workerManager::workerManager(){
    ifstream ifs;
    ifs.open(FILEPATH, ios::in);
    if (!ifs.is_open()){
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;

    }

}

void workerManager::showMenu(){
    cout << "***********************************************" << endl;
    cout << "***********\t欢迎使用职工管理系统\t*******" << endl;
    cout << "***********\t1.显示职工信息\t***************" << endl;
    cout << "***********\t2.增加职工信息\t***************" << endl;
    cout << "***********\t3.删除职工信息\t***************" << endl;
    cout << "***********\t4.修改职工信息\t***************" << endl;
    cout << "***********\t5.查找职工信息\t***************" << endl;
    cout << "***********\t6.按照编号排序\t***************" << endl;
    cout << "***********\t7.清空所有文档\t***************" << endl;
    cout << "***********\t0.退出管理系统\t***************" << endl;
    cout << "***********************************************" << endl;
}

void workerManager::addEmp() {
    int addNum = 0;  // 新增职工数量
    cout << "请输入增加职工数量：";
    cin >> addNum;
    if (addNum > 0){
        int newSize = this->m_EmpNum + addNum;  // 新增后，总员工数量
        Worker ** newSpace = new Worker *[newSize];

        if (this->m_EmpArray != NULL){
            for (int i = 0; i < this->m_EmpNum; i++){
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        for (int i = 0; i < addNum; i++){
            int id;
            int select;
            string name;
            string department;
            cout << "输入第" << i + 1 << "个职工的信息" << endl;
            cout << "姓名：";
            cin >> name;
            cout << "编号：";
            cin >> id;
            cout << "部门：";
            cin >> department;

            cout << "岗位：（输入数字）" << endl;
            cout << "1、普通员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> select;

            Worker *worker = NULL;
            switch(select){
                case 1:
                    worker = new Employee(name, id, department);
                    break;
                case 2:
                    worker = new Manager(name, id, department);
                    break;
                case 3:
                    worker = new Boss(name, id, department);
                    break;
                default:
                    cout << "输入岗位有误！" << endl;
                    return;
            }

            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray;  // 释放原有空间
        this->m_EmpArray = newSpace;  // 更改新空间的只想
        this->m_EmpNum = newSize;  // 更新职工个数
        cout << "成功添加" << addNum << "名新职工！" << endl;
        this->save();

    }else{
        cout << "输入错误，数量必须大于0。" << endl;
        return;
    }
    system("pause");
    system("cls");
}

void workerManager::save(){
    ofstream ofs;
    ofs.open(FILEPATH, ios::out);

    for (int i = 0; i < this->m_EmpNum; i++){
        ofs << this->m_EmpArray[i]->m_Id << '\t'
            << this->m_EmpArray[i]->m_Name << '\t'
            << this->m_EmpArray[i]->m_Department << endl;
    }

    ofs.close();

}

void workerManager::exitSystem(){
    cout << "欢迎下次使用！" << endl;
    system("pause");
    exit(0);
}

workerManager::~workerManager(){
    if (this->m_EmpArray != NULL){
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}