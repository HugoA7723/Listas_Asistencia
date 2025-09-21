#include "Asistencia.h"
//
// Funcion extra hecha con copilot
void Cargar_lista(TAlumnos **alumnos) 
{
    FILE *archivo = fopen("alumnos.dat", "rb");
    if (!archivo)
    {
        return; 
    }

    TAlumnos temp;
    while (fread(&temp, sizeof(TAlumnos), 1, archivo)) 
    {
        TAlumnos *nuevo = (TAlumnos *)malloc(sizeof(TAlumnos));
        *nuevo = temp;
        nuevo -> sig = NULL;

        if (*alumnos == NULL) 
        {
            *alumnos = nuevo;
        } 
        else 
        {
            TAlumnos *aux = *alumnos;
            while (aux -> sig != NULL)
                aux = aux -> sig;
                aux -> sig = nuevo;
        }
    }
    fclose(archivo);
}

int main()
{
    printf("Programa para gestionar lista de asistencia.\n");

    int alumnos, opcion;
    TAlumnos * alumnos_lista = NULL;
    Cargar_lista(&alumnos_lista);

    while (opcion != 7)
    {
        printf("Selecciona la opcion a realizar:\n1: Crear lista de asistencia\n2: Tomar asistencia\n3: Imprimir lista de asistencia\n4: Modificar alumno\n5: Eliminar alumno\n6: Eliminar de asistencia\n7: Salir\n");
        if( !(scanf("%d", &opcion))) //Instruccion hecha con copilot
        {
            printf("Entrada invalida. Por favor ingrese un numero.\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcion)
        {
            case 1:
                if(alumnos_lista != NULL)
                {
                    printf("Ya existe una lista de asistencia, ahora puedes modificar la lista o eliminar la lista.\n");
                    break;
                }
                printf("Ingrese la cantidad de alumnos: ");
                scanf("%d", &alumnos);
                printf("\n");
                Inicializar_alumnos(alumnos, &alumnos_lista);
                break;

            case 2:
                if(alumnos_lista == NULL)
                {
                    printf("No existe una lista de asistencia, primero crea una lista.\n");
                    break;
                }
                Tomar_asistencia(alumnos_lista);
                break;

            case 3:
                if(alumnos_lista == NULL)
                {
                    printf("No existe una lista de asistencia, primero crea una lista.\n");
                    break;
                }
                Imprimir_lista(alumnos_lista);
                break;
            case 4:
                if(alumnos_lista == NULL)
                {
                    printf("No existe una lista de asistencia, primero crea una lista.\n");
                    break;
                }
                Modificar_alumno(alumnos_lista);
                break;
            case 5:
                if(alumnos_lista == NULL)
                {
                    printf("No existe una lista de asistencia, primero crea una lista.\n");
                    break;
                }
                Eliminar_alumno(&alumnos_lista);
                break;
            case 6:
                if(alumnos_lista == NULL)
                {
                    printf("No existe una lista de asistencia, primero crea una lista.\n");
                    break;
                }
                Eliminar_asistencia(&alumnos_lista);
                break;
            case 7:
                printf("Saliendo del programa.\n");
                exit(1);
            default:
                printf("Opcion invalida, intente de nuevo.\n");
                break;
        }
    }
}

void Inicializar_alumnos(int A, TAlumnos ** alumnos)
{
    FILE *archivo = fopen("alumnos.dat", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < A; i++)
    {
        TAlumnos *nuevo = (TAlumnos *)malloc(sizeof(TAlumnos));
        if (nuevo == NULL)
        {
            printf("Error al asignar memoria.\n");
            fclose(archivo);
            return;
        }

        printf("\nAlumno %d\n", i + 1);
        printf("Clave: ");
        scanf("%d", &nuevo -> clave);
        getchar(); 

        printf("Nombre: ");
        fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
        nuevo -> asistio = -1;
        nuevo -> sig = NULL;

        if (*alumnos == NULL)
        {
            *alumnos = nuevo;
        }
        else
        {
            TAlumnos *aux = *alumnos;
            while (aux->sig != NULL)
                aux = aux -> sig;
                aux -> sig = nuevo;
        }

        fwrite(nuevo, sizeof(TAlumnos), 1, archivo);
    }

    fclose(archivo);
    printf("\n%d alumnos agregados y guardados en 'alumnos.dat'.\n", A);
    printf("\n");
}

void Tomar_asistencia(TAlumnos *cabecera)
{
    FILE *archivo = fopen("asistencia.dat", "wb"); 

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    TAlumnos *aux = cabecera;
    while (aux != NULL)
    {
        printf("\nAlumno: %s (Clave: %d)\n", aux -> nombre, aux -> clave);
        printf("¿Asistio? 1 = Si, 0 = No: ");
        scanf("%d", &aux->asistio);

        fwrite(&aux -> asistio, sizeof(int), 1, archivo);
        fwrite(&aux -> clave, sizeof(int), 1, archivo);
        fwrite(aux -> nombre, sizeof(char), 30, archivo);

        aux = aux -> sig;
    }

    fclose(archivo);
    printf("\nAsistencia guardada en 'asistencia.dat'.\n");
    printf("\n");
}

void Imprimir_lista(TAlumnos *cabecera)
{
    TAlumnos *aux = cabecera;
    int i = 1;

    printf("Lista de alumnos\n");
    while (aux != NULL)
    {
        if(aux -> asistio != 0 && aux -> asistio != 1)
        {
            printf("%d - Clave: %d, Nombre: %s, No se ha tomado asistencia\n", i, aux -> clave, aux -> nombre);
        }
        else
        {
            printf("%d - Clave: %d, Nombre: %s, Asistio: %s\n", i, aux -> clave, aux -> nombre, aux -> asistio ? "Si" : "No");
        }
        aux = aux->sig;
        i ++;
    }
    printf("\n");
}

void Modificar_alumno(TAlumnos *cabecera)
{
    Imprimir_lista(cabecera);

    int opcion;
    printf("Seleccione el numero del alumno a modificar: ");
    scanf("%d", &opcion);
    getchar();

    TAlumnos *aux = cabecera;
    int i = 1;
    while (aux != NULL && i < opcion)
    {
        aux = aux->sig;
        i++;
    }

    if (aux == NULL)
    {
        printf("Opcion invalida.\n");
        return;
    }

    printf("Ingrese la nueva clave: ");
    scanf("%d", &aux->clave);
    getchar();

    printf("Ingrese el nuevo nombre: ");
    fgets(aux -> nombre, sizeof(aux -> nombre), stdin);

    printf("Alumno modificado con exito.\n");
    printf("\n");
}

void Eliminar_alumno(TAlumnos **cabecera)
{
    Imprimir_lista(*cabecera);

    int opcion;
    printf("\nSeleccione el numero del alumno a eliminar: ");
    scanf("%d", &opcion);

    if (opcion <= 0)
    {
        printf("Indice invalido.\n");
        return;
    }

    TAlumnos *actual = *cabecera;
    TAlumnos *anterior = NULL;
    int i = 1;

    while (actual != NULL && i < opcion)
    {
        anterior = actual;
        actual = actual->sig;
        i ++;
    }

    if (actual == NULL)
    {
        printf("Indice fuera de rango.\n");
        return;
    }

    if (anterior == NULL)
    {
        *cabecera = actual -> sig;
    }
    else
    {
        anterior -> sig = actual -> sig;
    }

    printf("\nAlumno eliminado: Clave %d, Nombre %s\n", actual -> clave, actual -> nombre);
    free(actual);
    printf("\n");
}

void Eliminar_asistencia(TAlumnos **cabecera)
{
    TAlumnos *actual = *cabecera;
    TAlumnos *aux;

    while (actual != NULL)
    {
        aux = actual -> sig;
        printf("Eliminando alumno: Clave %d, Nombre %s\n", actual -> clave, actual -> nombre);
        free(actual);        
        actual = aux;        
    }

    *cabecera = NULL; 
    printf("Toda la lista de asistencia ha sido eliminada.\n");
    printf("\n");
}