#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <fcntl.h>
#include <wait.h>
#include <ctype.h>

#define Max 2048
#define BLUE "\033[1;32;34m"
#define BLUE2 "\033[;32;34m"
#define YELLOW "\33[1;32;33m"
#define GREEN "\033[0;32;32m"
#define GREEN2 "\033[0;35;32m"
#define RED "\033[1;32;31m"
#define NONE "\033[0m"

// int cin = 0;
char formatPath[Max];
int pass =0;

void showhistory();
// 获取用户组信息
void getid(char *str);
// 屏蔽信号
void getit();

// cd
void mycd(char *argv[]);

// void exec(char *arg[]);

void readltok(char *stdinn, char *argv[]);
void truedir(char *path);

void prosses(char *command);
char *trim(char *str);
char *rtrim(char *str);
char *ltrim(char *str);
void cancelchar(char *command, char n);
int main(int argc, char *argv[])
{
    getit();
    char *readlineonscreen = (char *)malloc(sizeof(char) * Max);
    char *stdinn = NULL;

    while (1)
    {
        fflush(stdout);
        fflush(stdin);
        printf("\n");
        getid(readlineonscreen);
        char *arg[Max] = {NULL};
        stdinn = readline(readlineonscreen);
        add_history(stdinn);
        if (stdinn == "\n" || stdinn == NULL)
            continue;
        if (strcmp(stdinn, "exit") == 0)
        {
            break;
        }
        char *command;

        int cnt = 0;
        pass = 0;
        if (strstr(stdinn, "&") != NULL)
        {
            cancelchar(stdinn, '&');
            pass = 1;
        }
        command = strdup(stdinn);
        command[strcspn(command, "\n")] = 0;
        readltok(stdinn, arg);
        if (arg[0] == NULL)
            continue;
        if (pass == 0)
        {
            if (strcmp(arg[0], "cd") == 0 || strcmp(arg[0], "chdir") == 0)
            {
                mycd(arg);
            }
            else
            {   
                prosses(command);
            }
        }
        else
        {
            int pid;
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit;
            }
            else if (pid == 0)
            {
                if (strcmp(arg[0], "cd") == 0 || strcmp(arg[0], "chdir") == 0)
                {
                    mycd(arg);
                }
                else
                {
                    prosses(command);
                    for (int i = 0; arg[i] != NULL; i++)
                        free(arg[i]);
                }
                exit(0);
            }
            else if (pid > 0 && pass == 1)
            {
                
                int stat;
                usleep(10000);
                waitpid(pid,&stat,WNOHANG);
                printf("[1] %d\t%s\n", pid, command);
                
            }
            
        }
        for (int i = 0; arg[i] != NULL; i++)
            free(arg[i]);
        free(stdinn);
        free(command);
        fflush(stdout);
    }
    free(stdinn);
    free(readlineonscreen);
}
void cancelchar(char *command, char n)
{
    char *p;
    for (p = command; *p != '\0'; p++)
        if (*p != n)
            *command++ = *p;
    *command = '\0';
}
void mycd(char *arg[])
{
    char *path;
    path = getcwd(NULL, 0);
    if (arg[1] == NULL || strcmp(arg[1], "~") == 0)
    {
        char *home = getenv("HOME");
        chdir(home);
        // free(home);
    }
    else if (strcmp(arg[1], "-") == 0)
    {
        // puts(formatPath);
        char currentPath[Max];
        strcpy(currentPath, formatPath);
        truedir(currentPath);
        puts(currentPath);
        chdir(formatPath);
    }
    else
    {
        if(chdir(arg[1]) == -1 ){
            printf("不存在的目录: %s",arg[1]);
        }
    }
    strcpy(formatPath, path);
    // formatPath = strdup(path);
    free(path);
}

void getid(char *str)
{
    // 获取当前用户
    uid_t uid;
    uid = getuid();
    struct passwd *pwd;
    pwd = getpwuid(uid);

    // 获取主机名
    char hostname[Max + 1];
    if (gethostname(&hostname[0], Max) == -1)
    {
        perror("gethostname");
        exit;
    }

    // 获取当前所在目录
    char *path = NULL;
    path = getcwd(NULL, 0);
    truedir(path);

    // 获取当前时间
    time_t t;
    time(&t);
    struct tm *tm;
    tm = localtime(&t);
    sprintf(str, "\001" BLUE "# " BLUE2 "%s" NONE " @ " GREEN "%s" NONE " in " YELLOW "%s" NONE " [%d:%d:%d]\n\001%s\002", pwd->pw_name, hostname, path, tm->tm_hour, tm->tm_min, tm->tm_sec, uid == 1 ? RED "# " NONE : RED "$ " NONE "\002");
    free(path);
    fflush(stdout);
}

