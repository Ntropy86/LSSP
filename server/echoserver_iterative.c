#include<sys/types.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include <unistd.h>
main()
{
char buff[1024];
int sockfd,connfd,fd,n;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(5295);
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
bind(sockfd,(struct sockaddr*) &servaddr,sizeof(servaddr));
listen(sockfd,5);
for(;;)
{
connfd=accept(sockfd,(struct sockaddr*)NULL,NULL);
for(;;)
{
n=read(connfd,buff,1024);
if (n==0)
break;
write(connfd,buff,n);
}
close(connfd);
}
}
