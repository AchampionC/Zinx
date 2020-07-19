//
// Created by es on 2020/7/18.
//
#include <zinx.h>
#include "ZinxTimer.h"
#include <sys/timerfd.h>
using namespace std;
bool ZinxTimerChannel::Init() {
    int bRet = false;
    int iFd = timerfd_create(CLOCK_MONOTONIC,0);
    if(0<=iFd){
        struct itimerspec period = {{1,0},{1,0}};
        if(0==timerfd_settime(iFd,0,&period,0)){
            bRet = true;
            m_TimerFd = iFd;
        }
    }
    return bRet;
}

bool ZinxTimerChannel::ReadFd(std::string &_input) {
    int bRet = false;
    char buff[8]  = {0};
    if(0<=read(m_TimerFd,buff,sizeof(buff))){
        bRet = true;
        _input.assign(buff,sizeof(buff));
    }
    return bRet;
}

bool ZinxTimerChannel::WriteFd(std::string &_output) {
    return false;
}

void ZinxTimerChannel::Fini() {
    close(m_TimerFd);
    m_TimerFd = -1;
}

int ZinxTimerChannel::GetFd() {
    return m_TimerFd;
}

std::string ZinxTimerChannel::GetChannelInfo() {
    return "TimerFd";
}

class output_hello: public AZinxHandler{
protected:
    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override {
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        std::string output = "hello world";
        ZinxKernel::Zinx_SendOut(output,*pchannel);
        return nullptr;
    }

    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override {
        return nullptr;
    }

}*pout_hello = new output_hello();
AZinxHandler *ZinxTimerChannel::GetInputNextStage(BytesMsg &_oInput) {
    return &TimerMng::getInstance();
}
TimerMng::TimerMng() {
    //创建10个齿
    list<TimerOutProc*> tmp;
    for(int i = 0;i<10;i++){
        m_timer_wheel.push_back(tmp);
    }
}
IZinxMsg *TimerMng::InternelHandle(IZinxMsg &_oInput) {

    unsigned long  iTimeroutCount = 0;
    GET_REF2DATA(BytesMsg,obytes,_oInput);
    obytes.szData.copy((char *)&iTimeroutCount,sizeof(iTimeroutCount),0);
    cur_index++;
    cur_index%=10;
    list<TimerOutProc*> m_cache;
    while(iTimeroutCount-->0) {
        for (auto itr = m_timer_wheel[cur_index].begin(); itr != m_timer_wheel[cur_index].end();) {
            if ((*itr)->iCount <= 0) {
                m_cache.push_back(*itr);
                auto ptmp = *itr;
                itr = m_timer_wheel[cur_index].erase(itr);
                AddTask(ptmp);
            } else {
                (*itr)->iCount--;
                ++itr;
            }
        }
        for (auto task:m_cache) {
            task->Proc();
        }
    }

    return nullptr;
}

AZinxHandler *TimerMng::GetNextHandler(IZinxMsg &_oNextMsg) {
    return nullptr;
}
void TimerMng::AddTask(TimerOutProc* _ptask){
    /*计算当前任务需要放到哪个齿上*/
    int index =(cur_index+_ptask->GetTimersec())%10;
    m_timer_wheel[index].push_back(_ptask);
    _ptask->iCount = _ptask->GetTimersec()/10;
}
void TimerMng::DelTask(TimerOutProc* _ptask){
    for(list<TimerOutProc*>& chi:m_timer_wheel){
        for(TimerOutProc* task:chi){
            if(task==_ptask){
                chi.remove(_ptask);
                return;
            }
        }
    }
}

TimerMng TimerMng::single;