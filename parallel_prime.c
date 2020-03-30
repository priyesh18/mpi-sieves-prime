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


	bool isPrime[1000000001];
	unsigned long long t,k, N=1000000000;
	unsigned long long low, high, start;
	unsigned long long i, j, next; //next = 1 is no. 2(first prime)
	unsigned long long* data;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(procname, &len);
	
	
	for(k = 1000; k <= N; k = k*10) {
    	start_time = MPI_Wtime();	
	    next = 1;
    	low = rank*(k/size);
    	high = (rank + 1)*(k/size) - 1;
    // Note: PE with rank 1 should have atleast sqrt(N) nos.
    
    	for(t = 0; t < high - low +1; t++) {
    		isPrime[t] = true;
    	}
    //	isPrime[0] = 0;
    //	isPrime[1] = 0;
    	
    	//make processor 0 find the next prime and broadcast
    	while(next < sqrt(k)) {
    		if(rank == 0) {
    			while(!isPrime[next++] && next < sqrt(k));
    		}
    		MPI_Bcast(&next, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    		if(low%next == 0) i = low;
    		else i = ceil(low/(float)next)*next;
    		if(i < next) i = next;
    		i = i < sqrt(k) ? i*i : i;	
    //		printf("i=%d, rank=%d\n",i,rank);
    //		Generally starts with i*i
    		for( j = i-low; j <= high - low; j+=next)
    			isPrime[j-1] = false;
    	}
    	end_time = MPI_Wtime();
    	if(rank == 0)
	        printf("%d,%f\n",k, end_time-start_time);

	}

// 	for(i = 0; i < high - low; i++) { if(isPrime[i]) printf("%d ",low + i+1); }
// 	printf("\ncalculated by %d of %d on node %s ", rank,size, procname);
// 	printf("Time for serial execution = %f seconds\n",end_time-start_time);
return 0;
}