void readltok(char *stdinn, char *argv[])
{
    char *tok = strtok(stdinn, " \n");
    if (tok == NULL)
        return;
    int i = 0;

    while (tok != NULL && i < Max)
    {
        // strcpy(argv[i],tok);
        argv[i] = strdup(tok);
        tok = strtok(NULL, " \n");
        i++;
    }
    argv[i] = NULL;
}

void truedir(char *path)
{
    char *token = getenv("HOME");
    char *p = NULL;
    int len1 = strlen(token);
    int len2 = strlen(path);
    p = strstr(path, token);
    if (p == NULL)
        return;
    sprintf(path, "~%s", p + len1);
}

void getit()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
}

void prosses(char *command)
{
    char *token;
    char *saveptr;
    char *commands[Max];
    int i = 0;

    token = strtok_r(command, "|", &saveptr);
    while (token != NULL && i < Max)
    {
        commands[i] = token;
        token = strtok_r(NULL, "|", &saveptr);
        i++;
    }
    commands[i] = NULL;
    int num_cmds = i;

    int fds[num_cmds - 1][2];

    for (i = 0; i < num_cmds - 1; i++)
    {
        pipe(fds[i]);
    }

    for (i = 0; i < num_cmds; i++)
    {
        int pd = fork();
        if (pd == 0)
        {
            if (i != 0)
            {
                dup2(fds[i - 1][0], STDIN_FILENO);
                close(fds[i - 1][0]);
            }
            if (i != num_cmds - 1)
            {
                dup2(fds[i][1], STDOUT_FILENO);
                close(fds[i][1]);
            }
            for (int j = 0; j < num_cmds - 1; j++)
            {
                close(fds[j][0]);
                close(fds[j][1]);
            }

            char *cmd = trim(commands[i]);
            char *redirect_output = strstr(cmd, ">");
            char *redirect_append = strstr(cmd, ">>");
            char *redirect_input = strstr(cmd, "<");

            if (redirect_output != NULL)
            {
                char *cmd_part = strtok(cmd, ">");
                char *output_file = strtok(NULL, ">");
                output_file = trim(output_file);
                int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                cmd = trim(cmd_part);
            }
            else if (redirect_append != NULL)
            {
                char *cmd_part = strtok(cmd, ">>");
                char *output_file = strtok(NULL, ">>");
                output_file = trim(output_file);
                int fd = open(output_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
                if (fd == -1)
                {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                cmd = trim(cmd_part);
            }
            else if (redirect_input != NULL)
            {
                char *cmd_part = strtok(cmd, "<");
                char *input_file = strtok(NULL, "<");
                input_file = trim(input_file);
                int fd = open(input_file, O_RDONLY);
                if (fd == -1)
                {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                cmd = trim(cmd_part);
            }

            char *arg[Max];
            readltok(cmd, arg);
            execvp(arg[0], arg);
            perror("execvp failed");
            free(command);
            exit(1);
        }
        else if (pd < 0)
        {
            perror("fork failed");
            free(command);
            exit(1);
        }
        
    // free(command);
    }

    for (i = 0; i < num_cmds - 1; i++)
    {
        close(fds[i][0]);
        close(fds[i][1]);
    }
    for (i = 0; i < num_cmds; i++)
    {
        wait(NULL);
    }
}

char *rtrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    int len = strlen(str);
    char *p = str + len - 1;
    while (p >= str && isspace(*p))
    {
        *p = '\0';
        --p;
    }
    return str;
}
char *ltrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    int len = 0;
    char *p = str;
    while (*p != '\0' && isspace(*p))
    {
        ++p;
        ++len;
    }

    memmove(str, p, strlen(str) - len + 1);

    return str;
}
// 去除首尾空格
char *trim(char *str)
{
    str = rtrim(str);
    str = ltrim(str);

    return str;
}