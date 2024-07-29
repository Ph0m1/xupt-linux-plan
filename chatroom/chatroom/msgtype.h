#ifndef MSGTYPE_H
#define MSGTYPE_H

enum MsgType{
    Success = 1,
    Refuse = 0,
    Failure = -1,
    MailError,
    Disconnent,
    OutLine,
    Logout,

    Captcha,

    UserAccount,
    UserLogin,
    AccountFound,
    ResetPasswd,
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
    FriendAddMsg,
    FriendDelete,
    FriendBanned,
    ReFreshFriendList,

    // 消息状态
    Unread,
    Read
};


#endif // MSGTYPE_H
