//
// Created by es on 2020/7/18.
//

#ifndef PRJ2_ZINX_STUDY_ZINXTIMER_H
#define PRJ2_ZINX_STUDY_ZINXTIMER_H

#include <zinx.h>
#include <list>
#include <vector>
class ZinxTimerChannel:public Ichannel  {
public:
    bool Init() override;

    bool ReadFd(std::string &_input) override;

    bool WriteFd(std::string &_output) override;

    void Fini() override;

    int GetFd() override;

    std::string GetChannelInfo() override;

protected:
    AZinxHandler *GetInputNextStage(BytesMsg &_oInput) override;
private:
    int m_TimerFd = -1;
};
class TimerOutProc{
public:
    virtual void Proc()= 0 ;
    virtual int GetTimersec()= 0;
    int iCount = -1;
};

class TimerMng: public AZinxHandler{
public:
    static TimerMng& getInstance(){
        return single;
    }

private:
    std::vector<std::list<TimerOutProc*>> m_timer_wheel;
    int cur_index = 0;
    static TimerMng single;
    TimerMng();
public:
    IZinxMsg *InternelHandle(IZinxMsg &_oInput) override;

    AZinxHandler *GetNextHandler(IZinxMsg &_oNextMsg) override;
    void AddTask(TimerOutProc* _ptask);

    void DelTask(TimerOutProc* _ptask);

};

#endif //PRJ2_ZINX_STUDY_ZINXTIMER_H
