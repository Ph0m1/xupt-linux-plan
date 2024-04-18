#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

void mycd(char *argv[]);

int main(int argc, char *argv[])
{
    mycd(argv);
    return 0;
}

void mycd(char *argv[])
{

    char *path;
    path = getcwd(NULL, 0);
    if (strcmp(argv[1],"~") == 0)
    {
        char*home=getenv("HOME");
        chdir(home);
        free(home);   
    }
    else if (strcmp(argv[1],"-") == 0)
    {
        puts(path);
    }
    else
    {
        chdir(argv[1]);
        
    }
    path=getcwd(NULL,0);
    puts(path);
    free(path);
}