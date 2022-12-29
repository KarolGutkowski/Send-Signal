#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ftw.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "process_sig.h"
#define MAXFD 1

#define ERR(source)                                                                                                    \
	(fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), perror(source), kill(0, SIGKILL), exit(EXIT_FAILURE))

char *process_name;
pid_t signal_destination = -1;
void usage(char *name)
{
	fprintf(stderr, "USAGE: %s -p [target_process] \n", name);
	exit(EXIT_FAILURE);
}

int find_pid(const char* name, const struct stat* s, int type, struct FTW *f)
{
    if(strstr(name,"/comm")!=NULL && strstr(name,"/task")==NULL)
    {
        int fd;
        if((fd=open(name,O_RDONLY))==-1)
            ERR("open()");

        int count;
        char buf[100];
        if((count=read(fd,buf,sizeof(process_name)))==-1)
            ERR("read");

        if(strstr(buf,process_name)!= NULL)
        {
            int fd2;
            char *id;
            if((fd2=open("./stat",O_RDONLY))==-1)
                ERR("open()");

            char buf2[8];
            if((count=read(fd2,buf2,7))==-1)
                ERR("read");

            id = strtok(buf2," ");
            if(signal_destination==-1)
                signal_destination=atoi(id);
            if(close(fd2))
                ERR("close");
        }
        if(close(fd))
            ERR("close");

    }
    return 0;
}


int main(int argc, char** argv)
{
    int c;
    char* signal_name;
    while((c=getopt(argc, argv,"p:s:"))!=-1)
    {
        switch (c)
        {
        case 'p':
            process_name = optarg;
            break;
        case 's':
            signal_name = optarg;
            break;
        default:
            break;
        }
    }

    if(!process_name)
        usage(argv[0]);
    if(!signal_name)
        signal_name = "SIGKILL";

    sig_atomic_t signal = map_signal(signal_name);
    if(nftw("/proc",find_pid,MAXFD,FTW_PHYS|FTW_CHDIR)==0){}

    printf("PID=%d\n", signal_destination);
    if(signal_destination!=-1)
        kill(signal_destination,signal);
    else
        printf("No such process currently running.\n");
    printf("%s\n", process_name);
    return EXIT_SUCCESS;
}