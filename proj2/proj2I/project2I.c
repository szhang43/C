#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

int *AllocateArray(int N)
{
    /* Allocate an array with N integers.
     * The value of each element of the array should be a
     * random number between 0 and 10N.
     * Hint: use the rand() function and a modulo operator.
     */
	int *array = malloc(sizeof(int)*N);
	for(int i = 0; i < N; i++){
		array[i] = rand() % (10 * N);
	}
	return array;
}

int compare(const void *a, const void *b){ 
	int x = *(int *)a; 
	int y = *(int *)b; 
	return x -y;
} 

void SortArray(int *A, int N)
{
   qsort(A, N, sizeof(int), compare); 
} 


void DeallocateArray(int *A)
{
	free(A);	
}

int main()
{
    //int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

// For fun:
    int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
                      256000, 512000, 1024000 };

    for (int i = 0 ; i < 11 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
     
        /* Call the three functions in a sequence. Also use
         * gettimeofday calls surrounding each function and set the 
         * corresponding variable (alloc_time, sort_time, dealloc_time).
         */
	
	// Allocate Array 
	struct timeval al_startTime; 
	gettimeofday(&al_startTime , 0); 
	
	int *array = AllocateArray(sizes[i]);

	struct timeval al_endTime; 
	gettimeofday(&al_endTime, 0); 
	alloc_time = (double)(al_endTime.tv_sec - al_startTime.tv_sec) + 
		(double)(al_endTime.tv_usec - al_startTime.tv_usec) / 100000000; 
	//ArrayChecker(array, size[i]);
	// SortArray
	struct timeval sa_startTime; 
	gettimeofday(&sa_startTime, 0); 
	
	SortArray(array, sizes[i]); 

	struct timeval sa_endTime; 
	gettimeofday(&sa_endTime, 0); 
	sort_time = (double)(sa_endTime.tv_sec - sa_startTime.tv_sec) + 
		(double)(sa_endTime.tv_usec - sa_startTime.tv_usec) / 100000000; 
	
	// FreeArray
	
	struct timeval fr_startTime; 
	gettimeofday(&fr_startTime, 0);

	DeallocateArray(array);

	struct timeval fr_endTime; 
	gettimeofday(&fr_endTime, 0); 
	dealloc_time = (double)(fr_endTime.tv_sec - fr_startTime.tv_sec) + 
		(double)(fr_endTime.tv_usec - fr_startTime.tv_usec) / 100000000; 

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
