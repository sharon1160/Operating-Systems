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
/* Map shared memory object */
    rptr = mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    rptr2 = mmap(NULL, sizeof(struct PIDHora), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
```


https://github.com/sharon1160/Operating-Systems/blob/cf6f6920911270272e5ace4ee8258d7608eb8cfe/Laboratorios/Laboratorio%2001/producer2.cpp#L108-L132

## Consumidor

Primero creamos nuevamente las estructuras "region" y "PIDHora" y creamos dos punteros a ambas estructuras rptr("region") y rptr2("PIDHora"), abrimos el segmento de memoria compartida para ambas estructuras pero con el permiso de solo leer mas no crear o escribir, luego colocamos mensajes en printf por si llega a haber un error al momento de abrir la memoria compartida. Posteriormente, mapeamos el segmento de memoria compartida en el espacio de direcciones del proceso tanto para el rptr( puntero a un struct "region") y  rptr2( puntero a un struct "PIDHora"), si hay un error en el mapeo, imprimimos mensaje de error al mapear. 
Luego hacemos uso de la plantilla de la sección 6.2 de la práctica de laboratorio , donde nos encontramos con el bucle infinito while, en cada iteración leemos el buffer de los procesos creados, dentro del while se actualiza la variable out, y realizamos un kill al proceso creado, finalmente mostramos en la terminal la información del consumidor y hacemos un sleep.
