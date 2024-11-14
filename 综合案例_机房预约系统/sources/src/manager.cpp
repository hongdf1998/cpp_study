#include "../include/manager.h"

Manager::Manager(){}
Manager::Manager(std::string name, std::string passwd){
    this->m_Name = name;
    this->m_Passwd = passwd;
    this->initVector();

    std::ifstream ifs(COMPUTER_FILE, std::ios::in);
    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum){
        vCom.push_back(c);
    }
    std::cout << "当前机房数量为：" << vCom.size() << std::endl;
    ifs.close();
}
void Manager::openMenu(){
    system("cls");
    std::cout << "欢迎管理员："<<this->m_Name << "登录！\n";
    std::cout << "1.添加账号\n";
    std::cout << "2.查看账号\n";
    std::cout << "3.查看机房\n";
    std::cout << "4.清空预约\n";
    std::cout << "0.注销登录\n";
    std::cout << "请选择您的操作： ";
}
void Manager::addPerson(){
    int select = 0;
    std::string filename;
    std::cout << "请输入添加账号的类型：\n";
    std::cout << "1、学生\n";
    std::cout << "2、老师\n";
    std::cin >> select;
    if(select == 1){
        std::cout << "请输入学号：";
        filename = STUDENT_FILE;
    }else if(select == 2){
        std::cout << "请输入职工号：";
        filename = TEACHER_FILE;
    }else{
        std::cout << "输入有误\n";
        system("pause");
        return;
    }
    int id;
    std::string name;
    std::string passwd;
    while (true){
        std::cin >> id;
        bool ret = this->checkRepeat(id, select);
        if (ret){
            std::cout << "账号重复，请重新输入：";
        }else{
            break;
        }
    }
    std::cout << "请输入姓名：";
    std::cin >> name;
    std::cout << "请输入密码：";
    std::cin >> passwd;

    std::ofstream ofs(filename, std::ios::out|std::ios::app);
    ofs << id << ' ' << name << ' ' << passwd << std::endl;
    std::cout << "添加成功\n";
    this->initVector();  // 解决：刚添加的账号由于没有更新到容器中，因此不会做检测，导致刚加入的账号的学生号或者职工编号，再次添加时依然可以重复
    system("pause");
}

void printStudent(const Student & s){
    std::cout << "学号：" << s.m_Id << "，姓名：" << s.m_Name << "，密码：" << s.m_Passwd << std::endl;
}

void printTeacher(const Teacher & t){
    std::cout << "学号：" << t.m_EmId << "，姓名：" << t.m_Name << "，密码：" << t.m_Passwd << std::endl;
}

void Manager::showPerson(){
    int select = 0;
    std::cout << "请选择查看内容：\n";
    std::cout << "1、学生\n";
    std::cout << "2、老师\n";
    std::cin >> select;
    if (select == 1){
        std::cout << "所有学生的信息如下：\n";
        std::for_each(vStu.begin(), vStu.end(), printStudent);
    }else if (select == 2){
        std::cout << "所有老师的信息如下：\n";
        std::for_each(vTea.begin(), vTea.end(), printTeacher);
    }else{
        std::cout << "选择有误！\n";
    }
    system("pause");
}

void Manager::showComputer(){
    std::cout << "机房数量为：" << vCom.size() << std::endl;
    for (std::vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++){
        std::cout << "机房编号：" << it->m_ComId << "，最大容量：" << it->m_MaxNum << std::endl;
    }
    system("pause");
}

void Manager::cleanFile(){
    std::ofstream ofs(ORDER_FILE, std::ios::trunc);
    ofs.close();
    std::cout << "清空成功！\n";
    system("pause");
}

void Manager::initVector() {
    // 读取学生文件信息
    std::ifstream ifs(STUDENT_FILE, std::ios::in);
    if (!ifs.is_open()){
        std::cout << "文件读取失败\n";
        return;
    }

    Student tmpStu;
    while(ifs >> tmpStu.m_Id && ifs >> tmpStu.m_Name && ifs >> tmpStu.m_Passwd){
        vStu.push_back(tmpStu);
    }
    std::cout << "当前学生数量为：" << vStu.size() << std::endl;
    ifs.close();

    // 读取老师文件信息
    ifs.open(TEACHER_FILE, std::ios::in);
    if (!ifs.is_open()){
        std::cout << "文件读取失败\n";
        return;
    }

    Teacher tmpTea;
    while(ifs >> tmpTea.m_EmId && ifs >> tmpTea.m_Name && ifs >> tmpTea.m_Passwd){
        vTea.push_back(tmpTea);
    }
    std::cout << "当前老师数量为：" << vTea.size() << std::endl;
    ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
    if (type == 1){
        for (std::vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++){
            if (id == it->m_Id){
                return true;
            }
        }
    }else{
        for (std::vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++){
            if (id == it->m_EmId){
                return true;
            }
        }
    }
    return false;
}