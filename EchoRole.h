//
// Created by es on 2020/7/16.
//

#ifndef PRJ2_ZINX_STUDY_ECHOROLE_H
#define PRJ2_ZINX_STUDY_ECHOROLE_H

#include <zinx.h>
class EchoRole : public Irole{
public:
    EchoRole();

    virtual ~EchoRole();

    bool Init() override;

    UserData *ProcMsg(UserData &_poUserData) override;

    void Fini() override;

};
class OutputCtrl: public Irole{
public:
    bool Init() override;

    UserData *ProcMsg(UserData &_poUserData) override;

    void Fini() override;

    Ichannel* pOut = NULL;

};

class DatePreRole: public Irole{
public:
    bool Init() override;

    UserData *ProcMsg(UserData &_poUserData) override;

    void Fini() override;

    bool needAdd = false;

};

#endif //PRJ2_ZINX_STUDY_ECHOROLE_H
