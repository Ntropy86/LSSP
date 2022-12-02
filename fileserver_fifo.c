#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include <string.h>

#define mode (S_IRUSR|S_IWUSR)
void client(int, int);
void server(int, int);
main(){
	int readfd, writefd, id;
	int fifo1,fifo2;
	mkfifo("fifo1",mode);
	mkfifo("fifo2",mode);
	id=fork();
	if(id==0){
		readfd=open("fifo1",O_RDONLY,0);
		writefd=open("fifo2",O_WRONLY,0);
		server(readfd, writefd);
	}
	else{
		writefd=open("fifo1",O_WRONLY,0);
		readfd=open("fifo2",O_RDONLY,0);
		client(readfd,writefd);
	}
	unlink ("fifo1");
	unlink ("fifo2");
}
void client(int readfd, int writefd){
	char buff[1024];	
	int n,len;
	fgets(buff,1024,stdin);
	len=strlen(buff);
	len--;
	write(writefd,buff,len);
	while((n=read(readfd,buff,1024))>0)
		write(1,buff,n);
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
