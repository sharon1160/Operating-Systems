#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <string.h>
#include <sys/types.h>
#include <setjmp.h> // for long jump

jmp_buf env;


void handler(int sig, siginfo_t *siginfo, void *context)
{
    if(siginfo){
        // mostrando la informacion de siginfo
        printf("Signal number -> %d \n", siginfo->si_signo);
        printf("Signal code -> %d\n", siginfo->si_code);
        printf("Errno value -> %d\n", siginfo->si_errno);
        printf("Sending process ID -> %d\n", siginfo->si_pid);
    }
    longjmp(env, 1234);
}



int main(int argc, char **argv)
{

    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;

    // registrando señales que manda el proceso hijo
    sigaction(SIGHUP, &act, NULL); 
    sigaction(SIGINT, &act, NULL); 
    sigaction(SIGQUIT, &act, NULL); 
    sigaction(SIGILL, &act, NULL); 
    sigaction(SIGABRT, &act, NULL); 
    sigaction(SIGFPE, &act, NULL); 
    sigaction(SIGKILL, &act, NULL); 
    sigaction(SIGSEGV, &act, NULL); 
    sigaction(SIGPIPE, &act, NULL); 
    sigaction(SIGALRM, &act, NULL); 
    sigaction(SIGTERM, &act, NULL); 
    sigaction(SIGCHLD, &act, NULL); 
    sigaction(SIGSTOP, &act, NULL); 
    sigaction(SIGTSTP, &act, NULL); 

    pause();

    while (1)
        ;

    return 0;
}