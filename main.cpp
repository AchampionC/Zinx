#include <iostream>
#include <zinx.h>
#include "StdinOutchannel.h"
#include "EchoRole.h"
#include <ZinxTCP.h>
#include <sys/timerfd.h>
#include "ZinxTimer.h"
using namespace std;




//class TestStdout:public Ichannel{
//public:
//    bool Init() override {
//        return true;
//    }
//
//    bool ReadFd(string &_input) override {
//        return false;
//    }
//
//    bool WriteFd(string &_output) override {
//        cout<<_output<<endl;
//        return true;
//    }
//
//    void Fini() override {
//
//    }
//
//    int GetFd() override {
//        return 1;
//    }
//
//    string GetChannelInfo() override {
//        return "stdout";
//    }
//
//protected:
//    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override {
//        return nullptr;
//    }
//
//
//
//}*poOut = new TestStdout();
//class Echo: public AZinxHandler{
//protected:
//    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override {
//        GET_REF2DATA(BytesMsg,input,_oInput);
//        ZinxKernel::Zinx_SendOut(input.szData,*poOut);
//        return nullptr;
//    }
//
//    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override {
//        return nullptr;
//    }
//
//}*poEcho = new Echo();
//
//class ExitFrameWork: public AZinxHandler{
//protected:
//    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override {
//        GET_REF2DATA(BytesMsg,obyte,_oInput);
//        if(obyte.szData=="exit"){
//            ZinxKernel::Zinx_Exit();
//            return NULL;
//        }
//        //创建交给下一个环节的数据
//        return new BytesMsg(obyte);
//    }
//
//    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override {
//        return poEcho;
//    }
//
//}*poExit = new ExitFrameWork();
//
//class AddDate: public AZinxHandler{
//protected:
//    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override {
//        GET_REF2DATA(BytesMsg,oBytes,_oInput);
//        time_t tmp;
//        time(&tmp);
//        string szNew = string(ctime(&tmp)) +oBytes.szData;
//        BytesMsg* pret = new BytesMsg(oBytes);
//        pret->szData = szNew;
//        return pret;
//    }
//
//    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override {
//        return poEcho;
//    }
//
//}*poAddDate = new AddDate();
//
//class CmdHandler: public AZinxHandler{
//    int status = 0;//0是不加前缀 1是加前缀
//protected:
//    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override {
//        GET_REF2DATA(BytesMsg,oBytes,_oInput);
//        if(oBytes.szData=="open"){
//            ZinxKernel::Zinx_Add_Channel(*poOut);
//            return NULL;
//        }else if(oBytes.szData=="close"){
//            ZinxKernel::Zinx_Del_Channel(*poOut);
//            return NULL;
//        }else if(oBytes.szData=="date"){
//            status = 1;
//        }else if(oBytes.szData=="cleardate"){
//            status = 0;
//        }
//        return new BytesMsg(oBytes);
//    }
//
//    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override {
//        GET_REF2DATA(BytesMsg, oBytes, _oNextMsg);
//        if (oBytes.szData == "exit") {
//            return poExit;
//        } else {
//            if(0==status){
//                return poEcho;
//            }else{
//                return poAddDate;
//            }
//        }
//    }
//
//}*poCmd = new CmdHandler();
//
//
//
//
//class TestStdin: public Ichannel{
//public:
//    bool Init() override {
//        return true;
//    }
//
//    bool ReadFd(string &_input) override {
//        cin>>_input;
//        return true;
//    }
//
//    bool WriteFd(string &_output) override {
//        return false;
//    }
//
//    void Fini() override {
//
//    }
//
//    int GetFd() override {
//        return 0;
//    }
//
//    string GetChannelInfo() override {
//        return "stdin";
//    }
//
//protected:
//    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override {
//        return poCmd;
//    }
//
//
//}*poStdin = new TestStdin();
class timerhello: public TimerOutProc{
public:
    void Proc() override {
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        std::string output = "hello world";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
    }

    int GetTimersec() override {
        return 3;
    }

};
class timerbye: public TimerOutProc{
public:
    void Proc() override {
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        std::string output = "bye";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
    }

    int GetTimersec() override {
        return 1;
    }

};


int main() {
    ZinxKernel::ZinxKernelInit();
//    TestStdin* poStdin = new TestStdin();
//    ZinxKernel::Zinx_Add_Channel(*poStdin);
//    ZinxKernel::Zinx_Add_Channel(*poOut);
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTimerChannel()));
    TimerMng::getInstance().AddTask(new timerhello());
    TimerMng::getInstance().AddTask(new timerbye());
    ZinxKernel::Zinx_Add_Channel(*(new Stdinchannel()));
    ZinxKernel::Zinx_Add_Channel(*(new Stdoutchannel()));
    ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(51111,new myFact())));
    ZinxKernel::Zinx_Add_Role(*(new EchoRole()));
    ZinxKernel::Zinx_Add_Role(*(new DatePreRole()));
    ZinxKernel::Zinx_Add_Role(*(new OutputCtrl()));




    ZinxKernel::Zinx_Run();
    ZinxKernel::ZinxKernelFini();
    return 0;
}
