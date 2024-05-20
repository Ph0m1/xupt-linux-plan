#include "redis.hpp"
#include "json.hpp"
#include "menu.hpp"
#include "cli.hpp"

/****************************************
*   user's json for chatroom
*  {
        "name": name string,
        "password": password string,
        "status": status int,
        "type": op/usr int,
        "msg": msg json,
    }
    rooms' json for chatroom   
    {
        "name": name string,
        ""
    }
*
****************************************/
