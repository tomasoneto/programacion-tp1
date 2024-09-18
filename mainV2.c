#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> //Para usar toupper() y tolower()

//Definicion de estructuras ----------------------------------

typedef struct registro_telem
{
    unsigned short hc;
    unsigned char fc;
    unsigned char pas;
    unsigned char pad;
    unsigned char temp;

} registro_telem_t;

typedef struct nodo_telem
{
    registro_telem_t registro;
    struct nodo_telem *sig;

} nodo_telem_t;

typedef struct registro_pacientes
{
    unsigned int hc;
    char apellido[16];
    char nombres[32];

} registro_pacientes_t;

typedef struct nodo_pacientes
{
    registro_pacientes_t registro;
    struct nodo_pacientes *sig;

} nodo_pacientes_t;

int agregarTelemetria(nodo_telem_t **, registro_telem_t);
int agregarPaciente(nodo_pacientes_t **, registro_pacientes_t);

float tempDecode(char value)
{
    float temp = ((float)value + 250) / 10;

    return temp;
}

int leerArchivos(nodo_telem_t **telemetria, nodo_pacientes_t **pacientes)
{
    FILE *f;
    void *aux;
    unsigned int contTelemetria = 0;
    unsigned int contPacientes = 0;

    // Telemetría
    aux = malloc(sizeof(registro_telem_t));

    f = fopen("telemetria.bin", "rb");

    if (f == NULL)
    {
        printf("Error al abrir el archivo de telemetria\n");
        return -1;
    }

    while (fread(aux, sizeof(registro_telem_t), 1, f))
    {
        // Agregar el elemento
        // Se pasa un puntero a puntero, para inicializar la cola en caso de tener el valor inicial NULL
        // Se hace un cast para el valor leido
        agregarTelemetria(telemetria, *(registro_telem_t *)aux);
        contTelemetria++;
    }

    printf("Leidos %d registros (%ld bytes) de telemetria.bin\n", contTelemetria, contTelemetria * sizeof(registro_telem_t));
    //Cambie el segundo d a ld, por que el valor del argumento 3 es long unsigned int

    if (fclose(f))
    {
        printf("Error al cerrar el archivo de telemetria\n");
        return -1;
    }

    // Pacientes
    aux = malloc(sizeof(registro_pacientes_t));

    f = fopen("pacientes.bin", "rb");

    if (f == NULL)
    {
        printf("Error al abrir el archivo de pacientes\n");
        return -1;
    }

    while (fread(aux, sizeof(registro_pacientes_t), 1, f))
    {
        // Agregar el elemento
        // Se pasa un puntero a puntero, para inicializar la cola en caso de tener el valor inicial NULL
        // Se hace un cast para el valor leido
        agregarPaciente(pacientes, *(registro_pacientes_t *)aux);
        contPacientes++;
    }

    printf("Leidos %d registros (%ld bytes) de pacientes.bin\n", contPacientes, contPacientes * sizeof(registro_pacientes_t));
    //Cambie el segundo d a ld, por que el valor del argumento 3 es long unsigned int
    if (fclose(f))
    {
        printf("Error al cerrar el archivo de pacientes\n");
        return -1;
    }

    return 0;
}

int agregarTelemetria(nodo_telem_t **cola, registro_telem_t registro)
{
    // Asignar memoria para nuevo elemento
    nodo_telem_t *nuevo = malloc(sizeof(nodo_telem_t));

    // Verificar alocacion de memoria
    if (nuevo == NULL)
    {
        return -1;
    }

    // Asignar valores al nuevo elemento
    nuevo->registro = registro;
    nuevo->sig = NULL;

    // Si la cola esta vacia, apuntar al elemento
    if (*cola == NULL)
    {
        *cola = nuevo;

        return 0;
    }
    // De lo contrario buscar el ultimo elemento y anexar
    else
    {
        nodo_telem_t *cursor = *cola;

        while (cursor->sig != NULL)
        {

            cursor = cursor->sig;
        }

        // Agregar nuevo elemento al final
        cursor->sig = nuevo;
    }

    return 0;
}

