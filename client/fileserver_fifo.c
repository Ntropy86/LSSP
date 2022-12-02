#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#define mode (S_IRUSR|S_IWUSR)
void client(int, int);
main(){
	int wfd, rfd;
	int fifo1, fifo2;
	wfd=open("fifo1",O_WRONLY);
	rfd=open("fifo2",O_RDONLY);
	client(rfd,wfd);
	unlink(fifo1);
	unlink(fifo2);
}
void client(int readfd, int writefd){
	char buff[1024];
	int len,n;
	fgets(buff,1024,stdin);
	len=strlen(buff);
	len--;
	write(writefd,buff,len);
	while((n=read(readfd,buff,1024))>0)
		write(1,buff,n);
}

