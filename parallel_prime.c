#include <stdio.h>
#include "mpi.h"
#include <stdbool.h>
#include <math.h>

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

	short int isPrime[1000];
	unsigned long int t, N = 100;
	unsigned long int low, high, start;
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
	while(next < sqrt(N)) {
		if(rank == 0) {
			while(!isPrime[next++] && next < sqrt(N));
		}
		MPI_Bcast(&next, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
		if(low%next == 0) i = low;
		else i = ceil(low/(float)next)*next;
		//if(i == 0) i = 2;
		if(i < next) i = next;
		i = i < sqrt(N) ? i*i : i;	
//		printf("i=%d, rank=%d\n",i,rank);
//		Generally starts with i*i
		for( j = i; j <= high; j+=next)
			isPrime[j-1] = 0;
	}
	end_time = MPI_Wtime();
	for(i = low; i < high; i++) { if(isPrime[i]) printf("%d ",i+1); }
	printf("\ncalculated by %d of %d on node %s next=%d", rank,size, procname, next);
	printf("Time for serial execution = %f seconds\n",end_time-start_time);
return 0;
}
