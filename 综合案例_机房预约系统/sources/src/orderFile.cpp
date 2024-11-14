#include "../include/orderFile.h"

OrderFile::OrderFile(){
    std::ifstream ifs(ORDER_FILE, std::ios::in);
    std::string date;      //日期
    std::string interval;  //时间段
    std::string stuId;     //学生编号
    std::string stuName;   //学生姓名
    std::string roomId;    //机房编号
    std::string status;    //预约状态
    this->m_Size = 0;

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status){
        std::string key;
        std::string value;
        std::map<std::string, std::string> m;

        int pos = date.find(":");
        if (pos != -1){
            key = date.substr(0, pos);  // : 前面是关键字
            value = date.substr(pos + 1, date.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        pos = interval.find(":");
        if (pos != -1){
            key = interval.substr(0, pos);  // : 前面是关键字
            value = interval.substr(pos + 1, interval.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        pos = stuId.find(":");
        if (pos != -1){
            key = stuId.substr(0, pos);  // : 前面是关键字
            value = stuId.substr(pos + 1, stuId.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        pos = stuName.find(":");
        if (pos != -1){
            key = stuName.substr(0, pos);  // : 前面是关键字
            value = stuName.substr(pos + 1, stuName.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        pos = roomId.find(":");
        if (pos != -1){
            key = roomId.substr(0, pos);  // : 前面是关键字
            value = roomId.substr(pos + 1, roomId.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        pos = status.find(":");
        if (pos != -1){
            key = status.substr(0, pos);  // : 前面是关键字
            value = status.substr(pos + 1, status.size() - pos + 1);  // : 后面是值
            m.insert(make_pair(key, value));
        }

        this->m_OrderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }
    ifs.close();
}

void OrderFile::updateOrder(){
    if (this->m_Size == 0){
        return;
    }
    std::ofstream ofs(ORDER_FILE, std::ios::out | std::ios::trunc);  // 清空原来的文件，重写写入
    for (int i = 0; i < this->m_Size; i++){
        ofs << "date:" << this->m_OrderData[i]["date"] << " ";
        ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
        ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_OrderData[i]["status"] << std::endl;
    }
    ofs.close();
}