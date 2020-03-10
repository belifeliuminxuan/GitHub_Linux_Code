/**********************************************************
 * Author   : liuminxuan
 * Email    : liuminxuan1024@163.com
 * Time     : 2020-03-04 20:09
 * FileName : udpsvr.hpp
 * *******************************************************/
#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
class UdpSvr
{
  public:
        UdpSvr()
        {
          Sock_ = -1;
        }
        ~UdpSvr()
        {

        }
        bool CreatSock()
        {
          Sock_ = socket(AF_INET,SOCK_DGRAM,17);
          if (Sock_ < 0)
          {
            perror("socket error");
            return false;
          }
            return true;
        }
        bool Bind(std::string& ip ,uint16_t port)
        {
          struct sockaddr_in addr;
          addr.sin_family = AF_INET;
          addr.sin_port = htons(port);// 两个字节 牵扯大小端问题
          addr.sin_addr.s_addr = inet_addr(ip.c_str()); 
          int ret = bind(Sock_,(struct sockaddr*)&addr,sizeof(addr));
          if (ret < 0)
          {
            perror("bind error!");
            return false;
          }
          return true;
        }
        bool Send(std::string& buf,struct sockaddr_in* destaddr)
        {
          // 在调用sizeof计算地址信息长度是不能使用sizeof(addr)，计算出来是指针的长度
         int ret = sendto(Sock_,buf.c_str(),buf.size(),0,(struct sockaddr*)destaddr,sizeof(struct sockaddr_in));
         if (ret < 0)
         {
           perror("send error!");
           return false;
         }
         return true;
        }
        bool Recv(std::string& buf,struct sockaddr_in* srcaddr)
        {
          char tmp[1024]={0};

          socklen_t socklen = sizeof(struct sockaddr_in);
         int ret = recvfrom(Sock_,tmp,sizeof(tmp)-1,0,(struct sockaddr*)srcaddr,&socklen);
         if (ret < 0)
         {
           perror("recv error!");
           return false;
         }
         buf.assign(tmp,ret);
         return true;
        }
        void Close()
        {
          close(Sock_);
        }
  private:
        int Sock_;
};
