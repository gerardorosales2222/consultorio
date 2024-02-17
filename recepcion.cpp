//Usuario: adminUTN // Contraseņa: admin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void listarTurnos(FILE *archTur);
FILE *f_prof, *archPac, *archTur;

bool autenticar();
void registrarPaciente(FILE *archPac);
void registrarTurno(FILE *archPac);

int main(){
	system("TITLE RECEPCION");
	int op;
	bool sesion=false;
    Usuarios rec;
    Profesionales pro;
    do{
    	system("CLS");
    	printf("Modulo del recepcionista\n");
    	printf("=========================\n");
    	printf("\n1.- Iniciar Sesion\n");
    	printf("\n2.- Registrar Pacientes\n");
    	printf("\n3.- Registrar Turno\n");
    	printf("\n4.- Listado de Atenciones por Profesional y Fecha\n");
    	printf("\n5.- Cerrar la aplicacion\n");
    	printf("\nIngrese una opcion: ");
    	scanf("%d",&op);
    	switch(op){
    		case 1:
    			system("CLS");
    			if(autenticar()){
    				sesion=true;
    				printf("\nAutenticado \n");
    			}else{
    				printf("\nUsuario o contrasenia incorrecta \n");
    			}
    			system("PAUSE");
    			break;
    		case 2:
    			if(sesion){
    				system("CLS");
    				archPac = fopen("pacientes.dat","ab");
    				registrarPaciente(archPac);
    				fclose(archPac);
    			}else{
    				printf("\n	PRIMERO DEBE INICIAR SESION \n	");
    			}
    			system(" PAUSE");
    			break;
    		case 3:
    			if(sesion){
    				system("CLS");
    				archTur = fopen("turnos.dat","ab");
    				registrarTurno(archTur);
    				fclose(archTur);
    			}else{
    				printf("\n	PRIMERO DEBE INICIAR SESION \n	");
    			}
    			system("PAUSE");
    			break;
    		case 4:
    			system("CLS");
				archTur = fopen("turnos.dat","rb");
    			listarTurnos(archTur);
    			fclose(archTur);
    			system("PAUSE");
				break;
    	}
    }while(op!=5);
    return 0;
}

bool autenticar(){
	Usuarios rec;
	FILE *arch = fopen("recepcionistas.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	_flushall();
    	printf("Usuario: ");
    	gets(usuario);
    	_flushall();
    	printf("Contrasenia: ");
    	gets(contrasenia);
    	while (fread(&rec, sizeof(rec), 1, arch) == 1) {
	        if(strcmp(usuario,rec.Usuario)==0&&strcmp(contrasenia,rec.Contrasenia)==0){
	        	coincidencia = true;
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}

void registrarPaciente(FILE *archPac){
	Pacientes pac;
	pac.baja = 0;
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(pac.ApeNom);
	_flushall();
	printf("DNI: ");
	gets(pac.DNI);
	_flushall();
	printf("Localidad: ");
	gets(pac.Localidad);
	_flushall();
	printf("Tel: ");
	gets(pac.Telefono);
	_flushall();
	printf("Fecha de Nac \n->Dia: ");
	scanf("%d",&pac.FechaDeNac.dia);	
	printf("->Mes: ");
	scanf("%d",&pac.FechaDeNac.mes);
	printf("->Anio: ");
	scanf("%d",&pac.FechaDeNac.anio);
	_flushall();
	fwrite(&pac,sizeof(pac),1,archPac);	
}

void registrarTurno(FILE *archTur){
	Turnos tur;
	tur.baja = 0;
	_flushall();
	printf("ID Medico: ");
	scanf("%d",&tur.IdProfesional);
	_flushall();
	printf("Fecha Atencion \n->Dia: ");
	scanf("%d",&tur.FechaAtencion.dia);	
	printf("->Mes: ");
	scanf("%d",&tur.FechaAtencion.mes);
	printf("->Anio: ");
	scanf("%d",&tur.FechaAtencion.anio);
	_flushall();
	printf("DNI Paciente: ");
	gets(tur.DNI);
	_flushall();
	printf("Detalle atencion: ");
	gets(tur.DetalleAtencion);
	_flushall();
	fwrite(&tur,sizeof(tur),1,archTur);
}

void listarTurnos(FILE *archTur){
	Turnos tur;
	int pro;
	Fecha f;
	if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  }
	printf("Ingrese ID del profesional: ");
	scanf("%d",&pro);
	printf("Ingrese Fecha de Atencion \n->Dia: ");
	scanf("%d",&f.dia);	
	printf("->Mes: ");
	scanf("%d",&f.mes);
	printf("->Anio: ");
	scanf("%d",&f.anio);
  while (fread(&tur, sizeof(tur), 1, archTur) == 1) {
  	if(tur.IdProfesional == pro 
	&& tur.FechaAtencion.anio == f.anio
	&& tur.FechaAtencion.mes == f.mes
	&& tur.FechaAtencion.dia == f.dia)
	{
	  	printf("\nProfesional: %d \n", tur.IdProfesional);
    	printf("Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  		printf("Detalle: %s \n", tur.DetalleAtencion);
	}
  }
}