int agregarPaciente(nodo_pacientes_t **cola, registro_pacientes_t registro)
{
    // Asignar memoria para nuevo elemento
    nodo_pacientes_t *nuevo = malloc(sizeof(nodo_pacientes_t));

    // Verificar alocacion de memoria
    if (nuevo == NULL)
    {
        return -1;
    }

    // Asignar valores al nuevo elemento
    nuevo->registro = registro;
    nuevo->sig = NULL;

    // Si la cola esta vacia, apuntar al elemento
    if (*cola == NULL)
    {
        *cola = nuevo;

        return 0;
    }
    // De lo contrario buscar el ultimo elemento y anexar
    else
    {
        nodo_pacientes_t *cursor = *cola;

        while (cursor->sig != NULL)
        {

            cursor = cursor->sig;
        }

        // Agregar nuevo elemento al final
        cursor->sig = nuevo;
    }

    return 0;
}

void freeTelemetria(nodo_telem_t *nodo)
{
    if (nodo->sig == NULL)
    {
        free(nodo);
    }
    else
    {
        freeTelemetria(nodo->sig);
        free(nodo);
    }
}

void freePacientes(nodo_pacientes_t *nodo)
{
    if (nodo->sig == NULL)
    {
        free(nodo);
    }
    else
    {
        freePacientes(nodo->sig);
        free(nodo);
    }
}

int menu()
{

    int seleccion;

    printf("Menu:\n");
    printf("1. Buscar un paciente por su apellido y mostrar su nombre, nro de HC y todos sus registros de datos vitales.\n");
    printf("2. Mostrar los valores promedio de todos los signos vitales (FC, PAS, PAD, Temp).\n");
    printf("3. Generar un archivo llamado reporte.txt que contenga los apellidos y nombres de los \
pacientes cuya temperatura difiera en un 5%% o más respecto de la temperatura promedio.\n");
    printf("0. Liberar memoria y salir.\n");

    scanf("%d", &seleccion);

    return seleccion;
}

int opc1(nodo_telem_t *telemetria, nodo_pacientes_t *pacientes)
{

    char apellido[16];
    int encontrado = 0;  // Variable para rastrear si se encontró el apellido

    while(!encontrado){
    printf("\nIngregar apellido: ");
    scanf("%s", apellido);

    // Convertir la primera letra a mayúscula y el resto a minúsculas
    apellido[0] = toupper(apellido[0]);  // Primera letra a mayúscula
    for (int i = 1; apellido[i]; i++) {
        apellido[i] = tolower(apellido[i]);  // Resto a minúsculas
    }

    nodo_pacientes_t *cursor = pacientes;

    while (cursor != NULL)
    {
        if (strcmp(apellido, cursor->registro.apellido) == 0)
        {
            encontrado = 1;  // Se encontró el apellido

            // Verificar que la conversion a 16 bit sea valida
            if (cursor->registro.hc >= 0xFFFF)
            {
                printf("El numero de historia clinica tiene mas de 16 bits\n");
                return -1;
            }

            nodo_telem_t *cursor2 = telemetria;
            unsigned short hc = cursor->registro.hc;

            int datosEncontrados = 0; //Variable para ver si hay datos de telemetria

            // Iterar sobre telemetria
            while (cursor2 != NULL)
            {
                if (cursor2->registro.hc == hc)
                {
                    if(datosEncontrados == 0){
                    // Imprimir titulos
                        printf("Paciente: %s, %s, historia: %d\n", cursor->registro.apellido, cursor->registro.nombres, cursor->registro.hc);
                        printf("FC\tPAS\tPAD\tTemp\n");
                    }

                    printf("%d\t%d\t%d\t%.2f\n\n", cursor2->registro.fc, cursor2->registro.pas,
                           cursor2->registro.pad, tempDecode(cursor2->registro.temp));
                    datosEncontrados = 1;  // Marcar que se encontraron registros
                }

                cursor2 = cursor2->sig;
            }

        }

        cursor = cursor->sig;
    }

        // Si no se encontró el apellido, mostrar advertencia
        if (!encontrado)
        {
            printf("El apellido ingresado no está en la base de datos. Intente de nuevo.\n");
        }
    }

    return 0;
}

