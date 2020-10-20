# Lab01 - Productor/Consumidor :smiley:
Principles of creation and completion of processes, shared memory and communication between those.

## Productor
Creamos dos punteros a las estructuras `region` y `PIDHora`.
```c
struct region {
    int len;
    char buf[MAX_LEN];
};

struct PIDHora {
    pid_t pid;
    char *tiempo;
};
```
A continuación creamos objetos de memoria compartida con los nombres `/myregion` y `/PIDHora`. Los cuales mapearemos a las estructuras declaradas previamente, como lo muestra el siguiente código:
```c
rptr = mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
rptr2 = mmap(NULL, sizeof(struct PIDHora), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
```
Luego, dentro del bucle while creamos un hijo con la funcion fork(), guardamos el tiempo en el que se creo el proceso hijo en un array llamado output, para luego mostrarlo en la terminal; imprimimos la información del proceso hijo y padre, después actualizamos la variable next_produced guardando en ella el pid del proceso hijo, para luego pasarlo al buffer, el cual esta dentro de la estructura de la memoria compartida; finalmente realizamos un sleep.

```c
while( true ) {
	int s = rand() % 5 + 1;

	tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%H:%M:%S",tlocal);
	
	printf("%s\n",(char *)rptr->buf);
	
	while( in  ==  out );
	next_consumed =  buffer [ out ] ;
	out =  ( out + 1) % BUFFER_SIZE ;
	printf("[ %s ] C( %d ) : Matando Proceso %d ( vivió %s ) \n", output , getpid() , rptr2->pid, rptr2->tiempo);
	kill(next_consumed.value , SIGKILL);
	sleep (s);
}
```

## Consumidor

Primero creamos nuevamente las estructuras `region` y `PIDHora` y creamos dos punteros a ambas estructuras `rptr("region")` y `rptr2("PIDHora")`.
Abrimos el segmento de memoria compartida para ambas estructuras pero con el permiso de solo leer mas no crear o escribir, luego colocamos mensajes en `printf` por si llega a haber un error al momento de abrir la memoria compartida.
```c
fd = shm_open ("/myregion", O_RDONLY,  S_IRUSR | S_IWUSR);
fd2 = shm_open ( "/PIDHora" , O_RDONLY, S_IRUSR | S_IWUSR );
```
Posteriormente, mapeamos el segmento de memoria compartida en el espacio de direcciones del proceso tanto para el `rptr` (puntero a un struct "region") y  `rptr2` (puntero a un struct "PIDHora"), si hay un error en el mapeo, imprimimos mensaje de error al mapear.
```c
rptr = mmap(NULL, sizeof(struct region), PROT_READ , MAP_SHARED, fd, 0);
rptr2 = mmap(NULL, sizeof(struct PIDHora), PROT_READ, MAP_SHARED, fd2, 0);

if ( rptr == MAP_FAILED ){
	/* Handle error */
	printf("\n Failed to map the shared memory 1\n");
	return -1;
}

if ( rptr2 == MAP_FAILED ){
	/* Handle error */
	printf("\n Failed to map the shared memory 2\n");
        return -1;
}
```
Luego hacemos uso de la plantilla de la sección 6.2 de la práctica de laboratorio , donde nos encontramos con el bucle infinito while, en cada iteración leemos el buffer de los procesos creados, dentro del while se actualiza la variable out, y realizamos un kill al proceso creado, finalmente mostramos en la terminal la información del consumidor y hacemos un sleep.
```c
while( true ) {
	int s = rand() % 5 + 1;
	tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%H:%M:%S",tlocal);
	printf("%s\n",(char *)rptr->buf);

	while( in  ==  out );
	/* do  nothing */
	next_consumed =  buffer [ out ] ;
	out =  ( out + 1) % BUFFER_SIZE ;
	printf("[ %s ] C( %d ) : Matando Proceso %d ( vivió %s ) \n", output , getpid() , rptr2->pid, rptr2->tiempo);
	kill(next_consumed.value , SIGKILL);
	sleep (s);
}
```
