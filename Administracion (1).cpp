/*MODULO ADMINISTRACION
a) Registrar Usuarios:
Registra los usuarios del sistema este puede ser Administrador o Secretario/a (Personal de
atencionn al publico).
b) Registrar Actividad:
Registra las actividades del gimnasio, los horarios de cada una de ellas y el entrenador
responsable. Tener en cuenta que un mismo entrenador no puede estar en 2 acuidades en el
mismo horario. Si es posible la existencia de mas de una actividad en el mismo horario.
c) Calcular pago al entrenador:
El pago se realiza teniendo en cuenta la cantidad de, personas a su cargo por cada actividad
d) Entrenador con mayor carga horaria:

INTEGRANTES:
-Figueroa Cesar Bernabe - 57150.
-Sleiman Julieta - 56017.	
*/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

using namespace std;
typedef char Dia[10];

struct GymAct {
	char nombre[50];
	char horario[10];
	char entrenador[60];
};

struct Usuarios{
	char usuario[10];
	char contra[32];
	char ApeyNom[60];
	char tipo[14];
};

struct Entrenadores{
	
	char ApellidoyNombre[60];
	Dia Dias[6];
	int legajo;
	char contrasenia[10];
	
};

void IniciarSesion(Usuarios &reg1,FILE *archMA);
void RegUsuarios(Usuarios reg1,FILE *archMA, bool &registrar, int tipo);
void RegEntrenador(Entrenadores regg1, FILE *archMA);
bool listaDias(char dia[10]);
void regAct(FILE *fp, GymAct act);
bool existe(char entrenador[60]);
void calcularPago(FILE *fp, GymAct act);
void calcularCarga(FILE *fp, GymAct act);
int HorasTotales(char nombre[60]);
int cantDias(Dia cantDias[6]);
bool seRepite(char user[100]);

int main()
{
Usuarios reg;
Entrenadores regg;
GymAct act;
FILE *archMA;
FILE *fp;
int opcion,longitud,respuesta;
bool error;
bool registrar;	
char usuario[10];


	do{
		fp=fopen("NewProgram.dat", "rb");
		if(fp!=NULL){
			fread(&registrar, sizeof(bool), 1, fp);
		} else {
			registrar=false;
		}
		system("CLS");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t\t\t*      MODULO ADMINISTRACION                                          *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 1. Iniciar Sesion                                            *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 2. Registrar usuario de Recepcion                            *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 3. Registrar Actividades del Gym                             *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 4. Calcular Pago al entrenador                               *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 5. Entrenador con mayor carga horaria                        *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t*\t 6. Volver al menu principal                                  *\n");
		printf("\t\t\t*                                                                     *\n");
		printf("\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\n\tIngrese la opcion: ");
		scanf("%d",&opcion);
	    system("cls");
		switch(opcion){
			case 1:
				if(registrar){
					IniciarSesion(reg, archMA);
				} else {
					printf("\n\t[Error] - Se requiere Registrar Usuario antes..");
					system("PAUSE");
				}
				break;
			case 2:
				if (!registrar || strcmp(reg.tipo, "administrador")==0){
					do{
						printf("\n\tQue Usuario desea registrarse? \n\t1. USUARIO\n\t2. ENTRENADOR\n\tRespuesta: " );
						scanf("%d", &respuesta);
						switch(respuesta){
							case 1:
								printf("\n\t. ADMINISTRADOR.\n\t. SECRETARIO.\n\tIntroduzca otro numero para cancelar.\n\tRESPUESTA: ");
								scanf("%d", &respuesta);
								if(respuesta!=1 && respuesta!=2){
									break;
								} else {
									if(respuesta==2 && !registrar){
										printf("\n\tLa primera cuenta debe ser de administrador.\n");
									} else {
										RegUsuarios(reg,archMA,registrar, respuesta);
									}
								}
								break;
							case 2:
								if(!registrar){
									printf("\n\tLa primera cuenta debe ser de administracion.\n");
									respuesta=3;
									system("\nPAUSE");
								} else {
									printf("\n\t\tENTRENADOR: ");
									RegEntrenador(regg,archMA);
								}
								break;
							default:
								printf("\n\t[Error] - Debe registrarse como Administrador o Secretario..");
								break;
						}

					}while(respuesta!=1 && respuesta!=2);
				} else {
					printf("\n\tNo se inicio sesion\n");
					system("PAUSE");
				}
				break;
			case 3:
				if(registrar && strcmp(reg.tipo, "administrador")==0){
					regAct(archMA,act);
				} else {
					printf("\n\tNo se inicio sesion\n");
				}
				system("\tPAUSE");
				break;
			case 4:
			 	if(registrar && strcmp(reg.tipo, "administrador")==0){
					calcularPago(archMA,act);
				} else {
					printf("\n\tNo se inicio sesion\n");
				}
				system("\tPAUSE");
				break;
			case 5:
				if(registrar && strcmp(reg.tipo, "administrador")==0){
					calcularCarga(archMA,act);
				} else {
					printf("\n\tNo se inicio sesion\n");
				}
				system("\tPAUSE");
				break;
			case 6:
				break;
			default:
				printf("\tLa opcion no esta disponible.\n\n");
				break;
		}
		fclose(fp);
	}while(opcion!=6);

	
	return 0;
}

