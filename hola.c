#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int numproc;
	int miproc;
	float x;
	float y;
	float data;
	MPI_Status status;
	float sum = 0.0;
	
	MPI_Init (&argc, &argv); /* Inicializar MPI */

	MPI_Comm_rank(MPI_COMM_WORLD, &miproc); /* Determinar el rango del proceso invocado */
	MPI_Comm_size(MPI_COMM_WORLD, &numproc); /* Determinar el numero de procesos */
	x = miproc;
	//printf("%i: Ready x = %f\n", miproc, x);
	MPI_Barrier (MPI_COMM_WORLD);
	y = x*x;
	//printf("%i:%f^2 = %f\n", miproc, x, y);

	if (miproc == 0) {
	  sum = 1;
	  for (int i = 1; i < numproc; i++) {
	    data = i + 1;
	    printf("Sending: %i -> %i, %f:", 0, i, data);
	    MPI_Send(&data, sizeof(data), MPI_FLOAT, i, 98, MPI_COMM_WORLD);
	    printf("OK.\n");
	  }
	} else { //slaves
	  //printf("Receiving%i -> %i:", 0, miproc);
	  MPI_Recv(&data, sizeof(data), MPI_FLOAT, 0, 98, MPI_COMM_WORLD, &status);
	  //printf("%f: OK.\n", data);
	  data = data * data;
	}

	MPI_Barrier (MPI_COMM_WORLD);

	if (miproc == 0) {
	  for (int i = 1; i < numproc; i++) {
	    MPI_Recv(&data, sizeof(data), MPI_FLOAT, i, 98, MPI_COMM_WORLD, &status);
	    sum += data;
	  }
	  printf("Suma = %f\n", sum);
	} else {
	  MPI_Send(&data, sizeof(data), MPI_FLOAT, 0, 98, MPI_COMM_WORLD);
	}

	MPI_Barrier (MPI_COMM_WORLD);

	
	//printf("%i: Finished!\n", miproc);

	MPI_Finalize ();

	return 0;
}
