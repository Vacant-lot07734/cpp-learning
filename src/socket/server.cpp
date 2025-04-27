//
// Created by Vacant lot on 2025/4/23.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
//#include <sys/unistd.h>
#include <unistd.h>
#define BUFFSIZE 2048
#define DEFAULT_PORT 16555 // 指定端口为16555
#define MAXLINK 2048
int sockfd, connfd; // 定义服务端监听套接字，服务端通信套接字（和客户端套接字是刚好相反）

void stopServerRunning(int p) {
  close(sockfd);
  printf("Close Server\n");
  exit(0);
}

// 1. socket()           创建套接字
// 2. bind()             绑定 IP 地址和端口号
// 3. listen()           监听连接（设置半连接队列 backlog）
// 4. accept()           接收客户端连接（建立连接）
// 5. read()/write()     通信（收发数据） recv send
// 6. close()            关闭连接

int server_main() {
  struct sockaddr_in servaddr; // 用于存放ip和端口的结构
  char buff[BUFFSIZE];         // 用于收发数据

  // 对应伪代码中的sockfd = socket();
  sockfd = socket(AF_INET, SOCK_STREAM, 0); // 服务端监听套接字
  if (-1 == sockfd) {
    printf("Create socket error(%d): %s\n", errno, strerror(errno));
    return -1;
  }
  // END

  // 对应伪代码中的bind(sockfd, ip::port和一些配置);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 绑定所有本地 IP
  servaddr.sin_port = htons(DEFAULT_PORT);      // 设置端口并转为网络字节序
  if (-1 == bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
    printf("Bind error(%d): %s\n", errno, strerror(errno));
    return -1;
  }
  // END

  // 对应伪代码中的listen(sockfd);
  if (-1 == listen(sockfd, MAXLINK)) {
    printf("Listen error(%d): %s\n", errno, strerror(errno));
    return -1;
  }
  // END

  printf("Listening...\n");
  while (true) {
    signal(SIGINT, stopServerRunning); // 这句用于在输入Ctrl+C的时候关闭服务器
    // 对应伪代码中的connfd = accept(sockfd);
    connfd = accept(sockfd, NULL, NULL); // 未收到connect会阻塞
    if (-1 == connfd) {
      printf("Accept error(%d): %s\n", errno, strerror(errno));
      return -1;
    }
    // END

    bzero(buff, BUFFSIZE);
    // 对应伪代码中的recv(connfd, buff);
    recv(connfd, buff, BUFFSIZE - 1, 0);
    // END
    printf("Recv: %s\n", buff);
    // 对应伪代码中的send(connfd, buff);
    send(connfd, buff, strlen(buff), 0);
    // END
    // 对应伪代码中的close(connfd);
    close(connfd);
    // END
  }
  return 0;
}