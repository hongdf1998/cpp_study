#include "../include/student.h"

Student::Student(){}

Student::Student(int id, std::string name, std::string passwd){
    this->m_Id = id;
    this->m_Name = name;
    this->m_Passwd = passwd;

    std::ifstream ifs(COMPUTER_FILE, std::ios::in);
    ComputerRoom c;
    while (ifs >> c.m_ComId && ifs >> c.m_MaxNum){
        vCom.push_back(c);
    }
    std::cout << "当前机房数量为：" << vCom.size() << std::endl;
    ifs.close();
}


void Student::openMenu(){
    system("cls");
    std::cout << "欢迎学生："<<this->m_Name << "登录！\n";
    std::cout << "1.申请预约\n";
    std::cout << "2.查看我的预约\n";
    std::cout << "3.查看所有预约\n";
    std::cout << "4.取消预约\n";
    std::cout << "0.注销登录\n";
    std::cout << "请选择您的操作： ";
}

void Student::applyOrder() {
    std::cout << "机房开放时间为周一至周五！\n";
    std::cout << "请输入申请预约的时间：\n";
    std::cout << "1、周一\n";
    std::cout << "2、周二\n";
    std::cout << "3、周三\n";
    std::cout << "4、周四\n";
    std::cout << "5、周五\n";

    int date = 0;
    int interval = 0;
    int room = 0;
    while (true){
        std::cin >> date;
        if (date >= 1 && date <= 5){
            break;
        }
        std::cout << "输入有误，请重新输入！\n";
    }

    std::cout << "请输入申请预约的时间段：\n";
    std::cout << "1、上午\n";
    std::cout << "2、下午\n";
    while(true){
        std::cin >> interval;
        if (interval == 1 or interval == 2){
            break;
        }
        std::cout << "输入有误，请重新输入！\n";
    }

    std::cout << "请选择机房：\n";
    std::cout << "1、1号机房容量：" << this->vCom[0].m_MaxNum << std::endl;
    std::cout << "1、2号机房容量：" << this->vCom[1].m_MaxNum << std::endl;
    std::cout << "1、3号机房容量：" << this->vCom[2].m_MaxNum << std::endl;
    while (true){
        std::cin >> room;
        if (room >= 1 && room <=3){
            break;
        }
        std::cout << "输入有误，请重新输入！\n";
    }


    std::cout << "预约成功！审核中\n";

    std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << std::endl;
    ofs.close();
    system("pause");

}

void Student::showMyOrder(){
    OrderFile of;
    if (of.m_Size == 0){
        std::cout << "没有预约记录！\n";
        system("pause");
        return;
    }

    for (int i = 0; i < of.m_Size; i++){
        if (stoi(of.m_OrderData[i]["stuId"]) == this->m_Id){
            // stoi 将 string 转为 int
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

    }
    system("pause");

}

void Student::showAllOrder(){
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

void Student::cancelOrder(){
    OrderFile of;
    if (of.m_Size == 0){
        std::cout << "没有预约记录！\n";
        system("pause");
        return;
    }
    int index = 1;
    std::vector<int> v;
    for (int i = 0; i < of.m_Size; i++){
        if (stoi(of.m_OrderData[i]["stuId"]) == this->m_Id){
            if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2"){
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
                else if (of.m_OrderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                std::cout << status << std::endl;
            }
        }
    }

    int select = 0;
    std::cout << "上述只列出状态为审核中或者预约成功的记录，请输入要取消的记录(0为退出)：";
    while (true){
        std::cin >> select;
        if (select >= 0 && select <= v.size()){
            if (select == 0){
                break;
            }else{
                of.m_OrderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                std::cout << "已取消该预约\n";
                break;
            }
        }
        std::cout << "输入有误，请重新输入！" << std::endl;
    }
    system("pause");

}
