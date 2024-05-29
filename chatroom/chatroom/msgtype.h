#ifndef MSGTYPE_H
#define MSGTYPE_H

enum MsgType{
    Success = 1,
    Refuse = 0,
    Failure = -1,

    UserAccount,
    UserLogin,
    AccountFound,
    ResetInfo,
    AccountDelete,

    GroupCreat,
    GroupJoin,
    GroupExit,

    UserEnter,
    UserLeft,

    Msg,
    File,

    FriendAdd,
    FriendDelete,
    FriendBanned,

};


#endif // MSGTYPE_H
