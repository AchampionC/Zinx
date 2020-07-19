//
// Created by es on 2020/7/16.
//

#ifndef PRJ2_ZINX_STUDY_CMDMSG_H
#define PRJ2_ZINX_STUDY_CMDMSG_H

#include <zinx.h>
class CmdMsg: public UserData  {
public:
    //成员变量表示要回显的字符串
    std::string szUserData;
    CmdMsg(){};
    ~CmdMsg(){};
    bool isOpen = true;

    bool isCmd = false;

    bool needDatePre = false;


};


#endif //PRJ2_ZINX_STUDY_CMDMSG_H
