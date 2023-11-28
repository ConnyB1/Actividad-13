//Cesar Alejandro Velazquez Mercado
//372329
//Me guarda unos registros y me da el archivo de texto y un archivo binario
//19/11/2023
#include <stdio.h>
#include "Funciones.h"


typedef struct _Talum 
{
    int status;
    int matricula;
    char ApPat[30];
    char ApMat[30];
    char Nombre[60]; 
    int edad;  
    char sexo[7];
} reg;
reg registros[5000]; 
//Tkey == reg
int n = 0; 
void agregarAutomatico(reg registros[], int *n);
void buscarPorMatricula(reg registros[], int n, int matricula);
void ordenarPorMatricula(reg registros[], int n);

int estaOrdenadoPorMatricula(reg registros[], int n);
void ordenarPorMatriculaSeleccion(reg registros[], int n);
void ordenarPorMatriculaBurbuja(reg registros[], int n);

void impr_reg(reg registros[], int n);
char *nombres(char genero);
char *apellidos();

void eliminarRegistro(reg registros[], int *n, int matricula);
void editar(reg registros[], int *n, int matricula);
void generarArchivo(reg registros[], int n);

void borrarContenidoArchivo(const char *nombreArchivo);
void mostrarArchivo(char *nombre);
int gen_Arch_bin(reg registros[], int n);

void cargarArchivoBinario(reg registros[], int *n);
void mostrarBorrados(reg registros[], int n);

