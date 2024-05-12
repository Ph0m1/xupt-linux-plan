## socket

   socket 是一种 IPC 方法,它允许位于同一主机(计算机)或使用网络连接起来的不同主机上的应用程序之间交换数据。

   socket 是一种网络通信的编程接口(interface),它为网络上的两个程序提供双向通信的能力。

### socket domain

   socket domain 定义了 socket 通信中使用的协议族。

   |协议族|描述|
   |:---:|:---:|
   |AF_INET|IPv4 网络通信|
   |AF_INET6|IPv6 网络通信|
   |AF_UNIX|本地通信|
   |:---:|:---:|

### socket type

   socket type 定义了 socket 通信中使用的协议类型。

   |协议类型|描述|
   |:---:|:---:|
   |SOCK_STREAM|TCP 协议|
   |SOCK_DGRAM|UDP 协议|
   |SOCK_RAW|原始套接字|
   |:---:|:---:|

### socket protocol

   socket protocol 定义了 socket 通信中使用的协议。

   |协议|描述|