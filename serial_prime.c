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
	char procname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(procname, &len);
	start_time = MPI_Wtime();	

	int isPrime[10000];
	int t;
	for(t = 0; t < 10000; t++) {
		isPrime[t] = 1;
	}
	isPrime[0] = 0;
	isPrime[1] = 0;
	unsigned int i, j, N = 1000;
	for(i = 2; i*i <= N; ++i) {
		if(isPrime[i]) {
			for( j = i*i; j <= N; j+=i)
				isPrime[j] = 0;
		}
	}
	// for(i = 2; i <= N; i++) { if(isPrime) printf("%d ",i); }
	end_time = MPI_Wtime();
	printf("calculated by %d of %d on node %s\n", rank,size, procname);
	printf("Time for serial execution = %f seconds\n",end_time-start_time);
return 0;
}
