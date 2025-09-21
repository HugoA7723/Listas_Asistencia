# Listas_Asistencia
¿Qué es este programa?
Este programa es una aplicación de consola en lenguaje C diseñada para gestionar la lista de asistencia de alumnos en un grupo o clase. Permite crear, modificar, eliminar y consultar la lista de alumnos, así como registrar y visualizar la asistencia de cada uno.

# ¿Para qué sirve?
El programa facilita el control y seguimiento de la asistencia de los alumnos. Es útil para profesores, administrativos o cualquier persona que necesite llevar un registro digital sencillo de quiénes asistieron a una clase o evento.

# ¿Cómo funciona?
Creación de la lista de alumnos:
Puedes crear una nueva lista ingresando la cantidad de alumnos, su clave y nombre. Esta información se guarda en un archivo llamado alumnos.dat para que no se pierda al cerrar el programa.

## Carga automática de la lista:
Al iniciar el programa, si ya existe una lista guardada, se carga automáticamente desde el archivo, permitiendo continuar el trabajo anterior.

## Registro de asistencia:
Puedes tomar la asistencia de los alumnos, indicando para cada uno si asistió o no. Esta información se guarda en el archivo asistencia.dat.

## Consulta de la lista:
Puedes imprimir la lista de alumnos y ver si la asistencia ya fue tomada. Si no se ha registrado la asistencia de un alumno, el programa lo indicará claramente.

## Modificación y eliminación:
Es posible modificar los datos de un alumno o eliminarlo de la lista. También puedes eliminar toda la lista de asistencia si lo deseas.

## Persistencia de datos:
Toda la información se guarda en archivos binarios, por lo que los datos se conservan aunque cierres y vuelvas a abrir el programa.

### Menú de opciones
El programa muestra un menú con las siguientes opciones:

1 - Crear lista de asistencia
2 - Tomar asistencia
3 - Imprimir lista de asistencia
4 - Modificar alumno
5 - Eliminar alumno
6 - Eliminar de asistencia
7 - Salir
Solo debes ingresar el número de la opción que deseas realizar y seguir las instrucciones en pantalla.
