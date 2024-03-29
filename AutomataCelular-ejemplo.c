#include <stdio.h>
//Funciones para calcular el techo de un numero.
#include <math.h>
//Funciones para reservar memoria.
#include <stdlib.h>

//Se Castean las funciones que se usaran en este programa
void mostrarArreglo(int **subArrays, int filas, int columnas);
void mostrarPrimerInstanteDeTiempo(int *primerInstante, int dimencion);
int recontruirLaSiguienteGeneracion(int **siguitesInstantes, int*siguienteInstanteDeTiempo, int filas, int columnas, int dimencionDelArray);
void crearSiguientesInstantesDeTiempo(int **instanteDeTiempoAnterior, int **siguienteInstanteDeTiempo, int numeroDeSubArrays, int numeroDeElementos);
void inicarArreglo(int ** arreglo, int numeroDeFilas, int numeroDeColumnas);

//Se Llama a la funcion principal
int main()
{
    //Variables NECESARIAS para el calculo del automata celular
    int numeroDeIteraciones = 1;
    double dimencionDelArray = 14;
    double numeroDeSubArrays = 3;

    //Se obtiene el numero de elementos que poseera los sub array (para cada uno de los calculos)
    //Se castea el valor a int para evitar conflictos de tipos
    int numeroDeSecciones = (int)ceil(dimencionDelArray / numeroDeSubArrays);

    printf("Cada array contara con %d elementos \n" , numeroDeSecciones);

    /*
    if(numeroDeSecciones <= 3)
    {
        printf("Las sub secciones debe tener por lo menos tres (3) elementos para evolucionar");
        return -1;
    }
    */

    //Arryas donde se almacenaran los datos del experimento
    int *primerInstanteDeTiempo = NULL;
    int *sigueinteInstanteDeTiempo = NULL;
    int **subArrays;
    int **subSiguienteInstante;

    //Se reserva memoria para cada elemento necesario

    // se reserva memoria para el primer instante de tiempo
    primerInstanteDeTiempo = (int *)malloc(dimencionDelArray * sizeof(int));
    sigueinteInstanteDeTiempo = (int *)malloc(dimencionDelArray * sizeof(int));

    //Se verifica que exista memoria para los instantes de tiempo
    if(primerInstanteDeTiempo == NULL || sigueinteInstanteDeTiempo == NULL)
    {
        printf("NO existe suficiente memoria para realizar la operacion");
        //Cierra el programa con un error
        return -1;
    }

    //Se reserva memoria para cada uno de los sub arrays
    subArrays = (int **)malloc(numeroDeSubArrays * sizeof(int));
    //Se reserva memoria para cada uno de los elemenos de las sub arrays
    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        //se reseva memoria para cada uno de los items de los sub arrays.
        //Se agregan dos slots adicionales a cada uno de los sub array.
        subArrays[i] = (int *) malloc((numeroDeSecciones + 2) * sizeof(int));
    }

    
    subSiguienteInstante = (int **)malloc(numeroDeSubArrays * sizeof(int));
    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        subSiguienteInstante[i] = (int *)malloc((numeroDeSecciones + 1) * sizeof(int));  
    }

    inicarArreglo(subSiguienteInstante, numeroDeSubArrays, numeroDeSecciones + 1);
    inicarArreglo(subArrays, numeroDeSubArrays, numeroDeSecciones + 2);
    
    printf("siguientes : \n");
    mostrarArreglo(subSiguienteInstante, numeroDeSubArrays, numeroDeSecciones + 1);

    int prueba[] = {0,1,1,0,0,1,0,1,0,0,0,1,1,0};
    //Se llena el arrya para pruebas
    for(int i = 0; i < dimencionDelArray; i++)
    {
        primerInstanteDeTiempo[i] = prueba[i];
        //primerInstanteDeTiempo[i] = i + 1;
    }

    mostrarPrimerInstanteDeTiempo(primerInstanteDeTiempo, dimencionDelArray);

    //Separa el array en sub arrays para su procesamiento
    //Se enviara dos slots adicional en cada una de las sub arrays (para tener vecino derecho e izquierdo)
    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        for(int j = 0; j < numeroDeSecciones; j++)
        {
            //Si es la ultima sub array
            if(i == numeroDeSubArrays - 1)
            {
                //Si NO es la ultima iteracion
                if(numeroDeSecciones * i + j < dimencionDelArray)
                {
                    subArrays[i][j] = primerInstanteDeTiempo[numeroDeSecciones * i + j];
                }
                //Si es la ultima iteracion
                else
                {
                    //Agrega los dos primero elementos del array (simulando una cola circular)
                    subArrays[i][j] = primerInstanteDeTiempo[0];
                    subArrays[i][j + 1] = primerInstanteDeTiempo[1];
                    break;
                }               
            }
            //SI no es la ultima sub array
            else
            {
                //SI no es el ultimo elemento que se agregara en el sub array
                if(j < numeroDeSecciones - 1)
                {
                    subArrays[i][j] = primerInstanteDeTiempo[numeroDeSecciones * i + j];
                }
                //Si es el ultimo elemento que se agregara en el sub array
                else
                {
                    subArrays[i][j] = primerInstanteDeTiempo[numeroDeSecciones * i + j];

                    //Se agregan los dos primeros elementos de la siguiente iteracion (para tener vecidad completa)
                    subArrays[i][j + 1] = primerInstanteDeTiempo[(numeroDeSecciones * i + j) + 1];
                    subArrays[i][j + 2] = primerInstanteDeTiempo[(numeroDeSecciones * i + j) + 2];
                }
            }
        }
    }
    
    //mostrarArreglo(subArrays, numeroDeSubArrays, numeroDeSecciones + 2);

    crearSiguientesInstantesDeTiempo(subArrays, subSiguienteInstante, numeroDeSubArrays, numeroDeSecciones + 1);
    mostrarArreglo(subSiguienteInstante, 3, 6);

    printf("\n");

    recontruirLaSiguienteGeneracion(subSiguienteInstante, sigueinteInstanteDeTiempo, numeroDeSubArrays, numeroDeSecciones, dimencionDelArray);
    printf("la siguiente generacion es \n");
    mostrarPrimerInstanteDeTiempo(sigueinteInstanteDeTiempo, dimencionDelArray);

    
    //siguienteInstanteDeTiempoParaUnaSeccion(numeroDeSecciones + 1, subArrays[0][0], subSiguienteInstante[0][0], 0);

    //mostrarArreglo(sigueinteInstanteDeTiempo, numeroDeSubArrays, numeroDeSecciones);
    

    
    //Se libera la memoria usada para este experimento
    free(primerInstanteDeTiempo);
    free(sigueinteInstanteDeTiempo);
    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        free(subArrays[i]);
    }
    free(subArrays);

    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        free(subSiguienteInstante[i]);
    }
    free(subSiguienteInstante);



    return 0;
}

