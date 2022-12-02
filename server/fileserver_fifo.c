#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>

#define mode (S_IRUSR|S_IWUSR)
void server(int, int);
main(){
	int fifo1, fifo2;
	int rfd, wfd;
	mkfifo("fifo1",mode);
	mkfifo("fifo2",mode);
	rfd=open("fifo1",O_RDONLY,0);
	wfd=open("fifo2",O_WRONLY,0);
	server(rfd,wfd);
}
void server(int readfd, int writefd){
	int n;
	char buff[1024];
	int fd;
	n=read(readfd,buff,1024);
	buff[n]='\0';
	fd=open(buff,O_RDONLY);
	while((n=read(fd,buff,1024))>0)
		write(writefd,buff,n);
}


