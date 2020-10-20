#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdbool.h> // true, false

int main()
{
    // señales en números
    int signals[] = {1, 2, 3, 4, 6, 8, 9, 11, 13, 14, 15, 17, 19, 20};
	int status;

    pid_t pid;
    // creamos nieto
    pid = fork();

    if(pid == 0)
        execlp("./nieto", NULL); // se pasa al proceso nieto

    for (size_t i = 0; i < 14; ++i) // recorre la lista de señales en numeros
    {
        sleep(1);
        kill(pid, signals[i]); // enviando señales al programa nieto.c

        int b = waitpid(pid, &status , WNOHANG | WUNTRACED); // deteccion del estado del nieto
        if(b != 0) // si el nieto muere
        {
			printf("Senial %d\n",i); // mostrando la señal en la que se encuentra
            kill(pid, 9); // matamos la señal
			printf("Senial dificil de tratar %d\n");
            pid = fork(); // creando nuevamente el proceso nieto
            if(pid == 0) // si se crea exitosamente el proceso nieto
                execlp("./nieto", NULL); // se pasa al proceso nieto
        }
    }

    kill(pid, 9);
    waitpid(pid, &status, 0);// esperamos al proceso nieto
    return 0;
}