int main()
{
    srand(time(NULL));
    int op, archivoCargado = 0, matricula;
    

    do
    {
        printf("\n\tmenu\n");
        printf("1.- AGREGAR (AUTOM 100 REGISTROS)\n");
        printf("2.- EDITAR REGISTRO\n");
        printf("3.- ELIMINAR REGISTRO (lógico)\n");
        printf("4.- BUSCAR \n");
        printf("5.- ORDENAR\n");
        printf("6- IMPRIMIR\n");
        printf("7.- GENERAR ARCHIVO TEXTO\n");
        printf("8.- VER ARCHIVO TEXTO\n");
        printf("9.- CREAR ARCH BINARIO\n");
        printf("10.- CARGAR ARCH BINARIO\n");
        printf("11.- MOSTRAR ELIMINADOS\n");
        printf("\n0.- Salir\n");
        op= valinum(0, 11);
        if(op == 1)
        {
            agregarAutomatico(registros, &n);
        }
        else
        {
            if(op == 2)
            {
                printf("Ingrese la matricula que desea editar: ");
                matricula = valinum(300000, 399999);
                editar(registros, &n, matricula);
                printf("\n\n");
                system("pause");
                system("cls"); 
            }
            else
            {
                if (op == 3)
                {
                    printf("\ningresa la matricula que deseas borrar: ");
                    matricula = valinum(300000, 399999);
                    eliminarRegistro(registros, &n, matricula);
                    printf("\n\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    if (op == 4)
                    {
                        printf("Ingrese la matricula que desea buscar: ");
                        matricula = valinum(300000, 399999);
                        buscarPorMatricula(registros, n, matricula);
                        printf("\n\n");
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        if (op == 5)
                        {
                            ordenarPorMatricula(registros, n);
                        }
                        else
                        {
                            if (op == 6)
                            {
                                impr_reg(registros, n);
                            }
                            else
                            {
                                if (op == 7)
                                {
                                    generarArchivo(registros, n);
                                }
                                else
                                {
                                    if (op == 8)
                                    {
                                        char nombreArchivo[50];
                                        printf("Ingrese el nombre del archivo a mostrar (sin extensión .txt): ");
                                        leercadena(nombreArchivo, sizeof(nombreArchivo));
                                        char nombreCompleto[100];
                                        sprintf(nombreCompleto, "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 13\\%s.txt", nombreArchivo);
                                        mostrarArchivo(nombreCompleto);
                                        printf("\n\n");
                                        system("pause");
                                        system("cls");
                                    }
                                    else
                                    {
                                        if (op == 9)
                                        {
                                            gen_Arch_bin(registros, n);
                                            
                                        }
                                        else
                                        {
                                            if (op == 10)
                                            {
                                                cargarArchivoBinario(registros, &n);
                                            }
                                            else
                                            {
                                                if (op == 11)
                                                {
                                                    mostrarBorrados(registros, n);
                                                }
                                            }
                                        }
                                        
                                    }
                                    
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
            }
        }
    } while (op != 0);
}

void agregarAutomatico(reg registros[], int *n) 
{
    if (*n + 100 > 5000) 
    {
        printf("No se pueden agregar 100 registros automáticamente, ya que superaría el límite de registros.\n");
        return;
    }

    int indice = *n;
    for (int i = 0; i < 100; i++) 
    {
        if (indice >= 5000) 
        {
            printf("Se ha alcanzado el máximo de registros permitidos.\n");
            break;
        }
        registros[indice].status = 1;
        registros[indice].matricula = valinumran(300000, 399999);
        char gen = (rand() % 2 == 0) ? 'M' : 'F';
        if (gen == 'F')
        {
            strcpy(registros[indice].sexo, "MUJER");
        }
        if (gen == 'M')
        {
            strcpy(registros[indice].sexo, "HOMBRE");
        }
        char *nombreGenerado = nombres(gen);
        strcpy(registros[indice].Nombre, nombreGenerado);
        strcpy(registros[indice].ApPat, apellidos());
        strcpy(registros[indice].ApMat, apellidos());
        registros[indice].edad = valinumran(0, 100);
        indice++;
    }
    *n = indice; 
}

void buscarPorMatricula(reg registros[], int n, int matricula) 
{
    int encontrado = 0;

    if (n <= 100) 
    {
        ordenarPorMatriculaSeleccion(registros, n);
        printf("\nUtilizando el metodo de búsqueda por seleccion.\n\n");
    } 
    else 
    {
        ordenarPorMatriculaBurbuja(registros, n);
        printf("\nUtilizando el metodo de busqueda por burbuja.\n\n");
    }

    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) 
    {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (registros[medio].matricula == matricula && registros[medio].status == 1) 
        {
            printf("Registro encontrado:\n");
            printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", medio + 1, registros[medio].matricula, registros[medio].Nombre, registros[medio].ApPat, registros[medio].ApMat, registros[medio].edad, registros[medio].sexo);
            encontrado = 1;  
            break;
        } 
        else 
        {
            if (registros[medio].matricula < matricula) 
            {
                izquierda = medio + 1;
            } 
            else 
            {
                derecha = medio - 1;
            } 
        }
    }

    if (!encontrado) 
    {
        printf("No se encontró un registro con la matrícula %d.\n", matricula);
    }
}

void ordenarPorMatricula(reg registros[], int n)
{
    if (estaOrdenadoPorMatricula(registros, n))
    {
        printf("El arreglo ya está ordenado por matrícula. No es necesario ordenarlo de nuevo.\n");
    }
    else
    {
        int tamanio = n;

        if (tamanio <= 100)
        {
            ordenarPorMatriculaSeleccion(registros, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de selección.\n");
        }
        else
        {
            ordenarPorMatriculaBurbuja(registros, tamanio);
            printf("El arreglo ha sido ordenado por matrícula utilizando el algoritmo de burbuja.\n");
        }
    }
}
int estaOrdenadoPorMatricula(reg registros[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (registros[i].matricula < registros[i - 1].matricula)
        {
            return 0; 
        }
    }
    return 1;
}

void ordenarPorMatriculaSeleccion(reg registros[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (registros[j].status == 1 && (registros[j].matricula < registros[minIndex].matricula))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            reg temp = registros[i];
            registros[i] = registros[minIndex];
            registros[minIndex] = temp;
        }
    }
}

void ordenarPorMatriculaBurbuja(reg registros[], int n)
{
    int intercambio;
    for (int i = 0; i < n - 1; i++)
    {
        intercambio = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (registros[j].status == 1 && (registros[j].matricula > registros[j + 1].matricula))
            {
                reg temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
                intercambio = 1;
            }
        }
        if (intercambio == 0)
        {
            break; 
        }
    }
}

char *nombres(char genero)
{
    char nombresMas[][30] = {
        "Juan", "Carlos", "Luis", "Segismundo", "Diego",
        "Andres", "Soponcio", "Jose", "Felipe", "Rafael",
        "Obama", "Adolfo", "Fernando", "Cipriano", "Francisco",
        "David", "Emilio", "Miguel", "Alberto", "Roberto"
    };
    char nombresFem[][30] = {
        "Maria", "Ana", "Sofia", "Laura", "Isabel",
        "Digna", "Clara", "Adriana", "Valeria", "Daniela",
        "Carolina", "Paola", "Camila", "Natalia", "Andrea",
        "Lucia", "Verónica", "Ana", "Beatriz", "Marciana"
    };

    char *nombreElegido = (char *)malloc(31);
    if (genero == 'M')
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresMas[nom]);
    }
    else
    {
        int nom = rand() % 20;
        strcpy(nombreElegido, nombresFem[nom]);
    }

    return nombreElegido;

}

char *apellidos()
{
    char listaApellidos[][30] = {
        "Garcia", "Martinez", "Lopez", "Rodriguez", "Perez",
        "Fernandez", "Gonzalez", "Sánchez", "Ramirez", "Torres",
        "Jimenez", "Díaz", "Vargas", "Romero", "Suarez",
        "Mendoza", "Ortega", "Hernández", "Silva", "Rojas",
        "Cruz", "Morales", "Núñez", "Guerrero", "Paredes",
        "Salazar", "Estrvez", "Figueroa", "Valencia", "Molina"
    };

    char *apellidoElegido = (char *)malloc(31); 
    int indice = rand() % 30;
    strcpy(apellidoElegido, listaApellidos[indice]);

    return apellidoElegido;
}

void impr_reg(reg registros[], int n) 
{
    int registrosPorPagina = 40;
    int paginas = (n + registrosPorPagina - 1) / registrosPorPagina; 

    for (int pagina = 0; pagina < paginas; pagina++) 
    {
        int inicio = pagina * registrosPorPagina;
        int fin = (pagina + 1) * registrosPorPagina;
        if (fin > n) {
            fin = n;
        }
        printf("Listado de registros:\n\n");
        printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
        for (int i = inicio; i < fin; i++) 
        {
        if (registros[i].status == 1) 
        {
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
        }
    }

        if (pagina < paginas - 1) 
        {
            printf("Presiona Enter para continuar...");
            while (getch() != 13) {} 
            system("cls");
        }
    }
}

void eliminarRegistro(reg registros[], int *n, int matricula)
{
    int encontrado = 0;

    for (int i = 0; i < *n; i++)
    {
        if (registros[i].matricula == matricula && registros[i].status == 1)
        {
            printf("Registro encontrado:\n");
            printf("Matrícula: \t%d\n", registros[i].matricula);
            printf("Nombre: \t%s\n", registros[i].Nombre);
            printf("Apellido Paterno: \t%s\n", registros[i].ApPat);
            printf("Apellido Materno: \t%s\n", registros[i].ApMat);
            printf("Sexo: \t%s\n", registros[i].sexo);
            printf("¿Desea eliminar este registro (s/n)? ");
            char respuesta = tolower(getch()); 
            if (respuesta == 's')
            {
                registros[i].status = 0; 
                printf("Registro con matrícula %d eliminado de forma lógica.\n", matricula);;
            }
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
    {
        printf("No se encontró un registro activo con la matrícula %d.\n", matricula);
    }
}

void editar(reg registros[], int *n, int matricula)
{
    int encontrado = 0;

    for (int i = 0; i < *n; i++)
    {
        if (registros[i].matricula == matricula && registros[i].status == 1)
        {
            printf("Registro encontrado:\n");
            printf("Matrícula: \t%d\n", registros[i].matricula);
            printf("Nombre : \t%s\n", registros[i].Nombre);
            printf("Apellido Paterno: \t%s\n", registros[i].ApPat);
            printf("Apellido Materno: \t%s\n", registros[i].ApMat);
            printf("Sexo: \t%s\n", registros[i].sexo);
            printf("¿Cual registro desea cambiar? ");
            printf("1)MATRICULA || 2)NOMBRE || 3)APELLIDO PATERNO || 4)APELLIDO MATERNO || 5)SEXO ");
            int op = valinum(1, 5);
            if (op == 1)
            {
                printf("¿Que matricula le vas a poner? ");
                int op2 = valinum(30000, 399999);
                registros[i].matricula = op2;
            }
            else
            {
                if (op == 2)
                {
                    leercadena(registros[i].Nombre, sizeof(registros[i].Nombre));
                }
                else
                {
                    if (op == 3)
                    {
                        leercadena(registros[i].ApPat, sizeof(registros[i].ApPat));
                    }
                    else
                    {
                        if (op == 4)
                        {
                            leercadena(registros[i].ApMat, sizeof(registros[i].ApMat));
                        }
                        else
                        {
                            if (op == 5)
                            {
                                printf("M) Hombre || F) Mujer");
                                char op2 = getch();
                                op2 = tolower(op2);
                                if (isalpha(op2))
                                {
                                    if (op2 == 'M')
                                    {
                                       strcpy(registros[i].sexo, "HOMBRE");
                                    }
                                    else
                                    {
                                        if (op2 == 'F')
                                        {
                                            strcpy(registros[i].sexo, "MUJER");
                                        }
                                        
                                    }
                                
                                    
                                    printf("%c", op2);
                                }
                                printf("\n\n");
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
    {
        printf("No se encontró un registro activo con la matrícula %d.\n", matricula);
    }
}

void generarArchivo(reg registros[], int n) 
{
    
    char nombreArchivo[50];
    printf("Ingresa el nombre del archivo (sin la extensión .txt): ");
    leercadena( nombreArchivo, sizeof(nombreArchivo));

    borrarContenidoArchivo(nombreArchivo);

    FILE *archivo;
    char nombreCompleto[100]; 
    sprintf(nombreCompleto, "C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 13\\%s.txt", nombreArchivo);


    archivo = fopen(nombreCompleto, "w");

    if (archivo != NULL) 
    {
        fprintf(archivo, "%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
        for (int i = 0; i < n; i++) 
        {
            if (registros[i].status == 1) 
            {
                fprintf(archivo, "%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
            }
        }
        fclose(archivo);
        printf("\n\nArchivo '%s' generado con éxito.\n", nombreCompleto);
    } 
    else 
    {
        printf("No se pudo abrir el archivo para escritura.\n");
    }
}

void borrarContenidoArchivo(const char *nombreArchivo) 
{
    FILE *archivo;
    archivo = fopen(nombreArchivo, "w");
    fprintf(archivo, " "); 
    fclose(archivo);
}

void mostrarArchivo(char *nombre) 
{
    FILE *archivo;
    char contenido[1000];

    archivo = fopen(nombre, "r");
    if (archivo == NULL) 
    {
        printf("El archivo %s no se encontró.\n", nombre);
    }
    else
    {
        printf("Contenido del archivo %s:\n", nombre);
        while (fgets(contenido, sizeof(contenido), archivo) != NULL) 
        {
            printf("%s", contenido);
        }
    }
    
    fclose(archivo);
}

int gen_Arch_bin(reg registros[], int n)
{
    reg rege;
    int i;
    FILE *fa;
    
    fa = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 13\\datos.tmp", "ab");

    if (fa == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        rege = registros[i];
        if (fwrite(&rege, sizeof(reg), 1, fa) != 1)
        {
            perror("Error writing to file");
            fclose(fa);
            return 1;
        }
    }

    fflush(fa);
    fclose(fa);
    return 0;
}

void cargarArchivoBinario(reg registros[], int *n)
{
    FILE *fa;
    fa = fopen("C:\\Users\\costco\\Documents\\Programacion estructurada\\Actividad 13\\datos.dll", "rb");

    if (fa == NULL)
    {
        printf("El archivo binario 'datos.dll' no se encontró.\n");
        return;
    }

    reg rege;
    int i = 0;
    while (fread(&rege, sizeof(reg), 1, fa) == 1)
    {
        registros[i] = rege;
        i++;
    }

    fclose(fa);
    *n = i;
    printf("Registros cargados desde el archivo binario 'datos.dll'.\n");
}

void mostrarBorrados(reg registros[], int n) 
{
    printf("Listado de registros eliminados:\n\n");
    printf("%-12s %-15s %-15s %-15s %-15s %-15s %-15s\n", "N", "Matrícula", "Nombre", "Ap. Paterno", "Ap. Materno", "Edad", "Sexo");
    int encontrado = 0;
    for (int i = 0; i < n; i++) 
    {
        if (registros[i].status == 0) 
        {
            encontrado = 1;
            printf("%-12d %-15d %-15s %-15s %-15s %-15d %-15s \n", i + 1, registros[i].matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].edad, registros[i].sexo);
        }
    }
    if (!encontrado) 
    {
        printf("No se encontraron registros eliminados.\n");
    }
}