# Lab02 - Señales
Identifica y aplica los principios de creación de procesos (fork, exec y waitpid).
También se aplican los conocimientos de tratamiento de señales en el sistema
Linux.
## Integrantes 
- Castillo Caccire, Kemely Francis
- Chullunquía Rosas, Sharon Rossely
### Padre :man:
- Será responsable de crear un proceso hijo usando la llamada fork () .
```C
	pid_t pid;
	// creamos hijo
	pid = fork();	
```
- Después de la creación de cada proceso hijo, por medio de la
llamada exec ( execlp ) reemplazará el código del programa hijo, para
ejecutar el programa hijo.c
```C
        execlp("./hijo","hijo",(char *) 0);		
```
- El programa deberá esperar a que termine la ejecución de los
programas hijo.c y nieto.c . Usar waitpid ().
```C
       waitpid(pid, &stat, 0);
				
```
### Hijo :adult:
- El programa hijo.c creará un proceso hijo, por medio de la llamada
fork () .
```C
   pid_t pid;
   pid = fork();				
```
- Después de la creación de cada proceso hijo, por medio de la
llamada exec ( execlp ) reemplazará el código del programa hijo, para
ejecutar el programa nieto.c
```C
   if(pid == 0)
        execlp("./nieto", NULL);		
			
```
- El programa hijo enviará al programa nieto (del cual conoce el
PID), cada una de las señales listadas en Señales soportadas.
- Detectar si el proceso nieto muere (Hint: detectar la señal
respectiva), y lanzarlo de nuevo, hasta completar el envío de todas
las señales requeridas.
```C
    int signals[] = {1, 2, 3, 4, 6, 8, 9, 11, 13, 14, 15, 17, 19, 20};
    int status;
    
    ...
    
   for (size_t i = 0; i < 14; ++i)
    {
        sleep(1);
        kill(pid, signals[i]);
        int b = waitpid(pid, &status , WNOHANG | WUNTRACED);
        if(b != 0)
        {
            //printf("Signal no tratable 9 o 19\n");
			printf("Signal no tratable %d\n",i);
            kill(pid, 9);
			printf("Signal no tratable edb%d\n");
            pid = fork();
            if(pid == 0)
                execlp("./nieto", NULL);
        }
    }

    sleep(1);
    kill(pid, 9);
    waitpid(pid, &status, 0);    
		
		
```

### Nieto :boy:
- En este programa serán redefinidos los manejadores ( handlers ) de
las señales indicadas en la sección Señales soportadas.
- El tratamiento de señales debe usar la función sigaction () . No usar
la función signal ().
```C
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
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
			
		
```
- Para cada señal recibida mostrar la siguiente información, obtenida
de siginfo_t (cuando esté disponible)
```C
    if(siginfo){
        printf("Signal number -> %d \n", siginfo->si_signo);
        printf("Signal code -> %d\n", siginfo->si_code);
        printf("Errno value -> %d\n", siginfo->si_errno);
        printf("Sending process ID -> %d\n", siginfo->si_pid);
    }
    longjmp(env, 1234);		
		
		
```