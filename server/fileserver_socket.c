#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdio.h>
#include <unistd.h>
int main()
{
	int sockfd,connfd,n,fd;
	char buff[1024];
	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5295);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
        ;
    listen(sockfd, 5);
    for(;;)
	{
		connfd=accept(sockfd,(struct sockaddr *)NULL,NULL);
		n=read(connfd,buff,1024);
		buff[n]='\0';
		fd=open(buff,O_RDONLY);
		while((n=read(fd,buff,1024))>0)
			write(connfd,buff,n);
		close(connfd);
	}
}
