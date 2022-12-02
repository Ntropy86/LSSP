#include<fcntl.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
int main(int argc,char **argv)
{
	int sockfd,n,len;
	char buff[1024];
	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5295);
     inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
     connect(sockfd,(struct sockaddr  *)&servaddr,sizeof(servaddr));
	fgets(buff,1024,stdin);
	len=strlen(buff);
	len--;
	write(sockfd,buff,len);
	while((n=read(sockfd,buff,1024))>0)
		write(1,buff,n);
}


