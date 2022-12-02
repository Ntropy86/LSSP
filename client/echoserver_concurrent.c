#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
main(int argc, char **argv)
{
int sockfd,n,len;
char buff[1024];
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(5295);
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
connect(sockfd,(struct sockaddr*) &servaddr,sizeof(servaddr));
while (fgets(buff,1024,stdin)!=0)
{
len=strlen(buff);
write(sockfd,buff,len);
n=read(sockfd,buff,1024);
write(1,buff,n);
}
}

