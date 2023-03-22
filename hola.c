#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
        MPI_Init(&argc,&argv);

        int miproc;
        MPI_Comm_rank(MPI_COMM_WORLD, &miproc);
        int numproc;
        MPI_Comm_size(MPI_COMM_WORLD, &numproc);

        float x=(int)miproc;
        printf("%02d: READY. x=%.02f.\n",miproc,x);

        MPI_Barrier(MPI_COMM_WORLD);
        float y=x*x;

        printf("%02d: DONE. y=x*x=%.02f.\n",miproc,y);

        MPI_Finalize();
        return 0;
}

