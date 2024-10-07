# Demo OpenGL

## Entorno y Librerías

El proyecto de OpenGL fue desarrollado y ejecutado en Fedora Linux versión 40. Para poder compilar el proyecto hace falta tener instaladas las siguientes librerías

* glfw (tanto x86_64 como i686)
* glfw_devel (tanto x86_64 como i686)
* mesa-libGL-devel (tanto x86_64 como i686)

Además generalmente se recomienda tener instalados los grupos de DNF "Development Tools" y "Development Libraries"

## Cómo Ejecutar

Para compilar se puede hacer uso del Makefile proveído en este mismo directorio. Esto es 

```
make
```

Posteriormente se puede ejecutar el programa con el binario resultante haciendo 

```
./main
```