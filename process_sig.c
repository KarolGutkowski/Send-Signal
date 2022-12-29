#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define ERR(source)                                                                                                    \
	(fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), perror(source), kill(0, SIGKILL), exit(EXIT_FAILURE))

int map_signal(char* signal_name)
{
    // in this case we assume we were given signle digit for signal number
    // improve this further so you can have more than 9 as a value
    if(strlen(signal_name)==1) 
        return atoi(signal_name);

    if(strcmp(signal_name,"SIGKILL")==0)
        return SIGKILL;
    else if(strcmp(signal_name,"SIGINT")==0)
        return SIGINT;
    else if(strcmp(signal_name,"SIGQUIT")==0)
        return SIGQUIT;
    else if(strcmp(signal_name, "SIGUSR1")==0)
        return SIGUSR1;
    else if(strcmp(signal_name,"SIGUSR2")==0)
        return SIGUSR2;
    else
        ERR("Provided signal type not supported");
    return EXIT_FAILURE;
}