/*Práctica 1: Programación estructurada
Equipo:
Marlene Tepal Romero
Jafet Jesus Perez Sanchez
Brandon Morales González
Torres Robles Joseph
Daniel Mendez Luna

Realizar un programa en lenguaje C

Realizar una agenda de datos de una firma de abogados, con los datos de: nombre, direccion, telefono, horario y especialidad (general, familiar,
civil, laboral, penal, administrativo,inmobiliario o asistencia familiar).
Los datos serán guardados en un archivo binario (estructurado) para posteriormente poder ser recuperados.
Las opciones dentro del programa son: alta de un abogado, mostrar a un abogado en particular y mostrar todos los datos que se tienen.
Las opciones dentro del programa son: alta de un abogado, mostrar a un abogado en particular y mostrar todos los datos que se tienen.*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
  #include<windows.h>
#endif  
//Valores globales y guardado
#define MAX_ABOGADOS 10
#define FILENAME "agenda_abogados.bin"
int cant=0;

//Estructura del registro
typedef struct{
    char nombre[30];
    char especialidad[20];
    char direccion[100];
    char telefono[10];
    char horario[10];
    }Abogado;

//Funcion para limpiar la pantalla en cualquier sistema
void limpiar_pantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
//Funcion para cargar el archiVo .bin
void cargar_archivo(Abogado abogados[],int *cont){
    FILE *file = fopen(FILENAME,"rb");
    if (file == NULL) {
        printf("No se encontro un archivo, creando archivo nuevo.\n");
        return;
    }
    *cont = fread(abogados, sizeof(Abogado), MAX_ABOGADOS, file);
    fclose(file);
    printf("Datos cargados exitosamente desde el archivo %s\n", FILENAME);

}
//Funcion para guardar el archivo
void guardar_archivo(Abogado abogados[], int cont) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    fwrite(abogados, sizeof(Abogado), cont, file);
    fclose(file);
    printf("Datos guardados exitosamente en el archivo %s\n", FILENAME);
}
//Funcion Seleccion especialidad
void selec_espe(Abogado abogados[],int **cont){
    int opcion;
     do {   
            limpiar_pantalla();
            printf("Seleccione especialidad\n");
            printf("1.General\n");
            printf("2.Familiar\n");
            printf("3.Laboral\n");
            printf("4.Penal\n");
            printf("5.Administrativo\n");
            printf("6.Inmobiliario\n");
            printf("7.Civil\n");
            printf("8.Asistencia Familiar\n");
            scanf("%d", &opcion);
            switch (opcion) {
                         case 1:
                              strcpy(abogados[**cont].especialidad, "General");
                         break;
                         case 2:
                         strcpy(abogados[**cont].especialidad, "Familiar");
                         break;
                         case 3:
                              strcpy(abogados[**cont].especialidad, "Laboral");
                         break;
                         case 4:
                         strcpy(abogados[**cont].especialidad, "Penal");
                         break;
                         case 5:
                              strcpy(abogados[**cont].especialidad, "Administrativo");
                         break;
                         case 6:
                         strcpy(abogados[**cont].especialidad, "Inmobiliario");
                         break;
                         case 7:
                              strcpy(abogados[**cont].especialidad, "Civil");
                         break;
                         case 8:
                         strcpy(abogados[**cont].especialidad, "Asistencia Familiar");
                         break;
                         default:
                    printf("Opción no válida\n");
                    continue;  // Repetir el ciclo si la opción no es válida
            }
            break;  // Salir del ciclo si la opción es válida
        } while (1);
}
//Funcion para agregar un Abogado
void agregar(Abogado abogados[], int *cont) {
    int cont_aux;
    bool aux;
    if (*cont < MAX_ABOGADOS) {
        do{
            printf("Ingrese la cantidad de abogados a agregar\n");
            scanf("%d",&cont_aux);
            limpiar_pantalla();
            if(((*cont)+cont_aux)< MAX_ABOGADOS){
                for(int i=0;i<cont_aux;i++){

                    printf("");
                    fgets(abogados[*cont].nombre, 30, stdin); //bug
                    printf("Ingrese el nombre del abogado: ");
                    fgets(abogados[*cont].nombre, 30, stdin);
                    abogados[*cont].nombre[strcspn(abogados[*cont].nombre, "\n")] = '\0';

                    selec_espe(abogados,&cont);
                    
                    printf("");
                    fgets(abogados[*cont].direccion, 100, stdin);
                    printf("Ingrese la direccion: ");
                    fgets(abogados[*cont].direccion, 100, stdin);
                    abogados[*cont].direccion[strcspn(abogados[*cont].direccion, "\n")] = '\0';

                    printf("Ingrese el telefono: ");
                    fgets(abogados[*cont].telefono, 10, stdin);
                    abogados[*cont].telefono[strcspn(abogados[*cont].telefono, "\n")] = '\0';
                    
                    printf("");
                    fgets(abogados[*cont].horario, 10, stdin);//bug
                    printf("Ingrese el horario: (formato: 00:00-24:00)");
                    fgets(abogados[*cont].horario, 10, stdin);
                    abogados[*cont].horario[strcspn(abogados[*cont].horario, "\n")] = '\0';

                    (*cont)++;
                    printf("Abogado agregado exitosamente!\n");
                    cant=1;
                    getch();
                    limpiar_pantalla();
                }
            }else{
                printf("La cantidad de abogados supera al maximo");
                aux=true;
                getch();
                limpiar_pantalla();
            }
        }while(aux);
    } else {
        printf("No se pueden agregar mas abogados\n");
        limpiar_pantalla();
    }
}
// Función para mostrar todos los abogados
void mostrar(Abogado abogados[], int cont) {
    if (cont == 0) {
        printf("No hay abogados en la agenda.\n");
    } else {
        for (int i = 0; i < cont; i++) {
            printf("\n--- Abogado %d ---\n", i + 1);
            printf("Nombre: %s", abogados[i].nombre);
            printf("\tEspecialidad: %s", abogados[i].especialidad);
            printf("\tDireccion: %s", abogados[i].direccion);
            printf("\tTelefono: %s", abogados[i].telefono);
            printf("\tHorario: %s\n", abogados[i].horario);
        }
    }
    getch();
}
//Funcion para mostrar un abogado en particular
void buscar(Abogado abogados[], int cont) {
    char nombre_busqueda[25];
    int encontrado = 0;

    if (cont == 0) {
        printf("No hay abogados en la agenda.\n");
        return;
    }
    printf("");
    fgets(nombre_busqueda, 50, stdin);//bug
    printf("Ingrese el nombre del abogado que desea buscar: ");
    fgets(nombre_busqueda, 50, stdin);
    nombre_busqueda[strcspn(nombre_busqueda, "\n")] = '\0';  // Eliminar el salto de línea

    for (int i = 0; i < cont; i++) {
        if (strcasecmp(abogados[i].nombre, nombre_busqueda) == 0) {
            printf("\n--- Abogado Encontrado ---\n");
            printf("Nombre: %s", abogados[i].nombre);
            printf("\tEspecialidad: %s\n", abogados[i].especialidad);
            printf("\tDireccion: %s", abogados[i].direccion);
            printf("\tTelefono: %s", abogados[i].telefono);
            printf("\tHorario: %s", abogados[i].horario);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró un abogado con el nombre: %s\n", nombre_busqueda);
    }
    getch();
}
//Funcion Para marcar errores...
void error_opc(){
    printf("Opcion/dato(s) incorrecto(s)...\n");
    getch();
}
//Funcion del Menu
int menu(){
    int n;
    printf("\t      [MENU]\n");
    printf("\t1-Alta de Abogado\n");
    if(cant>0){
        printf("\t2-Mostrar Abogado Particular\n");
        printf("\t3-Mostrar todos los abogados\n");
    }
    printf("\t4-Guardar y Salir\n");
    printf("Ingrese el numero de la opcion...\n");
    scanf("%d",&n);
    limpiar_pantalla();
    return n;
}  
//funcion Principal
int main (){
    Abogado abogados [MAX_ABOGADOS];
    int opc;
    int cont=0;
    printf("\t [Abogados BUAP]\n");
    cargar_archivo(abogados, &cont);
    cant=cont;
    printf("Cargando archivos ...\nPresione enter para continuar...");
    getch();
    limpiar_pantalla();
    do{
        printf("\t [Abogados BUAP]\n");
        opc=menu();
        switch(opc){
            case 1:{
                agregar(abogados,&cont);
                limpiar_pantalla();
                break;
                }
            case 2:{
                buscar(abogados,cont);
                limpiar_pantalla();
                break;
                }
            case 3:{
                mostrar(abogados,cont);
                limpiar_pantalla();
                break;
                }
            case 4:{
                guardar_archivo(abogados,cont);
                break;
                }
            default: {
                error_opc();
                limpiar_pantalla();
            }
        }

    }while(opc!=4);

    

}
