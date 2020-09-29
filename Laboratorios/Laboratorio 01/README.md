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