//Funciones necesarias (Ademas de la principal)

//Crea cada una de las siguientes generaciones
void crearSiguientesInstantesDeTiempo(int **instanteDeTiempoAnterior, int **siguienteInstanteDeTiempo, int numeroDeSubArrays, int numeroDeElementos)
{
    for(int i = 0; i < numeroDeSubArrays; i++)
    {
        for(int j = 1; j < numeroDeElementos; j++)
        {
            //valida que el automata celular solo posea 1s y 0s (se llena con -1 para inicializar)
            if(instanteDeTiempoAnterior[i][j - 1] < 0 || instanteDeTiempoAnterior[i][j] < 0 || instanteDeTiempoAnterior[i][j + 1] < 0)
            {
                continue;
            }
            else
            {
                printf("i: %d ... j: %d \n", i , j);
                //printf("%d %d %d \n", instanteDeTiempoAnterior[i][j-1], instanteDeTiempoAnterior[i][j], instanteDeTiempoAnterior[i][j+1]);

                //Valida cada una de las condiciones de evolucion
                //000 = 0           
                if(instanteDeTiempoAnterior[i][j-1] == 0 && instanteDeTiempoAnterior[i][j] == 0 && instanteDeTiempoAnterior[i][j+1] == 0)
                {
                    siguienteInstanteDeTiempo[i][j] = 0;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //001 = 1
                if(instanteDeTiempoAnterior[i][j-1] == 0 && instanteDeTiempoAnterior[i][j] == 0 && instanteDeTiempoAnterior[i][j+1] == 1)
                {
                    siguienteInstanteDeTiempo[i][j] = 1;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //010 = 1
                if(instanteDeTiempoAnterior[i][j-1] == 0 && instanteDeTiempoAnterior[i][j] == 1 && instanteDeTiempoAnterior[i][j+1] == 0)
                {
                    siguienteInstanteDeTiempo[i][j] = 1;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //011 = 1
                if(instanteDeTiempoAnterior[i][j-1] == 0 && instanteDeTiempoAnterior[i][j] == 1 && instanteDeTiempoAnterior[i][j+1] == 1)
                {
                    siguienteInstanteDeTiempo[i][j] = 1;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //100 = 0
                if(instanteDeTiempoAnterior[i][j-1] == 1 && instanteDeTiempoAnterior[i][j] == 0 && instanteDeTiempoAnterior[i][j+1] == 0)
                {
                    siguienteInstanteDeTiempo[i][j] = 0;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //101 = 1
                if(instanteDeTiempoAnterior[i][j-1] == 1 && instanteDeTiempoAnterior[i][j] == 0 && instanteDeTiempoAnterior[i][j+1] == 1)
                {
                    siguienteInstanteDeTiempo[i][j] = 1;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //110 = 1
                if(instanteDeTiempoAnterior[i][j-1] == 1 && instanteDeTiempoAnterior[i][j] == 1 && instanteDeTiempoAnterior[i][j+1] == 0)
                {
                    siguienteInstanteDeTiempo[i][j] = 1;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }

                //111 = 0
                if(instanteDeTiempoAnterior[i][j-1] == 1 && instanteDeTiempoAnterior[i][j] == 1 && instanteDeTiempoAnterior[i][j+1] == 1)
                {
                    siguienteInstanteDeTiempo[i][j] = 0;
                    //printf("%d", siguienteInstanteDeTiempo[i][j]);
                }
            }
        }
        printf(" parte \n");
    }
    printf("Estas son todas \n");    
}

//Al finalizar el ejercicio todos los elementos son separados, por este motivo es necesario volver a unir la generacion creada
int recontruirLaSiguienteGeneracion(int **siguitesInstantes, int*siguienteInstanteDeTiempo, int filas, int columnas, int dimencionDelArray)
{
    for(int i = 0; i < filas; i++ )
    {
        for(int j = 1; j < columnas + 1; j++)
        {
            //En caso que llegue a la ultima dimencion del array
            if(columnas * i + j == dimencionDelArray)
            {
                //Agrega el ultimo valor al primer slot del arrray
                siguienteInstanteDeTiempo[0] = siguitesInstantes[i][j];
                //En ocaciones la ultima sub array no ocupa todos sus elementos por eso es necesario detener cuado se llega al final
                break;
            }
            //Si no es el ultimo elemento del array
            else
            {
                //agrega el elemento a la posicion correspondiente para el siguiente instante de tiempo
                siguienteInstanteDeTiempo[columnas * i + j] = siguitesInstantes[i][j];
            }
        }
    }
    return 0;
}

//Vara evitar problemas con la memoria es recomendable iniciar los valores del arreglo (Esto tambien nos da control de este)
void inicarArreglo(int ** arreglo, int numeroDeFilas, int numeroDeColumnas)
{
    for(int i = 0; i < numeroDeFilas; i++)
    {
        for(int j = 0; j < numeroDeColumnas; j++)
        {
            //Se inicia los array con el valor de -1 (de forma arbitraria)
            arreglo[i][j] = -1;
        }
    }
}

//Muestra el contenido de una matriz
void mostrarArreglo(int **subArrays, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            //en caso de que el array tenga -1 no muestra nada (fue inicializado de esta forma)
            if(subArrays[i][j] == -1)
            {
                continue;
            }
            else
            {
                printf( "%i ",subArrays[i][j]);
            }            
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

//Muestra el contenido de un vector
void mostrarPrimerInstanteDeTiempo(int *primerInstante, int dimencion)
{
    for(int i = 0; i < dimencion; i++)
    {
        printf("%d " , primerInstante[i]);
    }
    printf("\n");
}
