//MODULO GYM
/*Este modulo esta dirigido a los entrenadores, los cuales mediante la identificacion con nombre de
usuario y contrasenia podrian acceder al sistema, donde tendrian las siguientes opciones
a) Inicio de sesion.
b) listado de Socios y actividad que desarrolla.
Registro de rutinas de gimnasia para un grupo en particular con un texto de no m�s de 380 palabras
1.- Iniciar Sesion.
2.- Visualizar listado de Socios y actividad que desarrolla.
3.- Registrar rutinas de gimnasia.
4.- Cerrar la aplicacion.

INTEGRANTES:
-Figueroa Cesar Bernabe - 57150.
-Sleiman Julieta - 56017.
*/

#include <iostream>
#include <stdlib.h> 
#include <conio.h>
#include <string.h>
#include <cstdio>
using namespace std;

typedef char Dia[10];

struct GymAct {
	char nombre[50];
	char horario[10];
	char entrenador[60];
};

struct Entrenadores{
	
	char ApellidoyNombre[60];
	Dia Dias[6];
	int legajo;
	char contrasenia[10];

};

struct fecha
{
	int dia;
	int mes;
	int anio;	
};

struct RegRecep 
{
	char Nombre[100];
	char Apellido[100];
	int DNI;
	int EDAD;
	float Peso;
	char IndMed[200];
	float Altura;
	char Direccion[100];
	fecha FechaIngreso;
	int NroSocio;
};

struct Turnos {
	char entrenador[60];
	char horario[10];
	int nroSocio;
	char nombreActividad[50];
};

struct registroRutina{
    char rutina[500];
    char grupo[100];
    char horario[50];
    char Entrenador[100];
 };

void RutinasGimnasia(Entrenadores entrenador,FILE *fp);
void IniciarSesion(Entrenadores &entrenador, bool &sesion);
void visualizarSocyAct(Entrenadores entrenador);
void encontrarSocio(int nroSocio);

main(){
	registroRutina reg;
	FILE *archMG;
	archMG=fopen("Rutinas.dat","w+b");
	Entrenadores entrenador;
	bool sesion=false;
	int opcion;
	do
	{
		system("CLS");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t*      MODULO GYM                                                     *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 1. Iniciar Sesion                                            *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 2. Visualizar listado de socios y actividad que desarrolla   *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 3. Registrar Rutinas de Gimnasia                             *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 4. Cerrar Aplicacion                                         *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("\n\tIngrese una opcion: ");
        scanf("%d",&opcion);
        switch(opcion){
        	case 1:
        		IniciarSesion(entrenador, sesion);
			    break; 
        	case 2:
				if(sesion){
        			visualizarSocyAct(entrenador);
				} else {
					printf("\tSe requiere iniciar sesion.\n");
				}
				printf("\n\t");
				system("PAUSE");
				system("CLS");
        		break;
        	case 3:
				if(sesion){
        			RutinasGimnasia(entrenador,archMG);
				} else {
					printf("\tSe requiere iniciar sesion.\n");
				}
				printf("\n\t");
				system("PAUSE");
				system("CLS");
			    break;
			case 4:
				system("cls");
				printf("\nCierre de Aplicacion...");
				break;
			default:
				system("cls");
				printf("\n\nOpcion no valida...");
				break;
		printf("\n\n");
		system("pause");
        }
	}while(opcion!=4);
	fclose(archMG);
}

void IniciarSesion(Entrenadores &entrenador, bool &sesion)
{	
	int legajo;
	char contrasenia[10];
 	FILE *fp=fopen("Entrenadores.dat", "rb");
	if(fp!=NULL){
		printf("\tIngresar legajo: ");
		scanf("%d", &legajo);
		printf("\tIngresar contrasenia: ");
		_flushall();
		cin.getline(contrasenia,10,'\n');

		fread(&entrenador, sizeof(Entrenadores), 1, fp);
		while(!feof(fp)){
			if(entrenador.legajo==legajo && strcmp(entrenador.contrasenia, contrasenia)==0){
				sesion=true;
				break;
			} else {
				sesion=false;
			}
			fread(&entrenador, sizeof(Entrenadores), 1, fp);
		}
		if(sesion){
			printf("\n\tSesion iniciada\n\n\t");
		} else {
			printf("\tError al iniciar sesion.\n\n\t");
		}
	} else {
		printf("\tHubo un error al abrir el archivo...\n\n\t");
	}
	fclose(fp);
	system("\n\tPAUSE");
	system("CLS");
}

void visualizarSocyAct(Entrenadores entrenador){
    FILE *fp=fopen("Turnos.dat", "rb");
	Turnos turno;

	fread(&turno, sizeof(Turnos), 1, fp);
	while(!feof(fp)){
		if(strcmp(strlwr(turno.entrenador),strlwr(entrenador.ApellidoyNombre))==0){
			printf("\n\tActividad: %s\n\tHorario: %s\n\tSocio: ", turno.nombreActividad, turno.horario);
			encontrarSocio(turno.nroSocio);
		}
		fread(&turno, sizeof(Turnos), 1, fp);
	}
	fclose(fp);
}

void encontrarSocio(int nroSocio){
	FILE *fp=fopen("Socios.dat", "rb");
	RegRecep socio;
	if(fp!=NULL){
		fread(&socio, sizeof(RegRecep), 1, fp);
		while(!feof(fp)){
			if(nroSocio==socio.NroSocio){
				printf("%s %s\n", socio.Nombre, socio.Apellido);
				break;
			}
			fread(&socio, sizeof(RegRecep), 1, fp);
		}
	} 
	fclose(fp);
}


void RutinasGimnasia(Entrenadores entrenador,FILE *fp){
    fp=fopen("GymAct.dat", "rb");
    FILE *rutina1=fopen("Rutinas.dat", "ab");
    GymAct actividad;
    registroRutina rutina;
    bool flag=false;
    if(fp!=NULL){   
        do{
            rewind(fp);
            printf("\n\tNombre del grupo: ");
			_flushall();
			cin.getline(rutina.grupo, 100, '\n');
            fread(&actividad, sizeof(GymAct), 1, fp);
            while(!feof(fp)){
                if((strcmp(rutina.grupo,actividad.nombre)==0)&&(strcmp(actividad.entrenador,entrenador.ApellidoyNombre)==0)){
                    strcpy(rutina.horario, actividad.horario);
                    strcpy(rutina.Entrenador, actividad.entrenador);
                    printf("\n\tRutina(max. 380 caracteres): ");
					_flushall();
					cin.getline(rutina.rutina,500, '\n');
                    if(strlen(rutina.rutina)>380){
                        flag=false;
                    } else {
                        flag=true;
                    }
                    break;
                }
                fread(&actividad, sizeof(GymAct), 1, fp);
            }
            
            if(!flag){
                printf("\n\tEl nombre del grupo es incorrecto.\n");
            }   
        } while (!flag);
        fwrite(&rutina, sizeof(registroRutina), 1, rutina1);
    } else {
        printf("\n\tNo hay turnos registrados.\t");
    }
    fclose(fp);
    fclose(rutina1);
}
