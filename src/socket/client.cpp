//
// Created by Vacant lot on 2025/4/23.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h>
//#include <sys/unistd.h>
#include <unistd.h>
#define BUFFSIZE 2048
#define SERVER_IP                                                              \
"192.168.19.12" // 指定服务端的IP，记得修改为你的服务端所在的ip
#define SERVER_PORT 16555 // 指定服务端的port

// 1. socket()           创建套接字
// 2. connect()           接收客户端连接（建立连接）
// 3. read()/write()     通信（收发数据） send recn
// 4. close()            关闭连接

int main() {
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        printf("Create socket error(%d): %s\n", errno, strerror(errno));
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);
    // 内核会自动选择一个空闲的本地端口和 IP 来绑定（相当于帮你自动 bind()）。所以客户端通常不需要手动调用 bind()。
    if (-1 == connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        printf("Connect error(%d): %s\n", errno, strerror(errno));
        return -1;
    }
    printf("Please input: ");
    scanf("%s", buff);
    send(sockfd, buff, strlen(buff), 0);
    bzero(buff, sizeof(buff));
    recv(sockfd, buff, BUFFSIZE - 1, 0);
    printf("Recv: %s\n", buff);
    close(sockfd);
    return 0;
}