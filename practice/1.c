#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
    
    static void sigHuandler(int sig){
        printf("哦！\n");  
    }
int main(int argc,char *argv[]){
   int j = 0;
   if(signal(SIGINT,sigHuandler) == SIG_ERR){
    perror("signal");
    exit(1);
   }
    for(j=0;;j++){
        printf("%d\n",j);
        sleep(3);//延时3s
    }
    return 0;
}