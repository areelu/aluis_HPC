#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, x0, m, i, sum, recv_val;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Introduce el valor inicial (x0): ");
        scanf("%d", &x0);
        printf("Introduce el número de ciclos (m): ");
        scanf("%d", &m);
    }

    MPI_Bcast(&x0, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sum = x0;
    for (i = 0; i < m; i++) {
        MPI_Send(&sum, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_val, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, &status);
        sum += recv_val;
    }

    printf("Proceso %d: Suma acumulativa = %d\n", rank, sum);

    MPI_Finalize();

    return 0;
}
