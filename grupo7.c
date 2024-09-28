#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *t,*p;

/**
 * Analisis:
 * La funcion main ejecuta todo el programa.
 * 
 * Correcciones:
 * - Seria conveniente dividir el programa en funciones mas pequeñas, para facilitar la lectura y el mantenimiento del codigo.
 * - Seria conveniente agregar comentarios que expliquen que hace cada parte del codigo.
 * - Seria conveniente mantener la indentacion del codigo.
 * 
 */

int main()
{

	/**
	 * Analisis:
	 * Define las estructuras de pacientes y telemetrias.
	 * 
	 * Correcciones:
	 * - Seria conveniente mover las definiciones fuera de la funcion main, para que puedan ser utilizadas en otras funciones.
	 * 
	 */
//definiciones
typedef struct pacientes
	{
	unsigned int HC;
	char apellido[16];
	char nombres[32];
	}paci;
typedef struct telemetrias
	{
	unsigned short HC;
	unsigned char FC;
	unsigned char PAS;
	unsigned char PAD;
	unsigned char C;
	}tele;

	/**
	 * Analisis:
	 * Define las variables necesarias para el programa.
	 * 
	 * Las variables son:
	 * - r: Variable para almacenar el resultado de la lectura de los datos de telemetria.
	 * - i: Variable para iterar sobre los datos de telemetria.
	 * - l: Variable para almacenar el tamaño del archivo de telemetria.
	 * - la: Variable para almacenar la cantidad de registros de pacientes.
	 * - re: Variable para almacenar el resultado de la lectura de los datos de pacientes.
	 * - pax: Variable para almacenar la cantidad de registros de pacientes.
	 * - tel: Variable para almacenar la cantidad de registros de telemetria.
	 * - b: Variable para iterar sobre los registros de pacientes.
	 * - c: Variable para almacenar el resultado de la comparacion de cadenas.
	 * - con: Variable para contar la cantidad de coincidencias de apellido.
	 * - coi: Variable para contar la cantidad de coincidencias de nombre.
	 * - aux: Variable auxiliar.
	 * - ce: Variable para almacenar el resultado de cerrar el archivo.
	 * - x: Variable para iterar sobre los registros de telemetria.
	 * - promFC: Variable para almacenar el promedio de la frecuencia cardiaca.
	 * - promPAS: Variable para almacenar el promedio de la presion arterial sistolica.
	 * - promPAD: Variable para almacenar el promedio de la presion arterial diastolica.
	 * - promC: Variable para almacenar el promedio de la temperatura corporal.
	 * - ca: Variable para almacenar la cantidad de registros de telemetria.
	 * - z: Variable para almacenar la opcion elegida por el usuario.
	 * 
	 * 
	 * Correcciones:
	 * - Seria conveniente utilizar nombres mas descriptivos para las variables.
	 * - Los promedios podrian ser float, para tener mayor precision.
	 * - Las variables de iteracion se pueden declarar en el lugar de cada bucle para mayor claridad.
	 * 
	 */

int r,i,l,la,re, pax, tel,b,c,con,coi,aux,ce,x, promFC, promPAS, promPAD,promC,ca,z=1; //SE INICIALIZó Z
char ap[16], np[32];
unsigned int nhp;
long sum;
paci *pac;

//iniciar programa

/**
 * Analisis:
 * Abre los archivos pacientes.bin y telemetria.bin y carga los datos en las estructuras. Se utilizan las funciones fseek y ftell
 * para obtener el tamaño del archivo y la cantidad de registros.
 * Se definen los vectores a y nom para almacenar los indices de los pacientes que coinciden con el apellido y nombre ingresados.
 * 
 * Correcciones:
 * - Para volver al principio del archivo, se puede utilizar la funcion fseek con SEEK_SET.
 * - Seria conveniente definir las variables en la parte superior del programa o medida que se utilizan para mantener consistencia.
 * - Seria conveniente validar el resultado de malloc
 * - Seria conveniente explicar la function de los vectores a y nom. Mas adelante se utilizan para almacenar
 * los indices de los pacientes que coinciden con el apellido y nombre ingresados. Sin embargo se declarar del tamaño de pax,
 * que es la cantidad de registros de pacientes y eso incumple la consigna de utilizar la memoria necesaria.
 * 
 */

//abrir archivo pacientes

printf ("abriendo archivo pacientes.bin\n");
p = fopen ("pacientes.bin", "r");

	if (p==NULL)
		{
		perror("error al abrir archivo");
		exit(1);
		}

fseek (p, 0,SEEK_END);

la = ftell (p);

fseek (p, -la , SEEK_END);

pax = (la/(sizeof (paci) ));

int a[pax], nom[pax]; 		//defino vectores con lugar para todos los pacientes

printf ("El archivo pacientes.bin contiene %d bytes de datos, %d registros\n",la, pax);


pac = malloc (la);		//asigno memoria dinamica para struct de descarga de datos

re = fread (pac, sizeof (paci), pax , p);

	if (re != pax)
		{
		printf("Error al cargar datos\n");
		exit (1);
		}

struct telemetrias *telem;

//abrir archivo telemetria

printf ("abriendo archivo telemetria.bin\n");
t = fopen ("telemetria.bin", "r");

	if (t==NULL)
		{
		perror("error al abrir archivo");
		exit(1);
		}

fseek (t, 0,SEEK_END);

l = ftell (t);

fseek (t, -l , SEEK_END); 

tel = (l/(sizeof (tele)));
printf ("El archivo telemetria.bin contiene %d bytes de datos, %d registros\n",l,tel );

telem = malloc (l);		//asigno memoria dinamica para struct de descarga de datos

r = fread (telem, sizeof (tele), tel, t);
	if (r!= tel)
		{
		printf("Error al cargar datos\n");
		exit (1);
		}
		
//cerrar archivos

/**
 * Analisis:
 * Cierra los archivos pacientes.bin y telemetria.bin.
 * 
 * Correcciones:
 * - No es necesario asignar el resultado de fclose a una variable.
 * - Se puede utilizar if else para mayor claridad.
 */

ce = fclose (t);
if (ce!=0) {printf("Error al cerrar archivo telemetria.bin\n");}
ce = fclose (p);
if (ce!=0) {printf ("Error al cerrar archivo pacientes.bin\n");}
if (ce == 0) {printf ("Archivos cerrados con exito\n");}

/**
 * Analisis:
 * Calcula los valores promedio de los signos vitales.
 * 
 * Correcciones:
 * - No contempla el caso en que no haya registros de telemetria y se divida por 0.
 */

//calculo valores promedio
sum=0;
for (x=0;x<tel;x++)
	{
	sum= sum+telem[x].FC;
	}
promFC=sum/tel;


sum=0;
for (x=0;x<tel;x++)
	{
	sum= sum+telem[x].PAS;
	}
promPAS=sum/tel;


sum=0;
for (x=0;x<tel;x++)
	{
	sum= sum+telem[x].PAD;
	}
promPAD=sum/tel;


sum=0;
for (x=0;x<tel;x++)
	{
	sum= sum+((telem[x].C)+250)/10;
	}
promC=sum/tel;




//elijo que quiero hacer

/**
 * Analisis:
 * Muestra un menu con las opciones disponibles y solicita al usuario que elija una opcion.
 * 
 * Correcciones:
 * - Se podria utilizar un switch para mayor claridad.
 */

while (z!=0) 
	{
	printf("Elija una de las siguientes opciones:\n\n1.Buscar un paciente y mostrar su informacion\n2.Mostrar valor promedio de todos los signos vitales\n3.Mostrar que pacientes se encuentran excedidos de temperatura\n0.Cerrar el programa\n");
	scanf("%d", &z);
	if (z==1)
		{
		//buscar por apellido


		/**
		 * Analisis:
		 * Solicita al usuario que ingrese apellido, nombre e historia clinina y busca los pacientes
		 * que coinciden con el apellido ingresado.
		 * 
		 * Correcciones:
		 * - Lo solicitado en la consiga es utilizar solo el apellido como criterio de busqueda
		 * - Al ramificar el programa para coi = 1 y coi > 1 se repite el codigo, se podria simplificar.
		 * 
		 */

		con=0;
		printf ("introduzca el apellido que desea buscar:\n");
		scanf ("%s", ap);
		printf ("El apellido ingresado es:%s\n\n",ap);
			for (b=0;b<pax;b++)
				{
				c = strcmp (pac[b].apellido, ap);
				if (c==0)
					{
					a[con] = b;
					con++;
					}
				}
		printf ("se encontraron %d coincidencias\n", con);


		if (con>1)
			{
			printf("introduzca el nombre/s del paciente:\n");
			scanf("%s", np);
			printf ("El nombre/s ingresado es: %s\n\n",np);
			coi=0;
			for (b=0;b<con;b++)
				{
				c = strcmp (pac[a[b]].nombres, np);
				if (c==0)
					{
					nom[coi] = a[b];
					coi++;
					}
				}		
			printf("El numero de coincidencias fue: %d\n",coi);
			if (coi>1)
				{
				aux=0;
				printf("introduzca el numero de historia clinica:\n");
				scanf("%u", &nhp);
				printf("El numero de historia clinica ingresado es:%u\n\n", nhp);
				for(b=0;b<coi;b++)
					{
					if (pac[nom[b]].HC==nhp)
						{
						printf("Numero de historia clinica:%u\nApellido:%s\nNombre:%s\n",pac[nom[b]].HC,pac[nom[b]].apellido,pac[nom[b]].nombres);  //Resultado positivo
						for (x=0;x<tel;x++)
							{
							if (pac[nom[b]].HC == telem[x].HC)
								{
								printf("FC:%hu\nPAS:%hu\nPAD:%hu\nTemperatura:%hu\n",telem[x].FC,telem[x].PAS,telem[x].PAD,(telem[x].C+250)/10);
								x=tel;
								aux=1;
								}
							}
						if (aux!=1)
							{
							printf("No hay datos de telemetria\n");
							}
						aux=1;
						}
					}
				if (aux!=1)
					{
					printf("No hubo coincidencias\n");   // Resultado negativo
					}
				}
			if (coi==0)
				{
				printf("No hubo coincidencias\n");   // Resultado negativo
				}
			if (coi==1)
				{
				aux=0;
				printf("Numero de historia clinica:%u\nApellido:%s\nNombre:%s\n",pac[nom[0]].HC,pac[nom[0]].apellido,pac[nom[0]].nombres);  //Resultado positivo
				for (x=0;x<tel;x++)
					{
					if (pac[nom[0]].HC == telem[x].HC)
						{
						printf("FC:%hu\nPAS:%hu\nPAD:%hu\nTemperatura:%hu\n",telem[x].FC,telem[x].PAS,telem[x].PAD,(telem[x].C+250)/10);
						x=tel;
						aux=1;
						}
					}
				if (aux!=1)
				{
				printf("No hay datos de telemetria\n");
				}
				}
			}
		if (con==0)
			{
			printf("No hubo coincidencias\n");   // Resultado negativo
			}
		if (con==1)
			{
			aux=0;
			printf("Numero de historia clinica:%u\nApellido:%s\nNombre:%s\n",pac[a[0]].HC,pac[a[0]].apellido,pac[a[0]].nombres);  //Resultado positivo
			for (x=0;x<tel;x++)
				{
				if (pac[a[0]].HC == telem[x].HC)
					{
					printf("FC:%hu\nPAS:%hu\nPAD:%hu\nTemperatura:%hu\n",telem[x].FC,telem[x].PAS,telem[x].PAD,(telem[x].C+250)/10);
					x=tel;
					aux=1;
					}
				}
			if (aux!=1)
				{
				printf("No hay datos de telemetria\n");
				}
			}	
		}
		
	else if (z==2)
		{
		//Muestro valores promedio
		printf("El valor promedio para la FC es:%d\n",promFC);
		printf("El valor promedio para la PAS es:%d\n",promPAS);
		printf("El valor promedio para la PAD es:%d\n",promPAD);
		printf("El valor promedio para la temperatura es:%d\n",promC);
		}
	
	else if (z==3)
		{
		//reporte

		/**
		 * Analisis:
		 * Muestra los pacientes cuya temperatura difiere en un 5% o mas respecto de la temperatura promedio.
		 * 
		 * Correcciones:
		 * - Falta generar el archivo
		 * - Falta limitar la impresion a 10 resultados
		 * - El calculo del umbral se puede realizar una sola vez antes del bucle.
		 * - Se contempla unicamente el caso en que la temperatura este por encima del promedio + 5% y no el caso inferior.
		 * 
		 */

	for (x=0;x<tel;x++)
		{
		if (((telem[x].C+250)/10)>=promC*1.05)
			{
			for (b=0;b<pax;b++)
				{
				if (pac[b].HC == telem[x].HC)
					{
					printf("Apellido:%s                  Nombre:%s\n",pac[b].apellido,pac[b].nombres);
					}
				}
			}
		}
		}
	else if (z == 0) {
        printf("Cerrando el programa...\n");
	}	
	else
		printf("opcion invalida");
	}

	

//Terminar programa
	
free (telem); 
free (pac); //CAMBIO free(telem), (pac); POR: free(telam); free(pac);

printf("Programa terminado\n");

return 0;
}
