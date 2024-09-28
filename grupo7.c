#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *t,*p;


int main()
{
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

int r,i,l,la,re, pax, tel,b,c,con,coi,aux,ce,x, promFC, promPAS, promPAD,promC,ca,z=1; //SE INICIALIZó Z
char ap[16], np[32];
unsigned int nhp;
long sum;
paci *pac;

//iniciar programa


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

ce = fclose (t);
if (ce!=0) {printf("Error al cerrar archivo telemetria.bin\n");}
ce = fclose (p);
if (ce!=0) {printf ("Error al cerrar archivo pacientes.bin\n");}
if (ce == 0) {printf ("Archivos cerrados con exito\n");}

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

while (z!=0) 
	{
	printf("Elija una de las siguientes opciones:\n\n1.Buscar un paciente y mostrar su informacion\n2.Mostrar valor promedio de todos los signos vitales\n3.Mostrar que pacientes se encuentran excedidos de temperatura\n0.Cerrar el programa\n");
	scanf("%d", &z);
	if (z==1)
		{
		//buscar por apellido


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
