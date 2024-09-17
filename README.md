## Consigna

Se solicita escribir un programa que permita leer ambos archivos almacenándolos en memoria RAM (usar sólo la memoria necesaria).

Al iniciarse el programa, debe leer ambos archivos e informar para cada uno de ellos: cantidad de registros y cantidad total de bytes leídos.

Luego debe mostrar un menú cíclico que permita realizar las siguientes operaciones:

1. Buscar un paciente por su apellido y mostrar su nombre, nro de HC y todos sus registros de datos vitales.

2. Mostrar los valores promedio de todos los signos vitales (FC, PAS, PAD, Temp)

3. Generar un archivo llamado reporte.txt que contenga los apellidos y nombres de los pacientes cuya temperatura difiera en un 5% o más respecto de la temperatura promedio. El archivo debe contener un paciente por renglón.

## Ejecutar

```
gcc -o build/main main.c && build/main
```
