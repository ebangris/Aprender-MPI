#include <stdio.h> 
#include <stdlib.h>
#include <mpi.h> 
#include <math.h> 

int main(int argc, char** argv)  {   
    int pid, p;
    int size = 15;    
    MPI_Init(&argc, &argv);   
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);   
    MPI_Comm_size(MPI_COMM_WORLD, &p); 
    /*   Inicializaciones en todos los procesos */   
    int A[size], B[size], tam[p], desp[p];         
    for(int i=0; i<size; i++){ 
        A[i] = i; 
        B[i] = 0;
    }
    if (pid == 0) {      
        printf("\n A en P0 = (%d  : %d )\n",A[0],A[size-1]);
        for(int k=0; k < size; k++){
            printf(" %d ",A[k]);   
        }
    }
    int part = (int)(size/p);
    int rest = size % p;
    for(int i=0; i<p; i++){ 
        if(rest>0){
            tam[i] = part+1;
            rest--;
        }else{
            tam[i] = part;
        }
        if(i==0){
            desp[i]= 0;
        }else{
            desp[i]= desp[i-1]+tam[i];
        }   
        rest -= tam[i];
    }
    MPI_Scatterv(&A[0],tam,desp,MPI_INT,&B[0],tam[pid],MPI_INT,0,MPI_COMM_WORLD); 
    printf("\n%d : %d -> %d : %d %d %d %d \n", pid, tam[pid], desp[pid],B[0],B[1],B[2],B[3]);
    for(int i=0;i<p;i++){
        printf(" %d \n", B[i]);
    }
    MPI_Finalize();
    return 0; 
} 