int opc2(nodo_telem_t *telemetria)
{
    unsigned int cont = 0;
    float fc = 0, pas = 0, pad = 0, temp = 0;

    while (telemetria != NULL)
    {
        fc += (float) telemetria->registro.fc;
        pas += (float) telemetria->registro.pas;
        pad += (float) telemetria->registro.pad;
        temp += tempDecode(telemetria->registro.temp);
        cont++;

        telemetria = telemetria->sig;
    }

    if (!cont)
    {
        printf("No hay valores para promediar\n");
        return -1;
    }

    printf("Registros %d\n", cont);


    printf("\n");
    printf("Valores medios:\n");
    printf("FC\tPAS\tPAD\tTemp\n");
    printf("%.2f\t%.2f\t%.2f\t%.2f\n", fc / cont, pas / cont, pad / cont, temp / cont);
    printf("\n");

    return 0;
}

int opc3(nodo_telem_t *telemetria, nodo_pacientes_t *pacientes)
{

    unsigned int cont = 0, impresos = 0;
    float media = 0, umbral;
    int mensaje_mostrado = 0;
    nodo_telem_t *cursor = telemetria;
    FILE *f;

    f = fopen("reporte.txt", "wb");

    if (f == NULL)
    {
        printf("Error abriendo archivo para guardar.\n");
        return -1;
    }

    // Obtener temperatura media
    while (cursor != NULL)
    {
        media += tempDecode(cursor->registro.temp);
        cont++;
        cursor = cursor->sig;
    }
    media = media / cont;

    // Iterar sobre pacientes
    nodo_pacientes_t *paciente = pacientes;
    while (paciente != NULL)
    {
        cursor = telemetria;

        // Iterar sobre registros
        while (cursor != NULL)
        {
            // Saltear registros que no pertenecen al paciente
            if (cursor->registro.hc == paciente->registro.hc)
            {
                char aux[16 + 2 + 32 + 1];

                // Imprimir si el desvio es mayor al umbral
                if (abs(tempDecode(cursor->registro.temp) - media) / media >= 0.05)
                {
                    // Guardar en variable aux
                    sprintf(aux, "%s, %s\n", paciente->registro.apellido, paciente->registro.nombres);

                    // Guardar en archivo
                    if (fwrite(&aux, 1, strlen(aux), f) != strlen(aux))
                    {
                        printf("Error al escribir en el archivo\n");
                        return -1;
                    }

                    // Mostrar en pantalla si corresponde
                    if (impresos < 10)
                    {
                        printf("%s", aux);
                        impresos++;
                    }
                    // Mensaje para indicar que solo se muestran los primeros 10
                    if (impresos == 10 && !mensaje_mostrado)
                    {
                        printf("\nSe muestran solo los primeros 10 pacientes. Los datos completos han sido guardados en 'reporte.txt'.\n\n");
                        mensaje_mostrado = 1;
                    }

                    // Imprimir cada paciente como maximo una vez, pasar al siguiente
                    break;
                }
            }

            cursor = cursor->sig;
        }

        paciente = paciente->sig;
    }

    if (fclose(f))
    {
        printf("Error al cerrar el archivo registro.txt");
    }

    return 0;
}

//Main ----------------------------------

int main()
{
    // Iniciar colas en NULL
    nodo_telem_t *telemetria = NULL;
    nodo_pacientes_t *pacientes = NULL;

    leerArchivos(&telemetria, &pacientes);

    while (1)
    {
        char opcion = menu();

        switch (opcion)
        {
        case 1:
            opc1(telemetria, pacientes);
            break;

        case 2:
            opc2(telemetria);
            break;

        case 3:
            opc3(telemetria, pacientes);
            break;

        case 0:
            freeTelemetria(telemetria);
            freePacientes(pacientes);
            return 0;

        default:
            printf("Opcion no valida\n");
            break;
        }
    }
}