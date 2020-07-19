//
// Created by es on 2020/7/16.
//

#ifndef PRJ2_ZINX_STUDY_CMDCHECK_H
#define PRJ2_ZINX_STUDY_CMDCHECK_H
#include <zinx.h>

class CmdCheck: public Iprotocol {
    CmdCheck();
    std::string szOutChannel;
    virtual ~CmdCheck();
    static CmdCheck* poSingle;
public:

    static CmdCheck* getInstance(){
        return poSingle;
    }

    UserData *raw2request(std::string _szInput) override;

    std::string *response2raw(UserData &_oUserData) override;

protected:
    Irole *GetMsgProcessor(UserDataMsg &_oUserDataMsg) override;

    Ichannel *GetMsgSender(BytesMsg &_oBytes) override;

};


#endif //PRJ2_ZINX_STUDY_CMDCHECK_H
