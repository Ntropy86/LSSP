#include<signal.h>
#include<stdio.h>
void catch(int signo);
main(){
	signal(SIGINT,catch);
	signal(SIGQUIT,catch);
	signal(SIGTERM,catch);
             signal(SIGHUP,catch);
	for(;;)
	pause();
}	
void catch(int signo){
	if(signo==SIGINT)
		printf("Recieved Interrupt Signal\n");
	else if(signo==SIGQUIT)
		printf("Recieved Quit Signal\n");
	else if(signo==SIGTERM)
		printf("Recieved Terminate Signal\n");
             else if(signo==SIGHUP)
		printf("Recieved HUP Signal\n");

}


