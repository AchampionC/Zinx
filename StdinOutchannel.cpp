//
// Created by es on 2020/7/16.
//

#include "StdinOutchannel.h"
#include <iostream>
#include "CmdCheck.h"
using namespace std;
Stdinchannel::~Stdinchannel() {

}

bool Stdinchannel::Init() {
    return true;
}

bool Stdinchannel::ReadFd(std::string &_input) {
    cin>>_input;
    return true;
}

bool Stdinchannel::WriteFd(std::string &_output) {
    return false;
}

void Stdinchannel::Fini() {

}

int Stdinchannel::GetFd() {
    return 0;
}

std::string Stdinchannel::GetChannelInfo() {
    return "stdin";
}

AZinxHandler *Stdinchannel::GetInputNextStage(BytesMsg &_oInput) {
    //返回协议对象
    return CmdCheck::getInstance();
}

Stdinchannel::Stdinchannel() {}


bool Stdoutchannel::Init() {
    return true;
}

bool Stdoutchannel::ReadFd(string &_input) {
    return false;
}

bool Stdoutchannel::WriteFd(string &_output) {
    cout<<_output<<endl;
    return true;
}

void Stdoutchannel::Fini() {

}

int Stdoutchannel::GetFd() {
    return 1;
}

string Stdoutchannel::GetChannelInfo() {
    return "stdout";
}

AZinxHandler *Stdoutchannel::GetInputNextStage(BytesMsg &_oInput) {
    return CmdCheck::getInstance();
}

ZinxTcpData *myFact::CreateTcpDataChannel(int _fd) {
    //tcp的工厂的类，会创建数据套接字通道对象。
    return new myTcpData(_fd);
}

AZinxHandler *myTcpData::GetInputNextStage(BytesMsg &_oInput) {
    return CmdCheck::getInstance();
}

