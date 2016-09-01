#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024


int main(int argc, char  **argv) {
  /* code */
  if (argc != 2){
		printf("Usage: %s ServerIPAddress\n",argv[0]);
		exit(1);
	}
  //设置一个socket 地址，代表客户端地址，端口
  struct sockaddr_in client_addr;
  memset(&client_addr,0,sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(0);
  client_addr.sin_addr.s_addr = htons(INADDR_ANY);

  //创建socket;
  int client_socket = socket(AF_INET,SOCK_STREAM,0);
  if(client_socket < 0){
    printf("Create Socket Failed!\n");
    exit(1);
  }

  //把客户机的socket和客户机的socket地址结构联系起来
  if(bind(client_socket,(struct sockaddr *)&client_addr,sizeof(client_addr))){
    printf("Bind Socket Failed\n");
    exit(1);
  }

  struct sockaddr_in server_addr;
  socklen_t server_addr_length = sizeof(server_addr);
  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(6000);
//连接服务器socket
if(connect(client_socket,(struct sockaddr*)&server_addr,server_addr_length)<0){
  printf("Connect Failed!\n");
  exit(1);
}

printf("Please input message to send:\n");
int ret = 0;
char buffer[BUFFER_SIZE];
memset(buffer,0,BUFFER_SIZE);
scanf("%s",buffer);
ret = send(client_socket,buffer,BUFFER_SIZE,0);
if(ret < 0){
  printf("Send message Failed!");
}

//关闭套接字
 close(client_socket);
 return 0;
}
