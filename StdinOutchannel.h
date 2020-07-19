//
// Created by es on 2020/7/16.
//

#ifndef PRJ2_ZINX_STUDY_STDINOUTCHANNEL_H
#define PRJ2_ZINX_STUDY_STDINOUTCHANNEL_H

#include <zinx.h>
#include <ZinxTCP.h>
class Stdinchannel: public Ichannel {
public:
    Stdinchannel();

    ~Stdinchannel() override;

    bool Init() override;

    bool ReadFd(std::string &_input) override;

    bool WriteFd(std::string &_output) override;

    void Fini() override;

    int GetFd() override;

    std::string GetChannelInfo() override;

protected:
    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override;

};

class Stdoutchannel: public Ichannel{
public:
    bool Init() override;

    bool ReadFd(std::string &_input) override;

    bool WriteFd(std::string &_output) override;

    void Fini() override;

    int GetFd() override;

    std::string GetChannelInfo() override;

protected:
    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override;

};
class myTcpData: public ZinxTcpData{
public:
    myTcpData(int _fd):ZinxTcpData(_fd){};
    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override;

};

class myFact: public IZinxTcpConnFact{
public:
    ZinxTcpData *CreateTcpDataChannel(int _fd) override;

};

#endif //PRJ2_ZINX_STUDY_STDINOUTCHANNEL_H
