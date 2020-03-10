/**********************************************************
 * Author   : liuminxuan
 * Email    : liuminxuan1024@163.com
 * Time     : 2020-03-04 21:09
 * FileName : server.cpp
 * *******************************************************/
#include "udpsvr.hpp"

// ip 和 port
int main(int argc,char* argv[])
{
  if (argc != 3)
  {
    printf ("cli [ip] [port]");
    return 0;
  }
  // 服务端的IP和Port
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  UdpSvr us;
  if(!us.CreatSock())
  {
    return 0;
  }
  std::string buf;
  printf ("client say:");
  fflush(stdout);
  std::cin>>buf;
  // 数据来源的地址信息
  struct sockaddr_in dest_addr;
  dest_addr.sin_family=AF_INET;
  dest_addr.sin_port=htons(port);
  dest_addr.sin_addr.s_addr=inet_addr(ip.c_str());
  us.Send(buf,&dest_addr);
  us.Recv(buf,&dest_addr);
  printf ("server say:[%s]\n",buf.c_str()); 
  us.Close();
  return 0;
}
