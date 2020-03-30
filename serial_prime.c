#include <stdio.h>
#include "mpi.h"
#include <stdbool.h>

int main(argc, argv)
	int argc;
	char **argv;
{
	int rank, size;
	int len;
	double start_time, end_time;
	short int isPrime[10000000000000000001];
	unsigned long t, k, N=10000000000000000000;
	char procname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(procname, &len);
	printf("calculated by %d of %d on node,%s\n", rank,size, procname);
	for(k = 100; k < N; k=k*10) {

		start_time = MPI_Wtime();	

		for(t = 0; t < k; t++) {
			isPrime[t] = 1;
		}
		isPrime[0] = 0;
		isPrime[1] = 0;
		unsigned long int i, j;
		for(i = 2; i*i <= k; ++i) {
			if(isPrime[i]) {
				for( j = i*i; j <= k; j+=i)
					isPrime[j] = 0;
			}
		}
		// for(i = 2; i <= N; i++) { if(isPrime) printf("%d ",i); }
		end_time = MPI_Wtime();
		if(rank == 0)
		    printf("%d,%f\n",k, end_time-start_time);
	}
	return 0;
}
