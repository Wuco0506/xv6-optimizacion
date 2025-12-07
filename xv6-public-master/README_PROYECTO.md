# Proyecto Sistemas Operativos - xv6

## Optimizaciones implementadas

### 1. Lottery Scheduler

Se reemplazó el planificador Round Robin por un planificador por
lotería. Cada proceso tiene un número de "tickets" que determinan su
probabilidad de ser ejecutado.

Archivos modificados: - proc.c - proc.h

### 2. Optimización de memoria con cache por CPU

Se implementó una cache local de páginas por CPU en el archivo kalloc.c
para reducir el acceso al lock global.

Archivo modificado: - kalloc.c

## Compilación

``` bash
make
make qemu-nox
```

## Integrantes

-   Jacobo Woodcock Ortiz -- Código: 2438024-2724
-   Sebastian Arango -- Código: 2435051-2724

## Notas

Este proyecto corresponde a una modificación académica del sistema
operativo xv6 con fines educativos.
