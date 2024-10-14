#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

void test(){
    Worker * worker = NULL;
    worker = new Employee("张三", 17, "工程师");
    worker->showInfo();
    cout << worker->getDeptName() << endl;
    delete worker;

    worker = new Manager("李四", 30, "业务主管");
    worker->showInfo();
    cout << worker->getDeptName() << endl;
    delete worker;

    worker = new Boss("王五", 45, "总裁");
    worker->showInfo();
    cout << worker->getDeptName() << endl;
    delete worker;
}

int main() {
    workerManager wm;
    int choice = -1;
    while(true){
        wm.showMenu();
        cout << "请输入您的选择：";
        cin >> choice;
        switch(choice){
            case 0:
                wm.exitSystem();
                break;
            case 1:
                break;
            case 2:
                wm.addEmp();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
        }
    }
    return 0;
}
