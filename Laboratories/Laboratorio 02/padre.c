#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdbool.h> // true, false



int main()
{
	int stat;
	pid_t pid;
	// creamos hijo
	pid = fork();

	if (pid < 0)
	{
		printf("Hijo no creado\n");
		exit(-1);
	}
	else{ 
		if (pid == 0) /* Estamos en el proceso hijo. */
		{
			printf("Soy el hijo :) .\n");
			/* le mandamos execlp el programa hijo*/
			execlp("./hijo","hijo",(char *) 0);
			/*  Si execlp() es exitoso, no deberia mostrar la siguiente linea. */
			printf("La llamada a execlp() no fue exitosa.\n");
			exit(127);
		}
		else  /* Estamos en el proceso padre */
		{
			printf("Soy el padre :) . El hijo termino justo ahora.  Ahora terminaré.\n");
			exit(0);
		}
	}

	waitpid(pid, &stat, 0); // espera a que el hijo termine
	return 0;  
}
