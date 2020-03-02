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

	short int isPrime[10000];
	unsigned long int t, N = 1000;
	unsigned long int low, high;
	unsigned long int i, j, next = 1; //next = 1 is no. 2(first prime)
	unsigned long int* data;
	low = rank*(N/size);
	high = (rank + 1)*(N/size) - 1;
// Note: PE with rank 1 should have atleast sqrt(N) nos.

	for(t = low; t < high+1; t++) {
		isPrime[t] = 1;
	}
//	isPrime[0] = 0;
//	isPrime[1] = 0;
	
	//make processor 0 find the next prime and broadcast
	if(rank == 0) {
		while(!isPrime[next++]);
	}
	MPI_Bcast(&next, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
	// TODO: change start value.
 	for(i = 2; i*i <= high; i++) {
		if(isPrime[i]) {
			for( j = i*i; j <= N; j+=i)
				isPrime[j] = 0;
		}
	}
	// for(i = 2; i <= N; i++) { if(isPrime) printf("%d ",i); } end_time = MPI_Wtime();
	printf("calculated by %d of %d on node %s\n next=%d", rank,size, procname, next);
	printf("Time for serial execution = %f seconds\n",end_time-start_time);
return 0;
}
