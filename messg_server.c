#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define BUFFER_SIZE 1024
#define LENGTH_OF_LISTEN_QUEUE 20

int main(){
    //创建服务器端套接字
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(6000);

    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket < 0){
       printf("Create server_socket Failed!\n");
       exit(1);
    }


    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))){
       printf("Bind Failed\n");
       exit(1);
    }

    if(listen(server_socket,LENGTH_OF_LISTEN_QUEUE)){
       printf("Listen Failed");
       exit(1);
    }

    while (1){
  		struct sockaddr_in client_addr;
  		socklen_t length = sizeof(client_addr);
  		int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
  		if(new_server_socket < 0){
  			printf("Server Accept Failed!\n");
  			break;
  		}
  		char buffer[BUFFER_SIZE];
  		memset(buffer,0, BUFFER_SIZE);
  		length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
  		if(length<0){
  			printf("Server Recieve Data Failed!\n");
  			break;
  		}
      printf("%s\n",buffer);
      //close
    close(server_socket);
    return 0;
}
}