void calcularCarga(FILE *sp, GymAct act){
    GymAct actividad;
	int mayor;
	Entrenadores entrenador;
    Entrenadores entrenador2;
    int horasActividades=0;
    int diasEntrenadores=0;
    int horasTotales=0;

    sp=fopen("Entrenadores.dat", "rb");
    if(sp!=NULL){
        fread(&entrenador2, sizeof(Entrenadores), 1, sp);
		mayor=HorasTotales(entrenador2.ApellidoyNombre)*cantDias(entrenador2.Dias);
		entrenador=entrenador2;
        while(!feof(sp)){
            horasTotales=HorasTotales(entrenador2.ApellidoyNombre)*cantDias(entrenador2.Dias);
            if(horasTotales>=mayor){
                mayor=horasTotales;
                entrenador=entrenador2;
            }
            fread(&entrenador2, sizeof(Entrenadores), 1, sp);
        }
		printf("\n\t\tEl entrenador con mayor carga horaria es: %s(%d horas)\n", entrenador.ApellidoyNombre, mayor);
    } else {
        printf("\n\t\tNo hay entrenadores registrados.\n");
    }
    fclose(sp);
}

int HorasTotales(char nombre[60]){
    FILE *fp;
    GymAct actividad;
    int c=0;
    
    fp=fopen("GymAct.dat", "rb");
    if(fp!=NULL){
        fread(&actividad, sizeof(GymAct), 1, fp);
        while(!feof(fp)){
            if(strcmp(nombre, actividad.entrenador)==0){
                c++;
            }
            fread(&actividad, sizeof(GymAct), 1, fp);
        }
    } else {
		fclose(fp);
        return 0;
    }
	fclose(fp);
    return c;
}

int cantDias(Dia cantDias[6]){
    int c=0;
    for(int i=0; i<6; i++){
        if(strcmp(cantDias[i], "-")!=0){
            c++;
        }
    }
    return c;
}

void calcularPago(FILE *fp, GymAct act){
	fp=fopen("GymAct.dat", "rb");
	int c=0, monto;
	char nombre[60];
	printf("\n\t\tIngresar nombre del entrenador: ");
	_flushall();
	cin.getline(nombre, 60, '\n');
	printf("\n\t\tMonto por actividad: ");
	scanf("%d", &monto);

	fread(&act, sizeof(GymAct), 1, fp);
	while(!feof(fp)){
		if(strcmp(strlwr(act.entrenador), strlwr(nombre))==0){
			c++;
		}
		fread(&act, sizeof(GymAct), 1, fp);
	}
	if(c==0){
		printf("\n\t\tNo hay ninguna actividad asignada para este entrenador.\n");
	} else {
		printf("\n\t\tEl pago correspondiente a %s es: %d\n", nombre, c*monto);
	}
	fclose(fp);
}

void regAct(FILE *fp, GymAct act){
	fp=fopen("GymAct.dat", "ab");
	if(fp!=NULL){
		printf("\n\t\t* * * * * * * * * * * * * * * * * * * * * *\n\t\t*             NUEVA  ACTIVIDAD            *\n\t\t* * * * * * * * * * * * * * * * * * * * * *");
		printf("\n\t\tNombre de la actividad: ");
		_flushall();
		cin.getline(act.nombre,50,'\n');
		printf("\n\t\tHorario: ");
		_flushall();
		cin.getline(act.horario,10,'\n');
		do{
			printf("\n\t\tEntrenador encargado: ");
			_flushall();
			cin.getline(act.entrenador,60,'\n');
			if(!existe(act.entrenador)){
				printf("\n\t\t[Error] - El entrenador no existe.");
			}
		}while(!existe(act.entrenador));
	} else {
		printf("\n\t[Error] - Error al abrir el archivo.\n");
	}
	fwrite(&act, sizeof(GymAct), 1, fp);
	fclose(fp);
}

