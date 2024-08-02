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
    sudo apt install libhiredis-dev libssl-dev qt6-base-dev qtbase5-dev qttools5-dev-tools qt6-tools-dev qt6-linguist-tools
```

- 编译运行

```shell
    mkdir build && cd build
    cmake .. 
    make -j20
    ./server
    ./client
```

## 项目结构

