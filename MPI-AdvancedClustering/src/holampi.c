#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv){
	int p, pid;
	int c = 10; // celulas
	int i = 5; // numero de iteraciones

	MPI_Status status;
	MPI_Init (&argc,&argv);
	MPI_Comm_size ( MPI_COMM_WORLD, &p );
	MPI_Comm_rank ( MPI_COMM_WORLD, &pid );      

	//Para todos 
	int road[c]; // vector
	int mypart[c]; //copia para nodos
	int desp[p]; // para el master
	int tam[p]; // para el scatter master
	int n_part = ceil(c/(p-1)); // cuantas partes por nodo, el master no cuenta

	// Master Node
	if(pid == 0){
		printf("Master enable\n");
		printf("Se repartiran %d celulas por %d nodos\n", n_part, p);
		//road = (int *)malloc(sizeof(int)*(c)); // separa memoria
		for(int k=0; k<c; k++){ // llena el vector road
			road[k]=k;
			printf("%d ",road[k] );
		}printf("\n");

		int rest = c;
		for(int i=0; i<p; i++){ 
        if(rest>0){
            tam[i] = n_part+1;
            rest--;
        }else{
            tam[i] = n_part;
        }
        if(i==0){
            desp[i]= tam[i];
        }else{
            desp[i]= desp[i-1]+tam[i];
        }   
        rest -= tam[i];
    }
		printf("Se repartio\n");
		for(int i=0; i<p; i++){ 
			printf("%d -> %d \n",tam[i],desp[i]);
		}

		// Msg to slave nodes
		for(int node=1;node<p;node++){ // todos los disponibles
			printf("Yo los invoco\n");
			MPI_Send(&code,1,MPI_INT,i,1,MPI_COMM_WORLD);
		}
		MPI_Finalize();
		return 0;
	} // fin master

	//Node 
	int next, from; // id del nodo anterior y siguiente
	printf("Slave # %d\n",pid);
	for(int k=0; k<c; k++){ // llena el vector
		mypart[k]=0;
	}
	// se forma un anillo de nodos para separar el vector entre ellos
	next = (pid + 1) % p;
	from = (pid + p - 1) % p;
	if (next = 0) next = 1; // no apunta al master, sino al primer nodo
	int rta;
	printf("%d : Esperando ando\n",pid);
	//MPI_Recv(&rta,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("Al proceso %d, le corresponde %d a %d \n",pid,mypart[0],mypart[n_part-1]);
	//MPI_Finalize();
	return 0;

}