bool existe(char entrenador[60]){
	FILE *fp=fopen("Entrenadores.dat", "rb");
	Entrenadores entrenador2;
	if(fp!=NULL){
		fread(&entrenador2, sizeof(Entrenadores), 1, fp);
		while(!feof(fp)){
			if(strcmp(entrenador, entrenador2.ApellidoyNombre)==0){
				fclose(fp);
				return true;
			}
			fread(&entrenador2, sizeof(Entrenadores), 1, fp);
		}
	}
	fclose(fp);
	return false;
}

void IniciarSesion(Usuarios &reg1,FILE *archMA)
{	
    char usuario[10];
    char contra[32];
 	archMA=fopen("Usuarios.dat", "rb");
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
				printf("\n\tInicio de Sesion realizada..\n\t");
				break;
			} else {
				strcpy(reg1.tipo, "none");
			}
			fread(&reg1, sizeof(Usuarios), 1, archMA);
		}
	}
	system("PAUSE");
	system("CLS");
	fclose(archMA);
}

void RegUsuarios(Usuarios reg1,FILE *archMA, bool &registrar, int tipo){
	system("cls");
	archMA=fopen("Usuarios.dat","a+b");
	int longitud,longit,digit=0,aux,compar,caractalfaconsc=0,caractnumconsec=0;
	bool May=false;
	bool Min=false;
	bool Num=false;
	bool sp=true;
	bool esp=true;
	int mayus=0;
	bool error;

	(tipo==1)
		?strcpy(reg1.tipo, "administrador")
		:strcpy(reg1.tipo, "secretario");
	
	
	do{
		printf("\n\n\tNOMBRE DE USUARIO");
		printf("\n\n\tACLARACION:Debera estar definido por una cantidad minima de 6 caracteres y maxima de 10 caracteres ");
		printf("\n\tlos cuales podran ser letras, numeros y/o simbolos del conjunto (+, -, /,*,?,�,!,i).");
		printf("\n\tTambien debera cumplir con los siguientes requisitos:");
		printf("\n\t1)Ser unico para cada usuario registrado.");
		printf("\n\t2)Comenzar con una letra minuscula.");
		printf("\n\t3)Tener al menos 2 letras mayusculas.");
		printf("\n\t4)Tener como maximo 3 d�gitos.");	
		
		do{
			printf("\n\n\tIngrese el nombre de usuario: ");
			_flushall();
			cin.getline(reg1.usuario,10,'\n');
			if(!seRepite(reg1.usuario)){
				printf("\n\tEl usuario ya se encuentra registrado.");
			}
		} while (!seRepite(reg1.usuario));
		
		longitud=strlen(reg1.usuario);
		if(longitud>=6&&longitud<=10)
		{
			if(int(reg1.usuario[0])>=97&&int(reg1.usuario[0])<=122)
			{
				for(int i=0;i<longitud;i++)
				{
					if(isupper(reg1.usuario[i]))
					{
						mayus++;
					}
				
				if(isdigit(reg1.usuario[i]))
					{
						digit++;
					}	
				}
			}
			else
			{
			printf("\n\t[Error] - El Nombre de Usuario debe comenzar con una letra minuscula..");
			error=0;
			}
			if(mayus>=2)
			{
			if(digit<=3)
			{
			printf("\n\tNOMBRE DE USUARIO REGISTRADO");
			error=0;
			}
			else
			{
			printf("\n\t[Error] - El Nombre de Usuario no tiene al menos tres digitos..");
			error=1;
			}
			}
		else
		{
			printf("\n\t[Error] - El Nombre de Usuario no tiene al menos dos letras mayusculas..");
			error=1;
		}

		}
		else
		{
			printf("\n\t[Error] - El nombre de usuario no tiene la cantidad de caracteres mencionada..");
			error=1;
		}	
	}while(error!=0);

	do{
		caractalfaconsc=0;
		printf("\n\n\tCONTRASENIA: ");
		printf("\n\n\tDebera cumplir los siguientes requisitos: ");
		printf("\n\t1)Debera contener al menos una letra mayuscula, una letra minuscula y un numero.");
		printf("\n\t2)No podra contener ningun caracter de puntuacion, ni acentos, ni espacios. Solo caracteres alfanumericos.");
		printf("\n\t3)Debera tener entre 6 y 32 caracteres.");
		printf("\n\t4)No debe tener mas de 3 caracteres numericos consecutivos. ");
		printf("\n\t5)No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente).");
		printf("\n\tEste criterio es valido tanto para letras mayusculas, minusculas o combinacion de ambas." );
		printf("\n\n\tIngrese la contrasenia: ");
		_flushall();
		cin.getline(reg1.contra,32,'\n');
		longit=strlen(reg1.contra);
		system("cls");
		if(longit>5&&longit<33){
			for(int i=0;i<longit;i++){
				if(isupper(reg1.contra[i])){
					May=true;
				}
				if(islower(reg1.contra[i])){
					Min=true;
				}
				if(isdigit(reg1.contra[i])){
					Num=true;
				}
				if(ispunct(reg1.contra[i])){
					sp=false;
				}
				if(isspace(reg1.contra[i])){
					esp=false;
				}
				if(isalpha(reg1.contra[i])!=0 || isdigit(reg1.contra[i])!=0){
					if (isalpha(reg1.contra[i]) != 0) {
						if ((int(tolower(reg1.contra[i + 1])) - 1) == int(tolower(reg1.contra[i]))) {
							caractalfaconsc=1;
						}
					}
				} else {
					if(caractnumconsec==0){
						caractnumconsec++;
					} else {
						if(isdigit(reg1.contra[i-1])!=0){
							caractnumconsec++;
						} else {
							caractnumconsec=0;
						}	
					}
				} 
			}
		} else {
			printf("\n\tLa contrasenia debe tener entre 6 y 32 caracteres");
			error=0;
		}

		if(May&&Min&&Num){
			if(sp&&esp){
				if(caractalfaconsc==0){
					if(caractnumconsec<3){
						printf("\n\tCONTRASENIA REGISTRADA");
						error=0;
					} else {
						printf("\n\t[Error] - La contrasenia no debe tener mas de tres caracteres numeriocos consecutivos..");
						error=1;
					}
				} else {
					printf("\n\t[Error] - La contrasenia no puede tener 2 letras alfabeticamete consecutivas..");
					error=1;	
				}
			} else {
				printf("\n\t[Error] - La contrasenia no debe tener ni signos de puntuacion,ni acentos,ni espacios..");
				error=1;
			}
		} else {
			printf("\n\tLa contasenia debe tener al menos una letra Mayuscula,una Minuscula y un numero..");
			error=1;
		}    
	}while(error!=0);

    do{
	  printf("\n\n\tIngrese el Apellido y Nombre del Usuario:  ");
	  _flushall();
	  cin.getline(reg1.ApeyNom,60,'\n');
	  compar=strcmp(reg1.ApeyNom,"");
		if(compar==0){
			error=1;
			printf("\n\t[Error] - El campo de Apellido y Nombre del Usuario se encunetra vacio.." );
		} else {
			error=0;
		}
    }while(error!=0);

	printf("\n\tUSUARIO REGISTRADO");
	fwrite(&reg1,sizeof(Usuarios),1,archMA);
	FILE *fp=fopen("NewProgram.dat", "wb");
   	registrar=true;
	fwrite(&registrar, sizeof(bool), 1, fp);
	fclose(fp);
	system("\n\tpause");
	fclose(archMA);
}

