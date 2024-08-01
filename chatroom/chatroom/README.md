# Ph0m's Chatroom

## 介绍

## 项目依赖

    - hiredis
    - openssl
    - Qt6
    - Qt5

## 使用方法

- 下载源码
    
```shell
        git clone https://github.com/Ph0m1/Chatroom.git
        cd Chatroom
```
    
- 安装依赖
    
archlinux：

```shell
    sudo pacman -S hiredis openssl qt5 qt6
```
ubuntu：
    
```shell
    sudo apt-get install libhiredis-dev libssl-dev qt6-base-dev qt5-base-dev
```

- 编译运行

```shell
    mkdir build && cd build
    cmake .. 
    make
    ./server
    ./client
```

## 项目结构

    - src
        - client
            - main.cpp
            - mainwindow.cpp
            - mainwindow.h
