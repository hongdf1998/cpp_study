#include <iostream>
#include <fstream>
#include "include/identity.h"
#include "include/student.h"
#include "include/teacher.h"
#include "include/manager.h"
#include "include/globalFile.h"
using namespace std;

void mainMenu(){
    system("cls");
    cout << "欢迎使用机房预约系统\n";
    cout << "1、学生\n";
    cout << "2、老师\n";
    cout << "3、管理员\n";
    cout << "0、退出\n";
}

void managerMenu(Identity* & manager){
    // 1. 因为loginIn中创建的是Identity指针，所以形参中有Identity*
    // 2. 又因为我们需要在当前函数中删除指针，需要能够直接修改本身，所以使用引用&
    while (true){
        manager->openMenu();
        Manager * man = (Manager *)manager;  // 将父类指针转为子类指针，条用子类接口
        int select = -1;
        cin >> select;
        if (select == 1){
            man->addPerson();
        }else if(select == 2){
            man->showPerson();
        }else if(select == 3){
            man->showComputer();
        }else if(select == 4){
            man->cleanFile();
        }else if(select == 0){
            delete manager;  // 销毁堆区对象
            system("pause");
            return;
        }else{
            cout << "输入有误！" << endl;
            system("pause");
        }

    }
}

void studentMenu(Identity* & student) {
    while (true){
        student->openMenu();
        Student * stu = (Student *)student;  // 将父类指针转为子类指针，条用子类接口
        int select = -1;
        cin >> select;
        if (select == 1){
            stu->applyOrder();
        }else if(select == 2){
            stu->showMyOrder();
        }else if(select == 3){
            stu->showAllOrder();
        }else if(select == 4){
            stu->cancelOrder();
        }else if(select == 0){
            delete student;  // 销毁堆区对象
            cout << "注销成功" << endl;
            system("pause");
            return;
        }else{
            cout << "输入有误！" << endl;
            system("pause");
        }

    }
}

void teacherMenu(Identity* &teacher){
    while (true){
        teacher->openMenu();
        Teacher * tea = (Teacher *)teacher;  // 将父类指针转为子类指针，条用子类接口
        int select = -1;
        cin >> select;
        if (select == 1){
            tea->showAllOrder();
        }else if(select == 2){
            tea->validOrder();
        }else if(select == 0){
            delete teacher;  // 销毁堆区对象
            cout << "注销成功" << endl;
            system("pause");
            return;
        }else{
            cout << "输入有误！" << endl;
            system("pause");
        }

    }
}

void loginIn(string filename, int type){
    // filename：需要操作的文件名
    // type：登录身份类型，1是学生  2是老师  3是管理员
    Identity * person = NULL;

    ifstream ifs(filename, ios::in);
    if (!ifs.is_open()){
        cout << "打开文件失败！" << endl;
        ifs.close();
        system("pause");
        return;
    }

    int id = 0;
    string name;
    string passwd;
    if (type == 1){
        // 学生
        cout << "请输入学号：";
        cin >> id;
    }else if(type == 2){
        // 教师
        cout << "请输入职工号：";
        cin >> id;
    }

    cout << "请输入名字：";
    cin >> name;
    cout << "请输入密码：";
    cin >> passwd;

    if (type == 1){
        // 学生身份验证
        int fid;
        string fname;
        string fpasswd;
        while(ifs >> fid && ifs >> fname && ifs >> fpasswd){
            if (id == fid && name == fname && passwd == fpasswd){
                cout << "学生身份验证成功！" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, passwd);
                // 进入学生菜单
                studentMenu(person);

                return;
            }
        }
    }else if(type == 2){
        // 老师身份验证
        int fid;
        string fname;
        string fpasswd;
        while(ifs >> fid && ifs >> fname && ifs >> fpasswd){
            if (id == fid && name == fname && passwd == fpasswd){
                cout << "教师身份验证成功！" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, passwd);
                // 进入教师菜单
                teacherMenu(person);

                return;
            }
        }
    }else if(type == 3){
        // 管理员身份验证
        string fname;
        string fpasswd;
        while(ifs >> fname && ifs >> fpasswd){
            if (name == fname && passwd == fpasswd){
                cout << "管理员身份验证成功！" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, passwd);
                // 进入管理员菜单
                managerMenu(person);
                return;
            }
        }
    }else{
        cout << "身份错误" << endl;
        return;
    }

    cout << "验证登录失败！" << endl;
    system("pause");
}


int main() {
    int select = -1;
    while (true){
        mainMenu();
        cout << "输入您的选择：";
        cin >> select;
        switch(select){
            case 0:
                cout << "欢迎下次使用\n";
                system("pause");
                exit(0);
            case 1:
                loginIn(STUDENT_FILE, 1);
                break;
            case 2:
                loginIn(TEACHER_FILE, 2);
                break;
            case 3:
                loginIn(ADMIN_FILE, 3);
                break;
            default:
                cout << "选择有误\n";
                system("pause");
                break;
        }
    }



}
