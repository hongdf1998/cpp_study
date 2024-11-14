#include "../include/teacher.h"

Teacher::Teacher(){}

Teacher::Teacher(int id, std::string name, std::string passwd){
    this->m_EmId = id;
    this->m_Name = name;
    this->m_Passwd = passwd;
}

void Teacher::openMenu(){
    system("cls");
    std::cout << "欢迎教师："<<this->m_Name << "登录！\n";
    std::cout << "1.查看所有预约\n";
    std::cout << "2.审核预约\n";
    std::cout << "0.注销登录\n";
    std::cout << "请选择您的操作： ";
}

void Teacher::showAllOrder(){
    OrderFile of;
    if (of.m_Size == 0){
        std::cout << "没有预约记录！\n";
        system("pause");
        return;
    }

    for (int i = 0; i < of.m_Size; i++){
        std::cout << "预约日期：周" << of.m_OrderData[i]["date"];
        std::cout << " 时段：" << of.m_OrderData[i]["interval"];
        std::cout << " 机房：" << of.m_OrderData[i]["roomId"];
        std::string status =  " 状态：";  //  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (of.m_OrderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if (of.m_OrderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_OrderData[i]["status"] == "-1")
        {
            status += "审核未通过，预约失败";
        }
        else
        {
            status += "预约已取消";
        }
        std::cout << status << std::endl;
    }

    system("pause");
}

void Teacher::validOrder(){
    OrderFile of;
    if (of.m_Size == 0){
        std::cout << "没有预约记录！\n";
        system("pause");
        return;
    }
    int index = 1;
    std::vector<int> v;
    for (int i = 0; i < of.m_Size; i++){
        if (of.m_OrderData[i]["status"] == "1"){
            v.push_back(i);
            std::cout <<  index ++  << "、 ";
            std::cout << "预约日期： 周" << of.m_OrderData[i]["date"];
            std::cout << " 时段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
            std::cout << " 机房：" << of.m_OrderData[i]["roomId"];
            std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
            if (of.m_OrderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            std::cout << status << std::endl;
        }
    }
    std::cout << "上述只列出状态为审核中的记录，请输入要审核的记录(0为退出)：";
    int select = 0;
    int ret = 0;
    while (true){
        std::cin >> select;
        if (select >= 0 && select <= v.size()){
            if (select == 0){
                break;
            }else{
                std::cout << "请输入审核结果：\n";
                std::cout << "1、通过\n";
                std::cout << "2、不通过\n";
                std::cin >> ret;
                if (ret == 1){
                    of.m_OrderData[v[select - 1]]["status"] = "2";
                }else if (ret == 2){
                    of.m_OrderData[v[select - 1]]["status"] = "-1";
                }else{
                    std::cout << "输入有误，重新选择记录\n";
                    system("pause");
                    continue;
                }
                of.updateOrder();
                std::cout << "审核完毕！\n";
                break;
            }
        }
        std::cout << "输入有误，请重新输入！\n";
    }
}