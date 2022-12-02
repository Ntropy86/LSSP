#include<fcntl.h>
#include<stdio.h>

#include<sys/stat.h>
#include <unistd.h>
#include <string.h>

void client(int readfd, int writefd){
	char buff[1024];
	int len,n;
	fgets(buff,1024,0);
	len=strlen(buff);
	len--;
	write(writefd,buff,len);
	while((n=read(readfd,buff,1024))>0)
		write(1,buff,n);
}
void server(int readfd, int writefd){
	int n,fd;
	char buff[1024];
	n=read(readfd,buff,1024);
	buff[n]=0;
	fd=open(buff,O_RDONLY);
	while((n=read(fd,buff,1024))>0)
		write(writefd,buff,n);
}
int main(){
	int id;
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	id=fork();
	if(id==0){
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0],pipe2[1]);
	}
	else{
		close(pipe2[1]);
		close(pipe1[0]);
		client(pipe2[0],pipe1[1]);
	}
}
