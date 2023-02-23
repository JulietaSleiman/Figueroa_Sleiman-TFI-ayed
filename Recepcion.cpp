//MODULO RECEPCION
/*Esta parte del proyecto esta dirigida al personal de atencion al publico, que atiende y registran los socios
del gimnasio, en una base de datos. Cada socios puede participar de 1 o mas actividades, (Zumba,
Spining, y pilate), cada actividad tiene asignado un entrenador por turno, dicho entrenador puede tener
mas de un horario disponible como asitambien puede brindar entrenamiento en distintas actividades.
Cada socio se identifica con un numero de socio y de igual forma cada entrenador se identifica con un
Legajo de Entrenador.
El sistema deberia contar con:
a) Registro de socio. Para cada Socio se debera registrar Nombre, Apellido DNI, Edad, peso,
Indicaciones mdicas (Donde es posible registrar si el socio esta restringido para alguna
actividad), Altura Peso, Direccion, Telefono, Fecha de ingreso.
b) Registro de actividad. Una vez registrado el socio, este podria inscribirse en distintas actividades
pudiendo elegir el horario y entrenador.
c) listado de participantes, de una actividad determinada, por horario y entrenador.
d) Listado de fecha de pago. La cual estar� relacionada con la fecha de ingreso.
Ademas se tiene la opcion de registrar por cada socio una rutina indicada por el entrenador en un texto
no mayor a 380 palabras, para esto cada operador debera identificarse en el sistema con un nombre de
usuario y contrasenia.

INTEGRANTES:
-Figueroa Cesar Bernabe - 57150.
-Sleiman Julieta - 56017.
*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
using namespace std;

struct Usuarios{
	char usuario[10];
	char contra[32];
	char ApeyNom[60];
	char tipo[14];
};

struct GymAct {
	char nombre[50];
	char horario[10];
	char entrenador[60];
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

bool valEnt(float x); 
bool valOpc(float x, int min, int may); 
bool Fecha(int x, int min, int max);
void IniciarSesion(Usuarios &reg1);
bool existe(char nombre[100], char apellido[100], RegRecep& socio2);
void fechaDePago(fecha fechaDeIngreso);
//Funciones
void RegistrodeSocio(RegRecep reg1,FILE *archMR);
void RegistroACT(RegRecep reg1,FILE *archMR);
void ListarSocios(RegRecep reg1,FILE *archMR);
// void ListarParti(RegRecep reg1,FILE *archMR);
void ListadoFP(RegRecep reg1,FILE *archMR);

int main(){
	RegRecep reg;
	int opc;
	Usuarios usuario;
	FILE *archMR; 
    bool band=true;
	do{
		system("cls");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t*      MODULO RECEPCION                                               *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 1. Iniciar Sesion                                            *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 2. Registrar Socios                                          *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 3. Registrar Actividades de Socios                           *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 4. Listado de Socios                                         *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 5. Listado de Fechas de Pago                                 *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 6. Cerrar la Aplicacion                                      *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\n\n\t\tIngrese una opcion: ");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				IniciarSesion(usuario);
				break;
			case 2:
				if(strcmp(usuario.tipo,"secretario")==0){
					RegistrodeSocio(reg,archMR);
				} else {
					printf("\n\t[Error] - Sesion invalida. El usuario que debe Iniciar Sesion tiene que ser un Secretario..\n\t");
					system("PAUSE");
				}
				break;
			case 3:
				if(strcmp(usuario.tipo,"secretario")==0){
					RegistroACT(reg,archMR);
				} else {
					printf("\n\t[Error] - Sesion invalida. El usuario que debe Iniciar Sesion tiene que ser un Secretario..\n\t");
					system("PAUSE");
				}
				break;
			case 4:
				if(strcmp(usuario.tipo,"secretario")==0){
					ListarSocios(reg,archMR);
				} else {
					printf("\n\t[Error] - Sesion invalida. El usuario que debe Iniciar Sesion tiene que ser un Secretario..\n\t");
					system("PAUSE");
				}
				break;
			case 5:
				if(strcmp(usuario.tipo,"secretario")==0){
					ListadoFP(reg,archMR);
				} else {
					printf("\n\t[Error] - Sesion invalida. El usuario que debe Iniciar Sesion tiene que ser un Secretario..\n\t");
					system("PAUSE");
				}
				break;
			case 6:	
				break;
			default:		
				system("cls");
				printf("\n\nOpcion no valida...");
				break;
		printf("\n\n");
		system("pause");		
		}
	}while(opc!=6);
	return 0;
}

void IniciarSesion(Usuarios &reg1){	
    char usuario[10];
    char contra[32];
 	FILE *archMA=fopen("Usuarios.dat", "rb");
	if(archMA!=NULL){
		printf("\tIngresar Nombre de Usuario: ");
		_flushall();
		cin.getline(usuario,10,'\n');
		printf("\tIngresar Contrasenia: ");
		_flushall();
		cin.getline(contra,32,'\n');
		fread(&reg1, sizeof(Usuarios), 1, archMA);
		while(!feof(archMA)){;
			if(strcmp(reg1.usuario, usuario)==0 && strcmp(reg1.contra, contra)==0){
				printf("\n\tSesion iniciada\n\t");
				break;
			} else {
				strcpy(reg1.tipo, "none");
			}
			fread(&reg1, sizeof(Usuarios), 1, archMA);
		}
	}
	fclose(archMA);
	system("PAUSE");
	system("CLS");
}

bool valEnt(float x)
{	
	int entero;
	float decimal;
	
	entero=x/1;
	decimal=x-entero;
		
	if(decimal!=0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
bool valOpc(float x, int min, int may)
{
	if(x<min || x>may)
	{			
		return 0;
	}
	else
	{
		return 1;
	}
}
bool Fecha(float x, int min, int max)
{
	bool vEnt,vOpc;
	
	vEnt=valEnt(x);
	vOpc=valOpc(x,min,max);
	
	if(vEnt==1 && vOpc==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//REGISTRAR SOCIOS
void RegistrodeSocio(RegRecep reg1,FILE *archMR)
{
	bool f,error;
	float aux;
	int continuar='N', c=0;
	FILE *fp;
	RegRecep Socio;
	archMR=fopen("Socios.dat","a+b");
	if(archMR != NULL){
		do
		{
		system("cls");
		printf("\n\t\tRegistro de Socio:");
		printf("\n\n\tIngrese el Nombre:  ");
		_flushall();
		cin.getline(reg1.Nombre, 100, '\n');
		printf("\n\tIngrese el Apellido:  ");
		_flushall();
		cin.getline(reg1.Apellido, 100, '\n');
		do{
		printf("\n\tIngrese el DNI (8 digitos): ");
		scanf("%d",&reg1.DNI);
		if(reg1.DNI>=10000000 && reg1.DNI<=99999999 )
				{
					error=0;
				}
				else
				{
					error=1;
					printf("\n\t[Error] - El numero ingresado no contiene 8 digitos..");
				}
			}while(error!=0);	
		printf("\n\tIngrese la EDAD: ");
		scanf("%d",&reg1.EDAD);
		printf("\n\tIngrese el Peso: ");
		scanf("%f",&reg1.Peso);
		_flushall();
		printf("\n\tIngrese la Altura: ");
		scanf("%f",&reg1.Altura);	
		_flushall();
		printf("\n\tIndique si el socio presenta alguna dificultad fisica: ");
		scanf("%s",&reg1.IndMed);
		_flushall();
		printf("\n\tIngrese la Direccion: ");
		_flushall();
		cin.getline(reg1.Direccion, 100, '\n');
		_flushall();
		printf("\n\tIngrese la Fecha de Ingreso");
			do
			{
				printf("\n\tDia : ");
				scanf("%f",&aux);
				f = Fecha(aux,1,30);
				if(f!=1)
				{
					error=1;
					printf("\n\t[Error] - El numero ingresado no se encuentra dentro de los 30 dias que puede tener un mes..");
				}
				else
				{
					error=0;
					reg1.FechaIngreso.dia=aux;
				}
			}while(error!=0);
				do
			{
				printf("\n\tMes : ");
				scanf("%f",&aux);
				f = Fecha(aux,1,12);
				if(f!=1)
				{
					error=1;
					printf("\n\t[Error] - El numero ingresado no se encuentra dentro de los 12 meses del a�o..");
				}
				else
				{
					error=0;
					reg1.FechaIngreso.mes=aux;
				}
			}while(error!=0);
			do
			{
				printf("\n\tAnio : ");
				scanf("%f",&aux);
				f = Fecha(aux,2000,3000);
				if(f!=1)
				{
					error=1;
					printf("\n\t[Error] - El numero ingresado no se encuentra entre el conjunto 2000-3000 posible de anio..");
				}
				else
				{
					error=0;
					reg1.FechaIngreso.anio=aux;
				}
				fp = fopen("Socios.dat", "rb");
				if(fp!=NULL){
					fread(&Socio, sizeof(RegRecep), 1, fp);
					while (!feof(fp)){
						c++;
						fread(&Socio, sizeof(RegRecep), 1, fp);
					}
					reg1.NroSocio=c;
				} else {
					reg1.NroSocio=0;
				}
				fclose(fp);
				printf("Numero de socio: %d", reg1.NroSocio);
			}while(error!=0);
		fwrite(&reg1, sizeof(RegRecep), 1, archMR); //Graba el registro l�gico.
		_flushall();
		printf("\n\tContinuar cargando Socios (S/N)");
		scanf("%c",&continuar);
		c=0;
		}while(continuar=='S'||continuar=='s');
	} else {
		system("CLS");
		printf("\nERROR al abrir el archivo..");
    }
    fclose(archMR);
}

//REGISTRAR ACTIVIDAD
void RegistroACT(RegRecep reg1,FILE *archMR){	
	archMR = fopen("Turnos.dat","a+b");
	GymAct actividad;
	GymAct actividades[30];
	FILE *fp=fopen("GymAct.dat", "rb");
	Turnos turno;
	RegRecep socio;
	int op,c,continuar;

   	if(archMR == NULL){
		system("CLS");
		printf("\nERROR al abrir el archivo..");
		exit(1);
    }

	do{
		c=0;
		system("CLS");
		do{
			printf("\n\tIngresar nombre del socio: ");
			_flushall();
			cin.getline(reg1.Nombre,100,'\n');
			printf("\n\tIngresar apellido del socio: ");
			_flushall();
			cin.getline(reg1.Apellido,100,'\n');
			if(!existe(reg1.Nombre,reg1.Apellido,socio)){
				printf("\n\t[Error] - El socio no esta registardo.\n");
			}
		} while (!existe(reg1.Nombre,reg1.Apellido, socio));
		printf("\n\t* * * * * * * * * * * * * * * * * * *\n\t*      ACTIVIDADES DISPONIBLES      *\n\t* * * * * * * * * * * * * * * * * * *\n");
		fread(&actividad, sizeof(GymAct), 1, fp);
		while(!feof(fp)){
			if(strcmp(socio.IndMed,actividad.nombre)!=0){
				actividades[c]=actividad;
				printf("\n\t%d) Nombre de la actividad: %s\n\tHorario: %s\n\tEntrenador: %s",c+1,actividad.nombre,actividad.horario,actividad.entrenador);
				c++;
			}
			fread(&actividad, sizeof(GymAct), 1, fp);
		}
		fclose(fp);
		do {
			printf("\n\n\tElija en que Actividad desea registrarse:  ");
			scanf("%d",&op);
			if(op>c || op<1){
				printf("\n\tLa actividad no esta disponible.\n");
			}
		} while(op>c || op<1);

		strcpy(turno.entrenador,actividades[op-1].entrenador);
		strcpy(turno.horario, actividades[op-1].horario);
		strcpy(turno.nombreActividad,actividades[op-1].nombre);
		turno.nroSocio=socio.NroSocio;

		printf("\n\n");
		_flushall();
		printf("\n\n\tIntroduzca '1' para continuar registrando y un numero distinto para finalizar la carga: ");
		scanf("%d", &continuar);
	}while(continuar==1);

	fwrite(&turno,sizeof(Turnos),1,archMR);
	fclose(archMR);
}

bool existe(char nombre[100], char apellido[100], RegRecep& socio2){
	RegRecep socio;
	FILE *fp=fopen("Socios.dat", "rb");
	fread(&socio, sizeof(RegRecep), 1, fp);
	while(!feof(fp)){
		if(strcmp(nombre, socio.Nombre)==0 && strcmp(apellido, socio.Apellido)==0){
			fclose(fp);
			socio2=socio;
			return true;
		}
		fread(&socio, sizeof(RegRecep), 1, fp);
	}
	fclose(fp);
	return false;
}

//LISTADO DE SOCIOS
void ListarSocios(RegRecep reg1,FILE *archMR)
{
	system("CLS");
	printf("\t*********************************************************\n");
	printf("\t** L I S T A D O  D E  S O C I O S **\n");
	printf("\t*********************************************************\n\n");

	archMR=fopen("Socios.dat", "rb");
	if (archMR!=NULL){
		fread(&reg1, sizeof(RegRecep), 1, archMR); 
		while(!feof(archMR)){ //Repite hasta el �ltimo registro.
			printf("\t\n Nombre y Apellido:  %s %s ", reg1.Nombre,reg1.Apellido);
			printf("\t\n DNI:  %d", reg1.DNI);
			printf("\t\n Edad:  %d", reg1.EDAD);
			printf("\t\nAltura: %.2f",reg1.Altura);
			printf("\t\n Peso:  %.2f", reg1.Peso);
			printf("\t\n Direccion:  %s", reg1.Direccion);
			printf("\t\n Fecha de Ingreso: %d/%d/%d ", reg1.FechaIngreso.dia, reg1.FechaIngreso.mes, reg1.FechaIngreso.anio);
			printf("\t\n Numero de Socio: %d",reg1.NroSocio);
			printf("\n");
			fread(&reg1, sizeof(RegRecep), 1, archMR);
		}
	} else {
		system("CLS");
		printf("\nEl Archivo esta vacio No se Registro Informacion.\n");
	}
	fclose(archMR);
	
	printf("F i n  d e l  L i s t a d o\n");
 	system("pause"); 
}

void ListadoFP(RegRecep reg1,FILE *archMR){
	int nroSocio;
	bool flag=false;
	system("CLS");
	printf("\t****************************************************\n");
	printf("\t** L I S T A D O  D E  F E C H A S  D E  P A G O  **\n");
	printf("\t****************************************************\n\n");

	archMR = fopen("Socios.dat","rb");
	if (archMR==NULL){
		system("CLS");
		printf("\nEl Archivo esta vacio No se Registro Informacion.");
	} else {
		printf("\t\n Numero de socio: ");
		scanf("%d", &nroSocio);

		fread(&reg1, sizeof(RegRecep), 1, archMR); 
		while(!feof(archMR)){ 
			if(nroSocio==reg1.NroSocio){
				printf("Proxima fecha de pago:");
				fechaDePago(reg1.FechaIngreso);
				printf("\n\n\t");
				flag=true;
				break;
			}
			fread(&reg1, sizeof(RegRecep), 1, archMR); 
		}
		if(!flag){
			printf("\n\tNo se encontro al socio.\n");
		}
	}
	system("PAUSE");
	fclose(archMR);
}

void fechaDePago(fecha fechaDeIngreso){
	int meses[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	fecha proxPago;
	if(fechaDeIngreso.mes==12){
		proxPago.dia=fechaDeIngreso.dia;
		proxPago.mes=1;
		proxPago.anio=fechaDeIngreso.anio+1;
	} else {
		if(fechaDeIngreso.dia>meses[fechaDeIngreso.mes]){
			proxPago.dia=meses[fechaDeIngreso.mes];
			proxPago.mes=fechaDeIngreso.mes+1;
			proxPago.anio=fechaDeIngreso.anio;
		} else {
			proxPago.dia=fechaDeIngreso.dia;
			proxPago.mes=fechaDeIngreso.mes+1;
			proxPago.anio=fechaDeIngreso.anio;
		}
	}
	printf("%d/%d/%d", proxPago.dia, proxPago.mes,proxPago.anio);
}












