#pragma once 

// 初始化监听套接字
int initListenFd(unsigned short port);
// 启动epoll
int epollRun(int lfd);
// 和客户端建立链接
int acceptClient(int lfd, int epfd);
// 接收http请求
int recvHttpRequestt(int cfd, int epfd);
// 解析请求行
int parseRequestLine(const char* line, int cfd);
// 发送文件
int sendFile(const char* fileName, int cfd);
// 发送响应头(状态行+响应头)
int sendHeadMsg(int cfd, int status, const char* descr, const char* type, int length);
// 判断文件的类型
const char* getFileType(const char* name);