bool seRepite(char user[100]){
	Usuarios usuario;
    FILE *fp = fopen("Usuarios.dat", "rb");
    fread(&usuario, sizeof(Usuarios), 1, fp);
    while (!feof(fp)) {
        if (strcmp(user, usuario.usuario) == 0) {
			fclose(fp);
            return false;
        }
        fread(&usuario, sizeof(Usuarios), 1, fp);
    }
    fclose(fp);

    return true;
}

void RegEntrenador(Entrenadores regg1, FILE *archMA){
	char nombreDoctor[50];
	int compar,dias;
	float aux;
	Entrenadores entrenador;
	int longitud,longit,digit=0,caractalfaconsc=0,caractnumconsec=0, c=0;
	bool May=false;
	bool Min=false;
	bool Num=false;
	bool sp=true;
	bool esp=true;
	bool error,encontrado=0;
	FILE *fp;
	archMA=fopen("Entrenadores.dat","a+b");
	
	do{
		system("cls");
		printf("\n\tIngrese el Apellido y Nombre del Entrenador: ");
		_flushall();
		cin.getline(regg1.ApellidoyNombre,60,'\n');
		compar=strcmp(regg1.ApellidoyNombre,"");
		if(compar==0){
			error=1;
			printf("\n\t[Error] - El campo de Apellido y Nombre del Usuario se encuentra vacio.." );
		} else {
			error=0;
		}
	}while(error!=0);

		do{
			printf("\n\tIngrese cuantos dias trabaja el entrenador en la semana (Maximo 6): ");
			scanf("%d",&dias);
			if(dias>6){
				printf("\n\tMaximo de dias permitidos: 6\n");
			}
		} while (dias>6);
		

		for(int i=0; i<6; i++){
			if(i<dias){
				do{
					printf("\n\t%d. Dia: ",i+1);
					_flushall();
					cin.getline(regg1.Dias[i],10,'\n');
					if(!listaDias(regg1.Dias[i])){
						printf("\n\t[Error] - Se debe ingresar un dia de la semana..\n");
					}
				}while(!listaDias(regg1.Dias[i]));
			} else {
				strcpy(regg1.Dias[i], "-");
			}
		}

		fp = fopen("Entrenadores.dat", "rb");
		if(fp!=NULL){
			fread(&entrenador, sizeof(Entrenadores), 1, fp);
			while (!feof(fp)){
				c++;
				fread(&entrenador, sizeof(Entrenadores), 1, fp);
			}
			regg1.legajo=c;
		} else {
			regg1.legajo=0;
		}
		fclose(fp);
			
	do{	
		caractalfaconsc=0;
		printf("\n\n\tContrasenia del Entrenador: ");
		printf("\n\n\tDebera cumplir los siguientes requisitos: ");
		printf("\n\t1)Debera contener al menos una letra mayuscula, una letra minuscula y un numero.");
		printf("\n\t2)No podra contener ningun caracter de puntuacion, ni acentos, ni espacios. Solo caracteres alfanumericos.");
		printf("\n\t3)Debera tener entre 6 y 32 caracteres.");
		printf("\n\t4)No debe tener mas de 3 caracteres numericos consecutivos. ");
		printf("\n\t5)No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente).");
		printf("\n\tEste criterio es valido tanto para letras mayusculas, minusculas o combinacion de ambas." );
		printf("\n\n\tIngrese la contrasenia: ");
		_flushall();
		cin.getline(regg1.contrasenia,32,'\n');
		longit=strlen(regg1.contrasenia);
		system("cls");
		if(longit>5&&longit<33)	{
			for(int i=0;i<longit;i++){
				if(isupper(regg1.contrasenia[i])){
					May=true;
				}
				if(islower(regg1.contrasenia[i])){
					Min=true;
				}
				if(isdigit(regg1.contrasenia[i])){
					Num=true;
				}
				if(ispunct(regg1.contrasenia[i])){
					sp=false;
				}
				if(isspace(regg1.contrasenia[i])){
					esp=false;
				}
				if(isalpha(regg1.contrasenia[i])!=0 || isdigit(regg1.contrasenia[i])!=0){
					if (isalpha(regg1.contrasenia[i]) != 0) {
						if ((int(tolower(regg1.contrasenia[i + 1])) - 1) == int(tolower(regg1.contrasenia[i]))) {
							caractalfaconsc=1;
						}
					}
				} else {
					if(caractnumconsec==0){
						caractnumconsec++;
					} else {
						if(isdigit(regg1.contrasenia[i-1])!=0){
							caractnumconsec++;
						} else {
							caractnumconsec=0;
						}	
					}
				} 
			}
		} else {
			printf("\n\tLa contrasenia debe tener entre 6 y 32 caracteres");
			error=0;
		}	
		if(May&&Min&&Num){
			if(sp&&esp){
				if(caractalfaconsc==0){
					if(caractnumconsec<3){
						printf("\n\tCONTRASENIA REGISTRADA");
						error=0;
					} else {
						printf("\n\t[Error] - La contrasenia no debe tener mas de tres caracteres numeriocos consecutivos..");
						error=1;
					}
				} else {
					printf("\n\t[Error] - La contrasenia no puede tener 2 letras alfabeticamete consecutivas..");
					error=1;
				}
			} else {
				printf("\n\t[Error] - La contrasenia no debe tener ni signos de puntuacion,ni acentos,ni espacios..");
				error=1;
			}
		} else {
			printf("\n\t[Error] -La contasenia debe tener al menos una letra Mayuscula,una Minuscula y un numero..");
			error=1;
		}    
	}while(error==0);

	printf("\n\tEl legajo del entrenador es: %d\n\t", regg1.legajo);
	fwrite(&regg1,sizeof(Entrenadores),1,archMA);
	fclose(archMA);
	system("pause");
}

bool listaDias(char dia[10]){
	Dia validos[6]={"lunes","martes","miercoles","jueves","viernes","sabado"};
	char dialwr[10];
	strcpy(dialwr, dia);
	strlwr(dialwr);
	for(int i=0; i<6; i++){
		if(strcmp(validos[i],dialwr)==0){
			return true;
		}
	}
	return false;
}
